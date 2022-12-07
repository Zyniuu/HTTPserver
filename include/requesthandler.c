#include "requesthandler.h"


int is_get_req(char *header) {
    char start_req[3] = "GET";
    for (int i = 0; i < 3; i++) {
        if (header[i] != start_req[i]) { return 0; }
    }
    return 1;
}

void get_filename_from_header(char *header, char *filenamebuff) {
    int index = 0;
    int i = 0;
    char start_char = '/';
    char end_char = ' ';

    /* get starting index of filename */
    while (header[index] != start_char) { index++; }

    /* for avoiding '/' in output */
    index++;

    /* check if filename is empty and return 'index.html' if so*/
    if (header[index] == end_char) { strcpy(filenamebuff, "index.html"); }
    else {
        /* add characters to the string until space is detected */
        while (header[index] != end_char) {
            filenamebuff[i] = header[index];
            i++;
            index++;
        }
        filenamebuff[i] = '\0';
    }

}