#ifndef	__MODE_SWITCH_H__
#define __MODE_SWITCH_H__

#include "types.h"

void read_cpuid(DWORD input, DWORD *eax, DWORD *ebx, DWORD *ecx, DWORD *edx);
void switch_kernel_64(void);

#endif
