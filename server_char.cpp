#include<stdio.h>  
#include<sys/socket.h>  
#include<netinet/in.h>  
#include<stdlib.h>  
#include<memory.h>  
#include<string.h>  
#include<sys/socket.h>  
#include <arpa/inet.h>
#include <unistd.h>
  
#define PORT 8888  
int main(){  
    int sock,new_sock;  
    struct sockaddr_in my_addr,client_addr;  
    socklen_t len;  
    char buf[100];  
  
    if((sock=socket(AF_INET,SOCK_STREAM,0))<0){  
        printf("socket create error!\n");  
        exit(1);  
    }  
    memset(&my_addr,0,sizeof(my_addr));  
    my_addr.sin_family=AF_INET;  
    my_addr.sin_port=htons(PORT);  
    my_addr.sin_addr.s_addr=INADDR_ANY;  
  
    if(bind(sock,(struct sockaddr*)&my_addr,sizeof(my_addr))==-1){  
        printf("bind error!\n");  
        exit(1);  
    }  
    if(listen(sock,5)<0){  
        printf("listen error!\n");  
        exit(1);  
    }  
    len=sizeof(struct sockaddr);  
new_sock=accept(sock,(struct sockaddr*)&client_addr,&len);
    if(new_sock < 0){  
        printf("accept error!\n");  
        exit(1);  
    }else{  
        printf("server: get connection from %s,port %d socket %d \n",inet_ntoa(client_addr.sin_addr),ntohs(client_addr.sin_port),new_sock);  
  
    }  
    while(1){  
        memset(buf,0,100);  
        printf("Input message to send: ");  
        fgets(buf,100,stdin);  
        if(!strncasecmp(buf,"quit",4)){  
            printf("server is closing...\n");  
            break;  
        }  
        len=send(new_sock,buf,strlen(buf)-1,0);  
        if(len<0){  
            printf("send error!\n");  
            exit(1);  
        }else{  
            printf("send succeed! send : %s\n",buf);  
        }  
        printf("------------------------------\n");  
        memset(buf,0,100);  
        len=recv(new_sock,buf,100,0);  
        if(len<0){  
            printf("recv error!\n");  
            exit(1);  
        }else if(len == 0){  
            printf("the client quit!\n");  
            break;  
        }else{  
            printf("receive message: %s \n",buf);  
        }  
    }  
    close(sock);  
    close(new_sock);  
    return 0;
} 
