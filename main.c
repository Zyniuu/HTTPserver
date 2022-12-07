#include "include/server.h"


int main() {
    WSADATA wsa;
    SOCKET sock;
    int bind_status, handle_status;

    puts("Initializing WinSock...");
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
        printf("[X] Failed. Error code: %d\n", WSAGetLastError());
        return 1;
    }
    puts("[*] WinSock initialized.");

    puts("Creating socket...");
    if ((sock = init_socket()) == -1) { 
        printf("[X] Could not create socket. Error code: %d\n", WSAGetLastError());
        return 1;
    }
    puts("[*] Socket created.");

    puts("Binding socket...");
    if ((bind_status = bind_socket(&sock)) == -1) {
        printf("[X]  Could not bind socket. Error code: %d\n", WSAGetLastError());
        return 1;
    }
    puts("[*] Socket binded.");

    if ((handle_status = handle_connections(&sock)) == -1) {
        printf("[X]  Could not handle connections. Error code: %d\n", WSAGetLastError());
        return 1;
    }

    closesocket(sock);
    WSACleanup();

    return 0;
}