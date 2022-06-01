#include <iostream>
#include <string>
#include <cstring>

/* This file uses the system library function to run linux commands to write output to a file. This is because it needs
 * to remove lines from the config file without deleting all of it. The commands it uses are cat, echo, mv and sed.
*/

std::string filename = "backup.conf";

void writeLoginToFile(std::string msg, std::string srvname){
    // Read from filename, delete srvname from filename's content, and then write it to filename.tmp
    // An example of how command usage, that would do the same:
    //      cat backup.conf | sed '/ssh.*/d' > backup.conf.tmp
    //      mv backup.conf.tmp backup.conf
    //      echo msg >> backup.conf
    
    std::string command2 = "cat " + filename + "|sed '/^" + srvname + ".*/d' > " + filename + ".tmp";
    int n2 = command2.length();
    char char_array2[n2+1];
    strcpy(char_array2, command2.c_str());
    system(char_array2);
    
    std::string command3 = "mv " + filename + ".tmp" + " " + filename;
    int n3 = command3.length();
    char char_array3[n3+1];
    strcpy(char_array3, command3.c_str());
    system(char_array3);
    
    std::string command = "echo " + msg + " >> " + filename;
    int n = command.length();
    char char_array[n+1];
    strcpy(char_array, command.c_str());    // argument for the system command needs to be a char pointer
    system(char_array); // system = run a command, in this case the echo command
    std::cout << "Added " << msg << '\n';
}

void writeDefaultService(std::string srvname){
    // Read from filename, delete srvname from filename's content, and then write it to filename.tmp
    // An example of how command usage, that would do the same:
    //      cat backup.conf | sed '/default=.*/d' > backup.conf.tmp
    //      mv backup.conf.tmp backup.conf
    //      echo default=ssh >> backup.conf
    std::string command2 = "cat " + filename + "|sed '/default=.*/d' > " + filename + ".tmp";
    int n2 = command2.length();
    char char_array2[n2+1];
    strcpy(char_array2, command2.c_str());
    system(char_array2);
    
    std::string command3 = "mv " + filename + ".tmp" + " " + filename;
    int n3 = command3.length();
    char char_array3[n3+1];
    strcpy(char_array3, command3.c_str());
    system(char_array3);
    
    std::string command = "echo " + srvname + " >> " + filename;
    int n = command.length();
    char char_array[n+1];
    strcpy(char_array, command.c_str());
    system(char_array);
    std::cout << "Added default=" << srvname << '\n';
}
