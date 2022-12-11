#include "server.h"


int get_file_size(FILE *file) {
    int lSize;
    fseek(file, 0, SEEK_END);
    lSize = ftell(file);
    rewind(file);
    return lSize;
}

void get_file_extension(char *buff, char *filename) {
    int index = 0;
    int z = 0;
    int len = strlen(filename);
    for (int i = len - 1; i >= 0; i--) {
        if (filename[i] == '.') {
            index = i + 1;
            break;
        }
    }

    for (int i = index; i < len; i++) {
        buff[z] = filename[i];
        z++;
    }
    buff[z] = '\0';
}

void get_ip_addres(char *buffer, int ip) {
    sprintf(buffer, 
            "%d.%d.%d.%d",
            (ip      ) & 0xFF,
            (ip >>  8) & 0xFF,
            (ip >> 16) & 0xFF,
            (ip >> 24) & 0xFF);
}

int handle_connections(int sock) {
    SOCKET client_socket;
    struct sockaddr_in client;
    int c = sizeof(struct sockaddr_in);
    char buff[4096];
    char filename[1024];
    char extension[10];
    int recv_size;

    listen(sock, 3);
    puts("[*] Server is listening...\n\n");
    while ((client_socket = accept(sock, (struct sockaddr *)&client, &c)) != INVALID_SOCKET) {
        puts("Connection accepted.\n");

        if ((recv_size = receive_request(client_socket, buff)) == -1) { puts("[X] Recv Error."); }
        buff[recv_size] = '\0';
        puts(buff);

        if (is_get_req(buff)) {
            get_filename_from_header(buff, filename);
            get_file_extension(extension, filename);
            FILE *logs = fopen("logs.txt", "a");
            char ip[16];
            get_ip_addres(ip, client.sin_addr.S_un.S_addr);
            time_t t = time(NULL);
            struct tm *tm = localtime(&t);
            fprintf(logs, "%-16s\t%-16s\t%-26s\n", ip, filename, asctime(tm));
            fclose(logs);

            FILE *file = fopen(filename, "rb");
            if (file) {
                int lSize = get_file_size(file);
                send_header(client_socket, lSize, extension);
                send_body(client_socket, file, lSize);
            }
            else {
                send_header(client_socket, 0, extension);
            }

            fclose(file);
        }
        closesocket(client_socket);
    }

    if (client_socket == INVALID_SOCKET) { return -1; }
    return 0;
}