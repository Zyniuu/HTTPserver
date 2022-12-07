#ifndef __REQUESTHANDLER_H_
#define __REQUESTHANDLER_H_
#include <string.h>


int is_get_req(char *header);                                       // check if received request is GET request

void get_filename_from_header(char *header, char *filenamebuff);    // get filename


#endif