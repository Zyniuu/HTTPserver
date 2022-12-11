#include "networkinit.h"


SOCKET init_socket() {
    SOCKET sock;
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) { return -1; }
    return sock;
}

int bind_socket(int sock) {
    struct sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(80);
    if (bind(sock, (struct sockaddr *)&server, sizeof(server)) == SOCKET_ERROR) { return -1; }
    return 0;
}