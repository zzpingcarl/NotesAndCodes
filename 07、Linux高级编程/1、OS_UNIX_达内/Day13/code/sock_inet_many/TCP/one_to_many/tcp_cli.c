#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>

#define QUE_MAXLEN 	20
#define BUF_MAXLEN 		100

void error_print(const char * ptr_err){
	perror(ptr_err);
	exit(EXIT_FAILURE);
}
int main(char argc, char ** argv)
{
	if(argc <= 2){
		printf("Too few parameter!\n");
		exit(EXIT_FAILURE);
	}

	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd == -1)
		error_print("socket");
	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = inet_addr(argv[1]);
	addr.sin_port = htons(atoi(argv[2]));

	int res = connect(sockfd,(struct sockaddr *)&addr,sizeof(addr));
	if(res == -1)
		error_print("connect");
	printf("connect ok!\n");
	
	char * buf_send = "Hello dear server!";
	res = write(sockfd,buf_send,strlen(buf_send));
	if(res == -1)
		error_print("write");
	printf("发送成功，发送内容为:%s\n",buf_send);
	char buf_recv[BUF_MAXLEN] = {};
	res = read(sockfd,buf_recv,sizeof(buf_recv));
	if(res == -1)
		error_print("read");
	printf("接收成功，接收内容为:%s\n",buf_recv);
	close(sockfd);
	return 0;
}
