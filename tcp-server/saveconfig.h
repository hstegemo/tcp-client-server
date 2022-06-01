#include <iostream>
#include <string>
#include <cstring>

/* This file uses the system library function to run linux commands to write output to a file. This is because it needs
 * to remove lines from the config file without deleting all of it. The commands it uses are cat, echo, mv and sed.
*/

void writeLoginToFile(std::string msg, std::string srvname);
void writeDefaultService(std::string srvname);
