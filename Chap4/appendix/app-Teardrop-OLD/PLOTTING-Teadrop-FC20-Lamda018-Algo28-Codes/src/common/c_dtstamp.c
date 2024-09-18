/*
 * c_dtstamp.c
 *
 *  Created on: Mon 10 Jan 2022 05:42:26 PM +08
 *      Author: wruslan
 */

#include <limits.h>   // perror()
#include <stdio.h>
#include <string.h>   // strcat(), strcpy()
#include <unistd.h>   // getcwd()
#include <stdlib.h>   // exit()

#include <sys/time.h> // For local date-time with (microseconds)
#include <time.h>     // For high-res timer clock_gettime with (nanoseconds)
                      // 
// THE FOLLOWING ARE DEFINED INSIDE <time.h>
// https://users.pja.edu.pl/~jms/qnx/help/watcom/clibref/qnx/clock_gettime.html
int clock_gettime  (clock_t clock_id, struct timespec *tp );
int clock_getres   (clock_t clock_id, struct timespec *res);
int clock_nanosleep(clock_t clock_id, int flags, const struct timespec * rqtp, struct timespec * rmtp );

// ========================================================
// GLOBALS
time_t WRY_time;
clock_t  CLOCK_REALTIME;    // THE TYPE DEFINITION
  
char WRY_strbuffer1[26];
char WRY_strbuffer2[60];

long int t_nsec;
char st_nsec[11];
char *datetime_stamp;

struct tm *WRY_tminfo;
struct timeval WRY_usecvalnow;  // inside #include <sys/time> microseconds
struct timespec WRY_nsecvalnow; // For hires timer #include <time> nanoseconds
struct timespec WRY_tvalres;

struct timespec t_starttimer, t_endtimer, tnow;
struct timespec t_startprogram, t_endprogram;

// ========================================================
char* get_time_stamp(void) {
// ========================================================
  time(&WRY_time);
	WRY_tminfo = localtime(&WRY_time);
	strftime(WRY_strbuffer1, 26, "%H:%M:%S ", WRY_tminfo);

  gettimeofday (&WRY_usecvalnow, NULL);            // MICROSECOND
           
	clock_gettime(CLOCK_REALTIME, &WRY_nsecvalnow);  // NANOSECOND
	t_nsec = (long int)WRY_nsecvalnow.tv_nsec; 
	
	// CONVERT TIME IN NANOSECONDS TO ASCI STRING
	// TAKE 9 digits FOR STRING st_nsec
	sprintf(st_nsec,"%ld", t_nsec); 

	// CONCATENATE WITH NANOSECOND STRING	
	strcat(WRY_strbuffer1, st_nsec);
	
	return (WRY_strbuffer1);
}
// ========================================================
char* get_datetime_stamp(void) {
// ========================================================
  time(&WRY_time);
	WRY_tminfo = localtime(&WRY_time);
	strftime(WRY_strbuffer1, 26, "%Y-%m-%d %H:%M:%S ", WRY_tminfo);

  gettimeofday(&WRY_usecvalnow, NULL);
	clock_gettime(CLOCK_REALTIME, &WRY_nsecvalnow);
	t_nsec = (long int)WRY_nsecvalnow.tv_nsec; 
	
	// CONVERT TIME IN NANOSECONDS TO ASCI STRING
	// TAKE 9 digits FOR STRING st_nsec
	sprintf(st_nsec,"%ld", t_nsec); 

	// CONCATENATE WITH NANOSECOND STRING	
	strcat(WRY_strbuffer1, st_nsec);
	
	return (WRY_strbuffer1);

}

// ========================================================
void DTStamp(void) {
// ========================================================
	time(&WRY_time);

	WRY_tminfo = localtime(&WRY_time);
	strftime(WRY_strbuffer1, 26, "%Y-%m-%d %H:%M:%S", WRY_tminfo);

	gettimeofday(&WRY_usecvalnow, NULL);

	printf("%s", WRY_strbuffer1);   // NO \n IN THIS PRINT
	//printf(".%06ld \t", (long int)WRY_usecvalnow.tv_usec);

	clock_gettime(CLOCK_REALTIME, &WRY_nsecvalnow);
	printf(".%09ld \t", (long int)WRY_nsecvalnow.tv_nsec);
}

