#include <iostream>
#include <cstdlib>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <fstream>
#include "saveconfig.h"
using namespace std;

std::string convertToString(char* a, int size)
{
    int i;
    std::string s = "";
    for (i = 0; i < size; i++) {
        s = s + a[i];
    }
    return s;
}

// Checks If a c-style string is an integer
bool is_int(char *c) {
    while (*c != '\0')
    {
        if (*c < '0' || *c > '9')
            return false;
        c++;
    }
    return true;
}

int main(int argc, char **argv) {
    std::ofstream outfile;
    //outfile.open("messages.txt");

    if (argc != 2 || !is_int(argv[1])) {
        std::cerr << "[ERROR] Port is not provided via command line parameters!\n";
        return -1;
    }

    // Create a socket & get the file descriptor
    int sock_listener = socket(AF_INET, SOCK_STREAM, 0);
    // Check If the socket is created
    if (sock_listener < 0) {
        std::cerr << "[ERROR] Socket cannot be created!\n";
        return -2;
    }

    std::cout << "[INFO] Socket has been created.\n";
    // Address info to bind socket
    sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(std::atoi(argv[1]));
    //server_addr.sin_addr.s_addr = INADDR_ANY;
    // OR
    inet_pton(AF_INET, "0.0.0.0", &server_addr.sin_addr);

    char buf[INET_ADDRSTRLEN];

    // Bind socket
    if (bind(sock_listener, (sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        std::cerr << "[ERROR] Created socket cannot be binded to ( "
                  << inet_ntop(AF_INET, &server_addr.sin_addr, buf, INET_ADDRSTRLEN)
                  << ":" << ntohs(server_addr.sin_port) << ")\n";
        return -3;
    }

    std::cout << "[INFO] Sock is binded to ("
              << inet_ntop(AF_INET, &server_addr.sin_addr, buf, INET_ADDRSTRLEN)
              << ":" << ntohs(server_addr.sin_port) << ")\n";

    // Start listening
    if (listen(sock_listener, SOMAXCONN) < 0) {
        std::cerr << "[ERROR] Socket cannot be switched to listen mode!\n";
        return -4;
    }
    std::cout << "[INFO] Socket is listening now.\n";

    sockaddr_in client_addr;
    socklen_t client_addr_size = sizeof(client_addr);
    int sock_client;
    if ((sock_client = accept(sock_listener, (sockaddr*)&client_addr, &client_addr_size)) < 0) {
        std::cerr << "[ERROR] Connections cannot be accepted for a reason.\n";
        return -5;
    }

    std::cout << "[INFO] A connection is accepted now.\n";

    // Close main listener socket
    close(sock_listener);
    std::cout << "[INFO] Main listener socket is closed.\n";

    // Get name info
    char host[NI_MAXHOST];
    char svc[NI_MAXSERV];

    if (getnameinfo(
            (sockaddr*)&client_addr, client_addr_size,
            host, NI_MAXHOST,
            svc, NI_MAXSERV, 0) != 0) {
        std::cout << "[INFO] Client: (" << inet_ntop(AF_INET, &client_addr.sin_addr, buf, INET_ADDRSTRLEN)
                  << ":" << ntohs(client_addr.sin_port) << ")\n";
    } else {
        std::cout << "[INFO] Client: (host: " << host << ", service: " << svc << ")\n";
    }


    char msg_buf[4096];
    int bytes;
    // While receiving - display & echo msg
    while (true) {
        bytes = recv(sock_client, &msg_buf, 4096, 0);
        // Check how many bytes recieved
        // If there is no data, it means server is disconnected
        if (bytes == 0) {
            std::cout << "[INFO] Client is disconnected.\n";
            break;
        }
            // If something gone wrong
        else if (bytes < 0) {
            std::cerr << "[ERROR] Something went wrong while receiving data!.\n";
            break;
        }
            // If there is some bytes
        else {
                // Print message
                cout << "client> " << string(msg_buf, 0, bytes) << "\n";
                outfile << string(msg_buf, 0, bytes) << "\n";
                string uploadservice = convertToString(msg_buf, sizeof(msg_buf) / sizeof(char)).substr(0, 4);
                if (uploadservice.compare("ssh ")==0) {
                    writeLoginToFile(string(msg_buf, 0, bytes), "ssh");
                } else if (uploadservice.compare("ftp ")==0) {
                    writeLoginToFile(string(msg_buf, 0, bytes), "ftp");
                } else if (uploadservice.compare("gdri")==0) {
                    writeLoginToFile(string(msg_buf, 0, bytes), "gdrive");

                } else if (uploadservice.compare("deff")==0){   // def = ftp is default
		  // Recommended to change this, to a check for each possible
		  // active service
                    writeDefaultService("default=ftp");
                }else if (uploadservice.compare("defg")==0){    // defg => gdrive is default backup servce
		  // Active service = google drive
                    writeDefaultService("default=gdrive");
                }else if (uploadservice.compare("defs")==0){    // defs = ssh is default backup service
		  // Recommended to change this, to a check for each possible
		  // active service
                    writeDefaultService("default=ssh");
                } else {
		    ofstream errorfile;
	            errorfile.open("echo-server-error.log");
	            errorfile << string(msg_buf, 0, bytes) << endl;
		    errorfile.close();
		    cout << "Logged error" << endl;

                }

            // Resend the same message
            if (send(sock_client, &msg_buf, bytes, 0) < 0) {
                std::cerr << "[ERROR] Message cannot be send, exiting...\n";
                break;
            }
        }

    }
    // Close client socket
    close(sock_client);
    std::cout << "[INFO] Client socket is closed.\n";

    // Using an error code as exit value, so that "Restart=on-failure" in the service file is triggered.
    // Check if it's possible to restart on all exit value, whether it's a failure or not.
    return 0;
}
