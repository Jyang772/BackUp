#include "page.h"

BOOL
initialize_page_table(void)
{
	struct page_table_entry *entry = (struct page_table_entry *)0x100000;

	int i;

	/* set PML4 table */
	entry->lower_entry = 0x101000 | PAGE_FLAGS_P | PAGE_FLAGS_RW;
	entry->upper_entry = 0;
	entry++;

	for (i=1 ; i<512 ; i++)
	{
		entry->lower_entry = 0;
		entry->upper_entry = 0;
		entry++;
	}

	/* set page directory pointer table */
	entry = (struct page_table_entry *)0x101000;

	entry->lower_entry = 0x102000 | PAGE_FLAGS_P | PAGE_FLAGS_RW;
	entry->upper_entry = 0;
	entry++;

	for (i=1 ; i<64 ; i++)
	{
		entry->lower_entry = (0x102000 + i * (1 << 12)) | PAGE_FLAGS_P | PAGE_FLAGS_RW;
		entry->upper_entry = 0;
		entry++;
	}

	for (i=64 ; i<512 ; i++)
	{
		entry->lower_entry = 0;
		entry->upper_entry = 0;
		entry++;
	}

	/* set page directory table */
	entry = (struct page_table_entry *)0x102000;

	for (i=0 ; i<512 * 64 ; i++)
	{
		entry->lower_entry = (0x200000 * i) | PAGE_FLAGS_P | PAGE_FLAGS_RW | PAGE_FLAGS_PS;
		entry->upper_entry = (0x200000 * i) >> 32;
		entry++;
	}
}
