/*
 * Copyright (C) 2019 Intel Corporation.  All rights reserved.
 * SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
 */

#include "platform_api_vmcore.h"
#include "platform_api_extension.h"
#if (WASM_MEM_DUAL_BUS_MIRROR != 0)
#include "soc/mmu.h"
#include "rom/cache.h"

#define MEM_DUAL_BUS_OFFSET (IRAM0_CACHE_ADDRESS_LOW - DRAM0_CACHE_ADDRESS_LOW)

#define in_ibus_ext(addr)                      \
    (((uint32)addr >= IRAM0_CACHE_ADDRESS_LOW) \
     && ((uint32)addr < IRAM0_CACHE_ADDRESS_HIGH))

static portMUX_TYPE s_spinlock = portMUX_INITIALIZER_UNLOCKED;
#endif

void *
os_mmap(void *hint, size_t size, int prot, int flags, os_file_handle file)
{
    return NULL;
}

void
os_munmap(void *addr, size_t size)
{

}

int
os_mprotect(void *addr, size_t size, int prot)
{
    return 0;
}

void os_dcache_flush()
{

}

void
os_icache_flush(void *start, size_t len)
{}

