#ifndef __SEREVER_H_
#define __SEREVER_H_
#include <time.h>
#include "connectionhandler.h"


int get_file_size(FILE *file);

void get_file_extension(char *buff, char *filename);

void get_ip_addres(char *buff, int ip);

int handle_connections(int sock);   // all magic happens here


#endif