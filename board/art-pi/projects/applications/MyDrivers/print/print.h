#ifndef __PRINT_H
#define __PRINT_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>

#define USE_RT_PRINT    0

#if USE_RT_PRINT
extern void rt_kprintf(const char *fmt, ...);
#define print rt_kprintf
#endif

#ifdef __cplusplus
}
#endif

#endif