// ===================================================
void current_working_directory(void) {
// ===================================================
   char cwd[255];
   if (getcwd(cwd, sizeof(cwd)) != NULL) {
	   DTStamp(); printf("Current directory: %s\n", cwd);
   } else {
	   perror("getcwd() error");
   }

}
// ========================================================
void WRY_starting_salutation(void){
// ========================================================
	clock_gettime(CLOCK_REALTIME, &tnow);
	t_startprogram = tnow;

	DTStamp();
	printf("Starting in main(), Bismillah 3 times WRY. \n");
	DTStamp();
	printf("Program started. \n");
	printf("\n");
}
// ========================================================
void WRY_ending_salutation(void){
// ========================================================
	printf("\n");
	DTStamp();
	printf("Program ended. \n");
	DTStamp(); printf("Ending in main(), Alhamdulillah 3 times WRY. \n");
}
// ========================================================
void total_program_duration(void) {
// ========================================================
	clock_gettime(CLOCK_REALTIME, &tnow);
	t_endprogram = tnow;

	struct timespec temp, t_duration;
	if ((t_endprogram.tv_nsec - t_startprogram.tv_nsec) < 0) {
		temp.tv_sec = t_endprogram.tv_sec - t_startprogram.tv_sec - 1;
		temp.tv_nsec = 1000000000 + t_endtimer.tv_nsec - t_startprogram.tv_nsec;
	} else {
		temp.tv_sec = t_endprogram.tv_sec - t_startprogram.tv_sec;
		temp.tv_nsec = t_endprogram.tv_nsec - t_startprogram.tv_nsec;
	}

	t_duration = temp;
	long sec_programduration  = t_duration.tv_sec;
	long nsec_programduration = t_duration.tv_nsec;
	DTStamp();
	printf("Total program run duration   = %ld.%09ld seconds. \n", sec_programduration, nsec_programduration);

}
// ========================================================
void display_date_only(void) {
// ========================================================
	time(&WRY_time);
	WRY_tminfo = localtime(&WRY_time);
	strftime(WRY_strbuffer2, 60, "%a %b %d, %Y %H:%M:%S", WRY_tminfo);

	DTStamp();
	printf("Current date and time: ");
	printf("%s \n", WRY_strbuffer2);
}

// ========================================================
void display_resolution_date_time(void) {
// ========================================================

	clock_getres(CLOCK_REALTIME, &WRY_tvalres);
	DTStamp();
	printf("Clock time resolution \t= %ld nanoseconds\n", WRY_tvalres.tv_nsec);

	/*
	clock_gettime(CLOCK_REALTIME, &WRY_nsecvalnow);
	DTStamp();
	printf("Wall clock time now \t= %ld seconds\n", WRY_nsecvalnow.tv_sec);
	DTStamp();
	printf("Wall clock time now \t= %ld nanoseconds\n", WRY_nsecvalnow.tv_nsec);
	*/
}

// ========================================================
// ALL SLEEP FUNCTIONS USING clock_nanosleep() for
// (seconds, milliseconds. microseconds and nanoseconds)
// ========================================================
void sleep_sec(long inp_sec) {

	// DTStamp(); printf("Sleep for %ld seconds \n", inp_sec);
    struct timespec res;
    res.tv_sec = inp_sec;
    res.tv_nsec = (inp_sec*1000000000) % 1000000000;
    clock_nanosleep(CLOCK_REALTIME, 0, &res, NULL);
}

void sleep_msec(long inp_millisec) {
	// DTStamp(); printf("Sleep for %ld milliseconds \n", inp_millisec);
    struct timespec res;
    res.tv_sec = inp_millisec/1000;
    res.tv_nsec = (inp_millisec*1000000) % 1000000000;
    clock_nanosleep(CLOCK_REALTIME, 0, &res, NULL);
}

