#include <asm-generic/socket.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdlib.h>
#include <arpa/inet.h>

#define PORT 8080

int main(int argc,char *argv[]){
    struct sockaddr_in address ;
    int new_socket,r,client_fd; 
    char buffer[1024]={0};
    socklen_t addrleng = sizeof(address);

    if(argc < 3){
        printf("need atleast two arguments");
        exit(EXIT_FAILURE);
    }

    char *message = argv[2];
    char *ip_address = argv[1];

    if(inet_pton(AF_INET,ip_address,&address) <= 0 ){
        printf("could not get this addres");
        exit(EXIT_FAILURE);
    }
    if((client_fd = socket(AF_INET,SOCK_STREAM,0)) < 0){
        printf("could create client socket");
        exit(EXIT_FAILURE);
    }
    address.sin_family = AF_INET;
    address.sin_port = htons(PORT);
    address.sin_addr.s_addr = inet_addr(ip_address);

    if(connect(client_fd,(struct sockaddr *)&address, addrleng) < 0){
        printf("could not connect client socket");
        perror("!CONNECT ERROR!");
        exit(EXIT_FAILURE);
    }
    send(client_fd, message, strlen(message), 0);
    r = recv(client_fd, &buffer, sizeof(buffer), 0);
    printf("reposnse from server:%s\n",buffer);
    close(client_fd);
    return 0;
}
