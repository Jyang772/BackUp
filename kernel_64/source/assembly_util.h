#ifndef __ASSEMBLYUTILITY_H__
#define __ASSEMBLYUTILITY_H__

#include "types.h"

BYTE keyboard_read(WORD port);
BYTE keyboard_write(WORD port, BYTE data);

#endif
