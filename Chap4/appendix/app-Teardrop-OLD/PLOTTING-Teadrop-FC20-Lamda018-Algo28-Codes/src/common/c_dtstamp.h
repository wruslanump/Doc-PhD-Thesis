/*
 * c_dtstamp.h
 *
 *  Created on: Mon 10 Jan 2022 05:42:26 PM +08
 *      Author: wruslan
 */

#ifndef C_DTSTAMP_H_
#define C_DTSTAMP_H_

#include "c_dtstamp.c"    // MUST INCLUDE RESPECTIVE IMPLEMENTATION CODE

// THE FOLLOWING ARE DEFINED INSIDE <time.h>
// https://users.pja.edu.pl/~jms/qnx/help/watcom/clibref/qnx/clock_gettime.html
int clock_gettime  (clock_t clock_id, struct timespec *tp );
int clock_getres   (clock_t clock_id, struct timespec *res);
int clock_nanosleep(clock_t clock_id, int flags, const struct timespec * rqtp, struct timespec * rmtp );

char* get_datetime_stamp(void);
char* get_time_stamp(void);

void DTStamp(void);
void WRY_starting_salutation(void);
void WRY_ending_salutation(void);
void total_program_duration(void);

void current_working_directory(void);
void display_date_only(void);
void display_resolution_date_time(void);

void sleep_sec(long inp_sec);
void sleep_msec(long inp_millisec);
void sleep_usec(long inp_microsec);
void sleep_nsec(long inp_nanosec);

void start_timer(int timer_num);
void stop_timer(int timer_num);
void duration_timer(void);
void duration_thread(struct timespec t_startthread, struct timespec t_endthread) ;

#endif /* C_DTSTAMP_H_ */
