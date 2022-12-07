#include "server.h"


int handle_connections(SOCKET *sock) {
    SOCKET client_socket;
    struct sockaddr_in client;
    int c = sizeof(struct sockaddr_in);
    char buff[4096];
    char filename[1024];
    int recv_size;

    listen(*sock, 3);
    puts("[*] Server is listening...");
    while ((client_socket = accept(*sock, (struct sockaddr *)&client, &c)) != INVALID_SOCKET) {
        puts("Connection accepted.");
        if ((recv_size = receive_request(client_socket, buff)) == -1) { puts("[X] Recv Error."); }
        buff[recv_size] = '\0';
        puts(buff);

        if (is_get_req(buff)) {
            get_filename_from_header(buff, filename);
            printf("Filename: %s\n", filename);
        }

        send_header(client_socket);
        send_body(client_socket);
    }

    if (client_socket == INVALID_SOCKET) { return -1; }
    return 0;
}