#ifndef __NETWRORKINIT_H_
#define __NETWRORKINIT_H_
#include <WinSock2.h>


SOCKET init_socket();           // initialize socket and return it

int bind_socket(int sock);      // bind socket to local ip and port 80


#endif