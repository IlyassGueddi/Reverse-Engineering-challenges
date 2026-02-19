#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main() {

    struct sockaddr_in revsockaddr;
    
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    revsockaddr.sin_family = AF_INET;       
    revsockaddr.sin_port = htons(44333);
    revsockaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    
    
    if(connect(sock, (struct sockaddr_in *)&revsockaddr, sizeof(revsockaddr)) == -1) {
        printf("Malware executed. You are screwed. Have a nice day.\n");
        return 0;
    }

    char request[] = "GET /neutralize HTTP/1.1\r\nHost: 127.0.0.1\r\nUser-Agent:crackme.one\r\n\r\n";

    size_t bytesSent = send(sock, request, strlen(request), 0);

    char response[4096];
    size_t bytesRead;

    while ((bytesRead = recv(sock, response, sizeof(response) - 1, 0)) > 0) {
        response[bytesRead] = "\0";
    }

    char* found = strstr(response, "200 OK");
    if (found == NULL) {
        printf("Malware executed. You are screwed. Have a nice day.\n");
    } else {
        printf("Malware successfully neutralized. Good job.\n");
    }

    close(sock);

    return 0;
}