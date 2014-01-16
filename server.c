#include <sys/socket.h>
#include <netinet/in.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define KNRM  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"
#define KWHT  "\x1B[37m"

char port[100];
char file[100];

void termination_handler (int signo)
{
	if (signo == SIGINT)
	{
		printf("%sKill Signal received. Exiting!\n", KNRM);
		exit(0);
	}
}

void display(char *msg)
{
	char exp=msg[0];
	FILE *fp;
//	fp=fopen(file, "a");
	switch(exp)
	{
		case 'C':
			printf("%s[CRITICAL] %s", KRED, msg+2);
//			fprintf(fp,"[CRITICAL] %s", msg+2);
			break;
		case 'E':
			printf("%s[EMERGENCY] %s", KBLU, msg+2);
//			fprintf(fp,"[EMERGENCY] %s", msg+2);
			break;
		case 'D':
			printf("%s[DEBUG] %s", KYEL, msg+2);
//			fprintf(fp,"[DEBUG] %s", msg+2);
			break;
		case 'I':
			printf("%s[INFO] %s", KNRM, msg+2);
//			fprintf(fp,"[INFO] %s", msg+2);
			break;
		default:
			break;
	}
//	fclose(fp);
}

void usage()
{
	printf("Usage: server -port <Port Number> -file <Log File Name>\n");
	exit(0);
}

void GetArgs (int argc, char **argv)
{
	if(argc==5)
	{	}
	else
		usage();
	int idx = 0;
	for (idx = 1; idx < argc;  idx++) 
	{
		if (strcmp(argv[idx], "-file") == 0)
		{
			sprintf(file, "%s", argv[++idx]);
		}
		if (strcmp(argv[idx], "-port") == 0)
		{
			sprintf(port, "%s", argv[++idx]);
		}
		else
		{
			printf("Error: unknown flag %s\n", argv[idx]);
		}
	}
}

int main(int argc, char**argv)
{
//	if (signal (SIGINT, termination_handler) == SIG_IGN)
//		signal (SIGINT, SIG_IGN);
//	GetArgs(argc, argv);
	printf("Starting RSYSLOG Server. To exit press Crtl-C at anytime.\n");
	int sockfd,n;
	struct sockaddr_in servaddr,cliaddr;
	socklen_t len;
	char mesg[1000];
	sockfd=socket(AF_INET,SOCK_DGRAM,0);
	bzero(&servaddr,sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr=htonl(INADDR_ANY);
	servaddr.sin_port=htons(32000);
	bind(sockfd,(struct sockaddr *)&servaddr,sizeof(servaddr));
	for (;;)
	{
		len = sizeof(cliaddr);
		n = recvfrom(sockfd,mesg,1000,0,(struct sockaddr *)&cliaddr,&len);
		display(mesg);
	}
	return 0;
}
