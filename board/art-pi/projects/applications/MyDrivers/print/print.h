#ifndef __PRINT_H
#define __PRINT_H

#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

extern void rt_kprintf(const char *fmt, ...);
#define print rt_kprintf

#ifdef __cplusplus
}
#endif

#endif