void sleep_usec(long inp_microsec) {
	// DTStamp(); printf("Sleep for %ld microseconds \n", inp_microsec);
    struct timespec res;
    res.tv_sec = inp_microsec/1000000;
    res.tv_nsec = (inp_microsec*1000) % 1000000000;
    clock_nanosleep(CLOCK_REALTIME, 0, &res, NULL);
}

void sleep_nsec(long inp_nanosec) {
	// DTStamp(); printf("Sleep for %ld nanoseconds \n", inp_nanosec);
    struct timespec res;
    res.tv_sec = inp_nanosec/1000000000;
    res.tv_nsec = (inp_nanosec*1) % 1000000000;
    clock_nanosleep(CLOCK_REALTIME, 0, &res, NULL);
}

// ========================================================
void start_timer(int timer_number){
// ========================================================
	clock_gettime(CLOCK_REALTIME, &tnow);
	t_starttimer = tnow;

	DTStamp();
	printf("Timer %d start. \n", timer_number);
}

// ========================================================
void duration_timer(void) {
// ========================================================

	struct timespec temp, t_duration;
	if ((t_endtimer.tv_nsec - t_starttimer.tv_nsec) < 0) {
		temp.tv_sec = t_endtimer.tv_sec - t_starttimer.tv_sec - 1;
		temp.tv_nsec = 1000000000 + t_endtimer.tv_nsec - t_starttimer.tv_nsec;
	} else {
		temp.tv_sec = t_endtimer.tv_sec - t_starttimer.tv_sec;
		temp.tv_nsec = t_endtimer.tv_nsec - t_starttimer.tv_nsec;
	}

	t_duration = temp;
	long sec_timerduration  = t_duration.tv_sec;
	long nsec_timerduration = t_duration.tv_nsec;

	printf("Duration (timer start-to-stop) = %ld.%09ld seconds. \n", sec_timerduration, nsec_timerduration);

}

// ========================================================
void stop_timer(int timer_number){
// ========================================================
	clock_gettime(CLOCK_REALTIME, &tnow);
	t_endtimer = tnow;

	DTStamp();
	printf("Timer %d stop. ", timer_number);
	duration_timer();
	printf("\n");
}

// ========================================================
void duration_thread(struct timespec t_startthread, struct timespec t_endthread) {
// ========================================================

	struct timespec temp, t_duration;

	if ((t_endthread.tv_nsec - t_startthread.tv_nsec) < 0) {
		temp.tv_sec = t_endthread.tv_sec - t_startthread.tv_sec - 1;
		temp.tv_nsec = 1000000000 + t_endthread.tv_nsec - t_startthread.tv_nsec;
	} else {
		temp.tv_sec = t_endthread.tv_sec - t_startthread.tv_sec;
		temp.tv_nsec = t_endthread.tv_nsec - t_startthread.tv_nsec;
	}

	t_duration = temp;
	long sec_threadduration  = t_duration.tv_sec;
	long nsec_threadduration = t_duration.tv_nsec;

	printf("Run duration = %ld.%09ld seconds. \n", sec_threadduration, nsec_threadduration);

}

// ========================================================
struct timespec duration(struct timespec timer_begin, struct timespec timer_end) {
// ========================================================
    struct timespec temp;

    if ((timer_end.tv_nsec - timer_begin.tv_nsec) < 0) {
        temp.tv_sec = timer_end.tv_sec - timer_begin.tv_sec - 1;
        temp.tv_nsec = 1000000000 + timer_end.tv_nsec - timer_begin.tv_nsec;
    } else {
        temp.tv_sec = timer_end.tv_sec - timer_begin.tv_sec;
        temp.tv_nsec = timer_end.tv_nsec - timer_begin.tv_nsec;
    }
return temp;
}

// ========================================================

