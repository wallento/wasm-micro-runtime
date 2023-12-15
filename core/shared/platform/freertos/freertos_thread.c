/*
 * Copyright (C) 2019 Intel Corporation.  All rights reserved.
 * SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
 */

#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif

#include "platform_api_vmcore.h"
#include "platform_api_extension.h"

typedef struct {
    thread_start_routine_t start;
    void *arg;
} thread_wrapper_arg;

static void *
os_thread_wrapper(void *arg)
{
    thread_wrapper_arg *targ = arg;
    thread_start_routine_t start_func = targ->start;
    void *thread_arg = targ->arg;

#if 0
    os_printf("THREAD CREATED %jx\n", (uintmax_t)(uintptr_t)pthread_self());
#endif
    BH_FREE(targ);
    start_func(thread_arg);
    return NULL;
}

korp_tid
os_self_thread(void)
{
    /* only allowed if this is a thread, xTaskCreate is not enough look at
     * product_mini for how to use this*/

}

int
os_mutex_init(korp_mutex *mutex)
{
    return 0;
}

int
os_recursive_mutex_init(korp_mutex *mutex)
{
    return BHT_OK;
}

int
os_mutex_destroy(korp_mutex *mutex)
{
    return 0;
}

int
os_mutex_lock(korp_mutex *mutex)
{
    return 0;
}

int
os_mutex_unlock(korp_mutex *mutex)
{
    return 0;
}

int
os_thread_create_with_prio(korp_tid *tid, thread_start_routine_t start,
                           void *arg, unsigned int stack_size, int prio)
{

    return BHT_OK;
}

int
os_thread_create(korp_tid *tid, thread_start_routine_t start, void *arg,
                 unsigned int stack_size)
{
    return os_thread_create_with_prio(tid, start, arg, stack_size,
                                      BH_THREAD_DEFAULT_PRIORITY);
}

int
os_thread_join(korp_tid thread, void **retval)
{
    return 0;
}

int
os_thread_detach(korp_tid tid)
{
    return 0;
}

void
os_thread_exit(void *retval)
{

}

int
os_cond_init(korp_cond *cond)
{
    return pthread_cond_init(cond, NULL);
}

int
os_cond_destroy(korp_cond *cond)
{
    return pthread_cond_destroy(cond);
}

int
os_cond_wait(korp_cond *cond, korp_mutex *mutex)
{
    return pthread_cond_wait(cond, mutex);
}

static void
msec_nsec_to_abstime(struct timespec *ts, uint64 usec)
{
    struct timeval tv;
    time_t tv_sec_new;
    long int tv_nsec_new;

    gettimeofday(&tv, NULL);

    tv_sec_new = (time_t)(tv.tv_sec + usec / 1000000);
    if (tv_sec_new >= tv.tv_sec) {
        ts->tv_sec = tv_sec_new;
    }
    else {
        /* integer overflow */
        ts->tv_sec = BH_TIME_T_MAX;
        os_printf("Warning: os_cond_reltimedwait exceeds limit, "
                  "set to max timeout instead\n");
    }

    tv_nsec_new = (long int)(tv.tv_usec * 1000 + (usec % 1000000) * 1000);
    if (tv.tv_usec * 1000 >= tv.tv_usec && tv_nsec_new >= tv.tv_usec * 1000) {
        ts->tv_nsec = tv_nsec_new;
    }
    else {
        /* integer overflow */
        ts->tv_nsec = LONG_MAX;
        os_printf("Warning: os_cond_reltimedwait exceeds limit, "
                  "set to max timeout instead\n");
    }

    if (ts->tv_nsec >= 1000000000L && ts->tv_sec < BH_TIME_T_MAX) {
        ts->tv_sec++;
        ts->tv_nsec -= 1000000000L;
    }
}

int
os_cond_reltimedwait(korp_cond *cond, korp_mutex *mutex, uint64 useconds)
{
    int ret;
    struct timespec abstime;

    if (useconds == BHT_WAIT_FOREVER)
        ret = pthread_cond_wait(cond, mutex);
    else {
        msec_nsec_to_abstime(&abstime, useconds);
        ret = pthread_cond_timedwait(cond, mutex, &abstime);
    }

    if (ret != BHT_OK && ret != ETIMEDOUT)
        return BHT_ERROR;

    return ret;
}

int
os_cond_signal(korp_cond *cond)
{
    return pthread_cond_signal(cond);
}

int
os_cond_broadcast(korp_cond *cond)
{
    return pthread_cond_broadcast(cond);
}