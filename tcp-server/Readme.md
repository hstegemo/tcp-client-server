This is the tcp-server application that is created for the reMarkable. It is created for receiving settings from the tcp-desktop-client.

For cross-compiling c++ for Arm, the arm-linux-gnueabi-g++ crosscompiler was used.

saveconfig.cpp contains quick and dirty functions that was created to make it possible to save different settings. This was mostly used for making it possible for cencors to test the solution, and also to make a it possible to show a video presentation of the solution without taking too many shortcuts.
