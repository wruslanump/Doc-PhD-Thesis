/*
 * preempt_rt.c
 *
 *  Created on: Feb 25, 2020
 *      Author: wruslan
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sched.h>
#include <limits.h>
#include <sys/mman.h>
#include <error.h>

#include "common/c_dtstamp.h"

// ========================================================
// GLOBAL VARIABLES
// ==========================================================
// Used for pthreads

struct sched_param 	param;
pthread_attr_t 		  attr;

int ret_lock, ret_pthread_init;
int ret_stacksize, ret_schedpolicy;
int ret_param_sched_priority, ret_inheritsched;

// TO FIGURE THIS OUT
#define PTHREAD_STACK_MIN  4096

// ========================================================
void execute_pthread_settings(void) {
// ========================================================

   // (1) Lock memory
	ret_lock = mlockall(MCL_CURRENT|MCL_FUTURE);
    if(ret_lock == -1) {
            DTStamp(); printf("(1) %m: mlockall memory current/future failed. ret_lock \t= %d \n", ret_lock);
            exit(1);
    } else {
			DTStamp(); printf("(1) %m: mlockall memory current/future success. ret_lock \t= %d \n", ret_lock);
	}

    // (2) Initialize pthread attributes (default values)
    ret_pthread_init = pthread_attr_init(&attr);
    if (ret_pthread_init) {
        DTStamp(); printf("(2) %m: pthread init attributes failed. ret_pth_init \t= %d \n", ret_pthread_init);
    } else {
		DTStamp(); printf("(2) %m: pthread init attributes success. ret_pth_init \t= %d \n", ret_pthread_init);
	}

    // (3) Set a specific stack size
    ret_stacksize = pthread_attr_setstacksize(&attr, PTHREAD_STACK_MIN);
    if (ret_stacksize) {
        DTStamp(); printf("(3) %m: pthread setstacksize failed. ret_stacksize \t= %d \n", ret_stacksize);
    } else {
		DTStamp(); printf("(3) %m: pthread setstacksize success. ret_stacksize \t= %d \n", ret_stacksize);
	}

    // (4) Set scheduler policy
    ret_schedpolicy = pthread_attr_setschedpolicy(&attr, SCHED_FIFO);
    if (ret_schedpolicy) {
        DTStamp(); printf("(4) %m: pthread setschedpolicy failed. ret_schedpolicy \t= %d \n", ret_schedpolicy);
    } else {
		DTStamp(); printf("(4) %m: pthread setschedpolicy success. ret_schedpolicy \t= %d \n", ret_schedpolicy);
	}

	// (5) Set priority of pthread
    param.sched_priority = 80;
    ret_param_sched_priority = pthread_attr_setschedparam(&attr, &param);
    if (ret_param_sched_priority) {
        DTStamp(); printf("(5) %m: pthread setschedparam priority failed. ret_param_sched_priority \t= %d \n", ret_param_sched_priority);
    } else {
		DTStamp(); printf("(5) %m: pthread setschedparam priority success. ret_param_sched_priority \t= %d \n", ret_param_sched_priority);
	}

    // (6) Use scheduling parameters of attr
    ret_inheritsched  = pthread_attr_setinheritsched(&attr, PTHREAD_EXPLICIT_SCHED);
    if ( ret_inheritsched) {
		DTStamp(); printf("(6) %m: pthread setsinheritsched failed. ret_inheritsched = %d \n", ret_inheritsched);
    } else {
		DTStamp(); printf("(6) %m: pthread setsinheritsched success. ret_inheritsched = %d \n", ret_inheritsched);
	}

}
// ========================================================

