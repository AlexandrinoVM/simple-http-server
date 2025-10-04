#include <asm-generic/socket.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/sendfile.h>
#include <sys/stat.h>
int main(){
    struct sockaddr_in address ;
    int new_socket,r,s; 
    int opt =1;
    char buffer[1024]={0};
    socklen_t addrleng = sizeof(address);
    char message[] = "message received\r\n";

    if((s = socket(AF_INET,SOCK_STREAM,0)) < 0){
        printf("could create socket");
        exit(EXIT_FAILURE);
    }

    if(setsockopt(s, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))){
        printf("error reusing port");
        exit(EXIT_FAILURE);

    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr =INADDR_ANY;
    address.sin_port = htons(8080);

    if(bind(s,(struct sockaddr *)&address,sizeof(struct sockaddr_in)) < 0){
        printf("could not bind socket");
        exit(EXIT_FAILURE);

    }

    if((listen(s, 10))<0){
        printf("could not listem");
        exit(EXIT_FAILURE);
    }

    while(1){
        new_socket = accept(s, (struct sockaddr *)&address, &addrleng);

        if(new_socket < 0){
            perror("!ACCEPT ERROR!"); 
            continue;
        }

        size_t bytes_recived = recv(new_socket, buffer, sizeof(buffer), 0);
        if(bytes_recived<0){
            printf("recv failed");
            exit(EXIT_FAILURE);
        }else if (bytes_recived == 0) {
            perror("!RECV ERROR!"); 
            close(new_socket);
            continue;
        }

        buffer[bytes_recived] = '\0';
        printf("%s\n",buffer);

        if((send(new_socket,message,strlen(message),0))<0){
           perror("!SEND ERROR!");
        }
        close(new_socket);
        buffer[0] ='\0';
    }
    close(s);


    return 0;
}
