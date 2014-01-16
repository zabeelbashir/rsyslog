#include"rsyslog.c"
#include<stdio.h>

int main()
{
	int i = 12345679;
	rsyslog_connect();
	log(RLOG_DEBUG,"hey: %i\n", i);
	log(RLOG_CRITICAL, "hey: %i\n", i);
        log(RLOG_INFO, "hey: %i\n", i);
}
