#ifndef	__PAGE_H__
#define	__PAGE_H__

#include "types.h"

#define	PAGE_FLAGS_P	0x00000001
#define	PAGE_FLAGS_RW	0x00000002
#define	PAGE_FLAGS_US	0x00000004
#define	PAGE_FLAGS_PWT	0x00000008
#define	PAGE_FLAGS_PCD	0x00000010
#define	PAGE_FLAGS_A	0x00000020
#define	PAGE_FLAGS_D	0x00000040
#define	PAGE_FLAGS_PS	0x00000080
#define	PAGE_FLAGS_G	0x00000100
#define	PAGE_FLAGS_PAT	0x00001000
#define	PAGE_FLAGS_EXB	0x80000000

#pragma pack(push, 1)

struct page_table_entry
{
	DWORD	lower_entry;
	DWORD	upper_entry;
};

#pragma pack(pop)

BOOL	initialize_page_table(void);

#endif
