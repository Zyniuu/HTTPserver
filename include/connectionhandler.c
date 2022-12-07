#include "connectionhandler.h"


int receive_request(int sock, char *buff) {
    int read;
    if ((read = recv(sock, buff, 4096, 0)) == SOCKET_ERROR) { return -1; }
    return read;
}

void send_header(int client_sock) {
    char *msg = "HTTP/1.0 200 OK\r\nContent-Type: text/html\r\nContent-Length: 42\r\n\r\n";
    send(client_sock, msg, strlen(msg), 0);
}

void send_body(int client_sock) {
    char *msg = "<html>\r\n<h1>Strona testowa</h1>\r\n</html>\r\n";
    send(client_sock, msg, strlen(msg), 0);
}