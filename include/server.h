#ifndef __SEREVER_H_
#define __SEREVER_H_
#include <stdio.h>
#include "networkinit.h"
#include "connectionhandler.h"
#include "requesthandler.h"


int handle_connections(SOCKET *sock);   // all magic happens here


#endif