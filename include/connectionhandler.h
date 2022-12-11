#ifndef __CONNECTIONHANDLER_H_
#define __CONNECTIONHANDLER_H_
#include <stdio.h>
#include "networkinit.h"
#include "requesthandler.h"


int receive_request(int sock, char *buff);                              // receive request header from client

void send_header(int client_sock, int bytes_to_send, char *extension);  // send header to the client

void send_body(int client_sock, FILE *file, int file_size);             // and body of the response


#endif