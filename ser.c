#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <unistd.h>
#include <ctype.h>
#include <netinet/in.h>//internet address family
#include <arpa/inet.h>
#include <string.h>
#include <sys/wait.h>
#include <stdlib.h>
int main (void){
	int s_fd;
	int arr1[110][3];
	int arr2[110][3];
	struct sockaddr_in ser;//IPv4协议族
	struct sockaddr_in cli1,cli2;
	s_fd=socket(AF_INET,SOCK_STREAM,0);
	if(s_fd==-1){
		perror("socket");
		return 1;
	}
	ser.sin_family=AF_INET;
	ser.sin_port=htons(6666);
	ser.sin_addr.s_addr=htonl(INADDR_ANY);
	int b=bind(s_fd,(struct sockaddr *)&ser,sizeof(ser));
	if(b==-1){
		perror("bind");
		return 2;
	}
	//监听sockfd
	int l=listen(s_fd,5);
	if(l==-1){
		perror("listen");
		return 3;
	}
	
	while(1){
		int cli_len=sizeof(cli1);
		//阻塞等待客户端连接的到来
		int connfd1=accept(s_fd,(struct sockaddr *)&cli1,&cli_len);
		int connfd2=accept(s_fd,(struct sockaddr *)&cli2,&cli_len);
		if(connfd1==-1||connfd2==-1){
			perror("accept");
			return 4;
		}
		//在这里fork子进程
		pid_t pid=fork();
		if(pid==-1){
			perror("fork");
			return 5;
		}
		if(pid==0){//负责和客户端通讯
			close(s_fd);
			//将客户端的IP地址的二进制转化为字符串格式
			//char ip[128];
			//printf("IP:%s\n",inet_ntop(AF_INET,&cli1.sin_addr,ip,128));
			//数据处理
			while(1){
				read(connfd1,arr1,1320);
				//回应给客户端
				write(connfd2,arr1,1320);
			}
		}
		else{
			close(s_fd);
			//将客户端的IP地址的二进制转化为字符串格式
			//char ip[128];
			//printf("IP:%s\n",inet_ntop(AF_INET,&cli2.sin_addr,ip,128));
			//数据处理
			while(1){
				read(connfd2,arr2,1320);
				//回应给客户端
				write(connfd1,arr2,1320);
			}
			
		}
	}
	return 0;
}
