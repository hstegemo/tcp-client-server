CC=g++
CC_AMD64=g++
CC_ARM=arm-linux-gnueabi-g++

echo-server: echo-server.cpp saveconfig.cpp saveconfig.h
	$(CC) echo-server.cpp saveconfig.cpp -o echo-server

echo-server-amd64: echo-server.cpp saveconfig.cpp saveconfig.h
	$(CC_AMD64) echo-server.cpp saveconfig.cpp -o echo-server-amd64

echo-server-arm: echo-server.cpp saveconfig.cpp saveconfig.h
	$(CC_ARM) echo-server.cpp saveconfig.cpp -o echo-server-arm --static

clean:
	rm -rf echo-server-arm echo-server-amd64 echo-server a.out
