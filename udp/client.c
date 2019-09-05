#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main()
{
	char *msg = "Hello from client!\n";
	int sock;
    	struct sockaddr_in addr;
	char buf[1024];
    	int bytes_read;
	int len;

    	sock = socket(AF_INET, SOCK_DGRAM, 0);

    	if(sock < 0)
    	{
        	perror("socket");
        	exit(1);
	}

    	addr.sin_family = AF_INET;
    	addr.sin_port = htons(3439);
    	addr.sin_addr.s_addr = INADDR_ANY;
    	sendto(sock, (const char *)msg, strlen(msg), MSG_CONFIRM,(const struct sockaddr *) &addr, sizeof(addr));
	bytes_read=recvfrom(sock, (char *)buf, 1024, MSG_WAITALL,(struct sockaddr *) &addr, &len);
	buf[bytes_read] = '\0';
	printf("%s",buf);
	close(sock);

    	return 0;
}
