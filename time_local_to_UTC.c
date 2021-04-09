#include <stdio.h>
#include <time.h>
#include "baseutils.h"

/* convert format string to time_t UTC */
time_t atotimef_utc(const char *s, const char *format)
{
	struct tm tm;
	if (s == NULL || format == NULL || strlen(s) == 0)
		return 0;
	sscanf(s, format, &tm.tm_year, &tm.tm_mon, &tm.tm_mday, &tm.tm_hour, &tm.tm_min, &tm.tm_sec);
	tm.tm_year = tm.tm_year - 1900;
	tm.tm_mon = tm.tm_mon - 1;
	// update system timezone
	tzset(); 	
	 // convert timezone from local to utc
	 // __timezone defined in "time.h"
	tm.tm_sec = tm.tm_sec + __timezone;

	return mktime(&tm);
}

/* convert time string from current timezone to UTC */
// input time format is "YYYY-mm-ddTHH:MM:SS"
// output time format is "YYYY-mm-ddTHH:MM:SS"
int time_str_to_UCT(char *time_cur, char *time_utc)
{
	if (!time_utc || !time_cur || strlen(time_cur) == 0) {
		return -1;
	}
	// utc
	time_t utctime;
	utctime = atotimef_utc(time_cur, "%d-%d-%dT%d:%d:%d");
	sprintf(time_utc, "%s", timetoaf(utctime, "%Y-%m-%dT%H:%M:%S"));
	return 0;
}

void main(int argc, char **argv)
{
	time_t utctime;
	char utc_time[64];

	if (argc < 2) {
		printf("%s YYYY-MM-DDThh:mm:ss\n", argv[0]);
		return;
	} 

	// utc
	time_str_to_UCT(argv[1], utc_time);
	printf("utc: %s\n", utc_time);

	return;
}
