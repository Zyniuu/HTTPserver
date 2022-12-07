#ifndef __CONNECTIONHANDLER_H_
#define __CONNECTIONHANDLER_H_
#include <WinSock2.h>


int receive_request(int sock, char *buff); // receive request header from client

void send_header(int client_sock);         // send header to the client

void send_body(int client_sock);           // and body of the response


#endif