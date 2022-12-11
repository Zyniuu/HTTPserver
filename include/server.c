#include "server.h"


int get_file_size(FILE *file) {
    /* Get file size by moving pointer to the end of file and reading the size */
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
    /* Get the index from witch the extension starts */
    for (int i = len - 1; i >= 0; i--) {
        if (filename[i] == '.') {
            index = i + 1;
            break;
        }
    }

    /* Save extension to the 'buff' */
    for (int i = index; i < len; i++) {
        buff[z] = filename[i];
        z++;
    }
    buff[z] = '\0';
}

void get_ip_addres(char *buffer, int ip) {
    /* Convert ip address from long int to the string by moving bits */
    sprintf(buffer, 
            "%d.%d.%d.%d",
            (ip      ) & 0xFF,
            (ip >>  8) & 0xFF,
            (ip >> 16) & 0xFF,
            (ip >> 24) & 0xFF);
}

int handle_connections(int sock) {
    /* init data needed */
    SOCKET client_socket;
    struct sockaddr_in client;
    int c = sizeof(struct sockaddr_in);
    char buff[4096];
    char filename[1024];
    char extension[10];
    int recv_size;

    /* Start listening for connections */
    listen(sock, 3);
    puts("[*] Server is listening...\n\n");

    /* Accept coming connection */
    while ((client_socket = accept(sock, (struct sockaddr *)&client, &c)) != INVALID_SOCKET) {
        puts("Connection accepted.\n");

        /* Recieve the header from the client and print an error if there is none */
        /* and finally print out the request */
        if ((recv_size = receive_request(client_socket, buff)) == -1) { puts("[X] Recv Error."); }
        buff[recv_size] = '\0';
        puts(buff);

        /* Proceed only if this GET request */
        if (is_get_req(buff)) {
            /* Get filename and file extension */
            get_filename_from_header(buff, filename);
            get_file_extension(extension, filename);

            /* Save the client's ip address, requested file and time of connection to the 'logs.txt' file */
            FILE *logs = fopen("logs.txt", "a");
            char ip[16];
            get_ip_addres(ip, client.sin_addr.S_un.S_addr);
            time_t t = time(NULL);
            struct tm *tm = localtime(&t);
            fprintf(logs, "%-16s\t%-16s\t%-26s\n", ip, filename, asctime(tm));
            fclose(logs);

            /* Open requested file and check if it exists */
            FILE *file = fopen(filename, "rb");
            if (file) {
                /* Send the requested file with appriotiate header */
                int lSize = get_file_size(file);
                send_header(client_socket, lSize, extension);
                send_body(client_socket, file, lSize);
            }
            else {
                /* If the file was not found send only error header */
                send_header(client_socket, 0, extension);
            }

            fclose(file);
        }
        closesocket(client_socket);
    }

    /* If client connection failed return error */
    if (client_socket == INVALID_SOCKET) { return -1; }
    return 0;
}