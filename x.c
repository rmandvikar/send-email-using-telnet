/* rishikesh mandvikar
 * ipp project: mail client
 * nov 30, 2004 
 * x.c
 * compile: gcc x.c -o x
 * run: ./x smtp mail.smu.edu 25
 */


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>

/* Connect to a predefined port on a user specified host */

const int PORT = 25;       /* the port client will be connecting to*/
const int MAXDATASIZE=200; /* max no of bytes we can get at once*/

int main(int argc, char *argv[])
{

	int sockfd, numbytes;
	char buf[MAXDATASIZE];
	struct hostent *he;
	struct sockaddr_in remote_addr; /*connectors address information*/
	unsigned short int port;
	char buf1[3];
	int i;
	int a;
	int q;
	
	/*if (argc !=3)
	{
		fprintf(stderr,"usage: clnt hostname port\n"); 
		exit(1);
	}*/
	
	if ((he=gethostbyname(argv[1])) ==NULL) 
	{ 	
		/* get the host info */
		herror("gethostbyname");
		exit(1);
		//port = atoi(argv[2]);
	}
	
	if ((sockfd=socket(AF_INET, SOCK_STREAM, 0)) == -1)
	{
		perror("socket");
		exit(1);
	}

	remote_addr.sin_family = AF_INET; /* host byte order*/
	remote_addr.sin_port = htons(PORT);    /* short, network byte order*/
	remote_addr.sin_addr = *((struct in_addr *)he->h_addr);
	bzero(&(remote_addr.sin_zero),8);  /*zero rest of the structure*/
	
	/* Connect to address in remote_addr */
	if (connect(sockfd, (struct sockaddr *)&remote_addr, sizeof(struct sockaddr)) == -1)
	{	
		perror("connect");
		exit(1);
	}

	if ((numbytes=recv(sockfd, buf, MAXDATASIZE, 0)) == -1)
	{
		perror("recv");
		exit(1);
	}
	
	///////////////////////////////////////////////////////////////////
	
	//buf[numbytes] = '\0'; /*We must null terminate the buffer */
	//printf("received: %s \n",buf);
	//a=atoi(buf);
	//printf("%d \n",a);
	
	int k;
	int j=0;	
	//HELO 
	char t[100]="";
	do 
	{
		char msg0[] = "HELO ";//smu.edu";
		//q = strlen(msg0);
		printf("enter hostname\n");
		fgets(t,100,stdin);
		//strcat(msg0, t);
		q = strlen(msg0);
		/*msg0[q-1]='\0';
		msg0[q]= 13;
		msg0[q+1]=10;
		msg0[q+2]='\0';
		q=q+2;*/
		//printf("%d\n",strlen(msg0)); 
		write(sockfd, msg0, q);
		write(sockfd, t, 100);
		bzero(buf, strlen(buf));
		read(sockfd, buf, 100);
		printf("%s", buf);
		for(k=0; k<=q; k++)
			printf("%c*", msg0[k]);
		for(k=0;k<=strlen(t); k++)
			printf("%c*",t[k]);

		if(++j==5) exit(0);

	}
	while(buf[0]==53);
	j=0;
	//MAIL FROM:
	do
	{
		printf("enter sender\n");
		//char t[100]="";
		//bzero(t,99);
		fgets(t, 100, stdin);
		char msg1[]="MAIL FROM: "; 
		q=strlen(msg1);
		write(sockfd, msg1, q);
		write(sockfd, t, strlen(t)-1);
		t[0]=13;t[1]=10;
		write(sockfd, t, 2);
		//write(sockfd, 10, 1);
		bzero(buf, 200);//strlen(buf)); 
		read(sockfd, buf, 200);//strlen(buf));
		printf("%s\n", buf);
		//printf("qmsg1:%d\n",q);
		for(k=0; k<=q; k++)
			printf("%c*",msg1[k]);
                for(k=0;k<=strlen(t); k++)
                        printf("%c*",t[k]);
		if(++j==5) exit(0);

	}
	while(buf[0]==53);
	        j=0;

	//RCPT TO:
	do
	{
		printf("enter rcpt email addy\n");
		char msg2[] = "RCPT TO: ";//rmandvik@smu.edu";
		//printf("msg2: %s\n", msg2);
		fgets(t,100,stdin);
		strcat(msg2, t);
		q = strlen(msg2);
		msg2[q-1]='\0';
		msg2[q] = 13;
		msg2[q+1] = 10;
		msg2[q+2] = '\0';
		q=q+2;
		//printf("qmsg2:%d\n",q);
		write(sockfd, msg2, q);
		bzero(buf, 100);//strlen(buf));
		read(sockfd, buf, 100);//strlen(buf));
		printf("%s \n", buf);
		//int k;
		//for(k=0; k<=q; k++)
		//printf("%d*",msg2[k]);
		//printf("\n\n\n\n\nrcptbuf[0]%d\n",buf[0]);
                if(++j==5) exit(0);

	}
	while(buf[0]==53);
        j=0;
	
	printf("\n");                                                                                                                          
	
	///DATA
	do
	{
		char msg3[] = "DATA";
		printf("msg3: %s\n", msg3);
		q = strlen(msg3);
		msg3[q+1] = 13;
		msg3[q+2] = 10;
		msg3[q+3] = '\0';
		q=q+3;
		
		write(sockfd, msg3, q);
		bzero(buf, strlen(buf));
		read(sockfd, buf, 100);//strlen(buf));
		printf("%s \n", buf);
                if(++j==5) exit(0);

	}
	while(buf[0]==53);
        j=0;

	
	//EMAIL BODY
	printf("enter email body\n");
	//int t=0;
	char m[]="";// = "body";
	while(1)
	{	
		//m = itoa(t);
		//printf("\n%d",++t);
		bzero(m,100);
		fgets(m,100,stdin);
		//write(sockfd, m, strlen(m));
		if ((m[0]==46)&&(strlen(m)==2)) break;
		write(sockfd, m, strlen(m));
                if(++j==5) exit(0);

	}

        j=0;
	
	//CRLF.CRLF
	char msg4[] = "";
	//printf("msg4: %s\n", msg4);
	q = strlen(msg4);
	msg4[q+0] = 13;
	msg4[q+1] = 10;
	msg4[q+2] = '.';
	msg4[q+3] = 13;
	msg4[q+4] = 10;
	msg4[q+5] = '\0';
	q=q+6;
	
	write(sockfd, msg4, q);
	bzero(buf, strlen(buf));
	read(sockfd, buf, 100);
	//strlen(buf));
	printf("%s \n", buf);
	
	close(sockfd);
	return (0);
}