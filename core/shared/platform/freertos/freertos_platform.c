/*
 * Copyright (C) 2019 Intel Corporation.  All rights reserved.
 * SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
 */

#include "platform_api_vmcore.h"
#include "platform_api_extension.h"

int
bh_platform_init()
{
    return 0;
}

void
bh_platform_destroy()
{}

int
os_printf(const char *format, ...)
{
    int ret = 0;
    va_list ap;

    va_start(ap, format);
    ret += vprintf(format, ap);
    va_end(ap);

    return ret;
}

int
os_vprintf(const char *format, va_list ap)
{
    return vprintf(format, ap);
}

uint64
os_time_get_boot_microsecond(void)
{
    return 0;
}

uint8 *
os_thread_get_stack_boundary(void)
{
#if defined(CONFIG_FREERTOS_USE_TRACE_FACILITY)
    TaskStatus_t pxTaskStatus;
    vTaskGetInfo(xTaskGetCurrentTaskHandle(), &pxTaskStatus, pdTRUE, eInvalid);
    return pxTaskStatus.pxStackBase;
#else // !defined(CONFIG_FREERTOS_USE_TRACE_FACILITY)
    return NULL;
#endif
}

void
os_thread_jit_write_protect_np(bool enabled)
{}

int
os_usleep(uint32 usec)
{
    return usleep(usec);
}


int
openat(int fd, const char *path, int oflags, ...)
{
    errno = ENOSYS;
    return -1;
}

int
fstatat(int fd, const char *path, struct stat *buf, int flag)
{
    errno = ENOSYS;
    return -1;
}

int
mkdirat(int fd, const char *path, mode_t mode)
{
    errno = ENOSYS;
    return -1;
}

ssize_t
readlinkat(int fd, const char *path, char *buf, size_t bufsize)
{
    errno = EINVAL;
    return -1;
}

int
linkat(int fd1, const char *path1, int fd2, const char *path2, int flag)
{
    errno = ENOSYS;
    return -1;
}

int
renameat(int fromfd, const char *from, int tofd, const char *to)
{
    errno = ENOSYS;
    return -1;
}

int
symlinkat(const char *target, int fd, const char *path)
{
    errno = ENOSYS;
    return -1;
}

int
unlinkat(int fd, const char *path, int flag)
{
    errno = ENOSYS;
    return -1;
}

int
utimensat(int fd, const char *path, const struct timespec *ts, int flag)
{
    errno = ENOSYS;
    return -1;
}

DIR *
fdopendir(int fd)
{
    errno = ENOSYS;
    return NULL;
}

int
ftruncate(int fd, off_t length)
{
    errno = ENOSYS;
    return -1;
}

int
futimens(int fd, const struct timespec *times)
{
    errno = ENOSYS;
    return -1;
}

int
nanosleep(const struct timespec *req, struct timespec *rem)
{
    errno = ENOSYS;
    return -1;
}