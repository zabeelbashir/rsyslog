#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <stdarg.h>
#include "rsyslog.h"
#include <sys/socket.h>
#include <netinet/in.h>

#define log(level, fmt, ...) _log(level, fmt"\n", ##__VA_ARGS__)

int sockfd,n;
struct sockaddr_in servaddr,cliaddr;

int _log(int level, char *fmt, ...)
{
	int l;
	char* buf;
	char temp[1000];
	va_list arg;
	va_start(arg, fmt);
	switch(level)
	{
		case RLOG_DEBUG:
			l = vsnprintf( 0, 0, fmt, arg );
			buf = (char*) malloc( l + 1 );
			va_start( arg, fmt );
			vsnprintf( buf, l, fmt, arg );
			sprintf(temp, "%s%s", "D:", buf);
			sendto( sockfd, temp, sizeof(temp), 0, (struct sockaddr *)&servaddr, sizeof(servaddr));
			free( buf );
		break;
		case RLOG_CRITICAL:
			l = vsnprintf( 0, 0, fmt, arg );
			buf = (char*) malloc( l + 1 );
			va_start( arg, fmt );
			vsnprintf( buf, l, fmt, arg );
			sprintf(temp, "%s%s", "C:", buf);
			sendto( sockfd, temp, l, 0, (struct sockaddr *)&servaddr, sizeof(servaddr));
			free( buf );
		break;
		case RLOG_ERROR:
			l = vsnprintf( 0, 0, fmt, arg );
			buf = (char*) malloc( l + 1 );
			va_start( arg, fmt );
			vsnprintf( buf, l, fmt, arg );
			sprintf(temp, "%s%s", "E:", buf);
			sendto( sockfd, temp, l, 0, (struct sockaddr *)&servaddr, sizeof(servaddr));
			free( buf );
		break;
		case RLOG_INFO:
			l = vsnprintf( 0, 0, fmt, arg );
			buf = (char*) malloc( l + 1 );
			va_start( arg, fmt );
			vsnprintf( buf, l, fmt, arg );
			sprintf(temp, "%s%s", "I:", buf);
			sendto( sockfd, temp, l, 0, (struct sockaddr *)&servaddr, sizeof(servaddr));
			free( buf );
		break;
		case RLOG_LOCAL:
			vfprintf(stdout, fmt, arg);
			va_end(arg);
			fflush(stdout);
		break;
		default:
		break;
	}
}

int rsyslog_connect()
{
	sockfd=socket(AF_INET,SOCK_DGRAM,0);
	bzero(&servaddr,sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr=inet_addr(remote_ip);
	servaddr.sin_port=htons(remote_port);
}

//int main()
//{
//	int i=103456700;
//	rsyslog_connect();
//	log(RLOG_LOCAL,"hey: %i", i);
//	log(RLOG_DEBUG,"hey: %i\n", i);
//	log(RLOG_CRITICAL,"hey: %i\n", i);
//	log(RLOG_ERROR,"hey: %i\n", i);
//}
