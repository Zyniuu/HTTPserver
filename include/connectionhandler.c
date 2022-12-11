#include "connectionhandler.h"


int receive_request(int sock, char *buff) {
    /* Recevive request header and store it inside buff */
    int read;
    if ((read = recv(sock, buff, 4096, 0)) == SOCKET_ERROR) { return -1; }
    return read;
}

void send_header(int client_sock, int bytes_to_send, char *extension) {
    /* Check what type of file is going to be sent */
    char type[16];
    if (!strcmp(extension, "html")) { strcpy(type, "text/html"); }
    else if (!strcmp(extension, "css")) { strcpy(type, "text/css"); }
    else if (!strcmp(extension, "js")) { strcpy(type, "text/javascript"); }
    else if (!strcmp(extension, "png") || !strcmp(extension, "jpg") || !strcmp(extension, "jpeg")) { strcpy(type, "image/webp"); }
    
    /* Send if the file exists and has something inside */
    if (bytes_to_send > 0) {
        /* Send OK header with file length in bytes */
        char header[4096];
        sprintf(header, "HTTP/1.0 200 OK\r\nContent-Type: %s\r\nContent-Length: %d\r\n\r\n", type, bytes_to_send);
        send(client_sock, header, strlen(header), 0);
    }
    else {
        /* Send back the info of inability to find a file */
        char *header = "HTTP/1.0 404 Not Found\r\n\r\n";
        send(client_sock, header, strlen(header), 0);
    }
}

void send_body(int client_sock, FILE *file, int file_size) {
    /* Sending file itself */
    int offset = 0;
    int result;
    char buffer[4096];
    /* Sending as long as there is still data in the file */
    while (offset < file_size) {
        result = fread(buffer, 1, 4096, file);
        offset += result;
        send(client_sock, buffer, result, 0);
    }
}