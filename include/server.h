#ifndef __SEREVER_H_
#define __SEREVER_H_
#include <time.h>
#include "connectionhandler.h"


int get_file_size(FILE *file);                          // get file size of the file that is going to be sent

void get_file_extension(char *buff, char *filename);    // extract the file extension

void get_ip_addres(char *buff, int ip);                 // extract the ip address in string format

int handle_connections(int sock);                       // all magic happens here


#endif