#include "types.h"
#include "page.h"
#include "mode_switch.h"

void 	printk(int x, int y, const char* string);

BOOL	check_memory_size(void);
BOOL	initialize_kernel_64_area(void);
BOOL	copy_kernel_64_image(void);

void main(void)
{
	DWORD eax, ebx, ecx, edx;
	BYTE manufacturer_name[13];

	printk(0, 4, "Protected Mode C Kernel Loading........[Pass]");

	printk(0, 5, "Memory Size Check......................[    ]");
	if (!check_memory_size())
	{
		printk(40, 5, "Fail");
		printk(0, 6, "SOS requires more than 64MB memory.");

		while (TRUE);
	}
	else
		printk(40, 5, "Pass");

	printk(0, 6, "IA-32e Kernel Area Initialization......[    ]");
	if (!initialize_kernel_64_area())
	{
		printk(40, 6, "Fail");

		while (TRUE);
	}
	else
		printk(40, 6, "Pass");

	printk(0, 7, "Page Table Initialization..............[    ]");
	initialize_page_table();
	printk(40, 7, "Pass");

	printk(0, 7, "Processor Checking.....................[            ]");
	read_cpuid(0x00000000, &eax, &ebx, &ecx, &edx); 

	*((DWORD *)manufacturer_name) = ebx;
	*((DWORD *)manufacturer_name + 1) = edx;
	*((DWORD *)manufacturer_name + 2) = ecx;
	manufacturer_name[12] = 0;

	printk(40, 7, manufacturer_name);

	printk(0, 8, "64-bit Support Checking................[    ]");
	read_cpuid(0x80000001, &eax, &ebx, &ecx, &edx); 

	if ((edx >> 29) & 0x1)
		printk(40, 8, "Pass");
	else
	{
		printk(40, 8, "Fail");
		printk(0, 9, "This processor doesn't support 64-bit mode.");

		while (TRUE);
	}

	printk(0, 9, "64-bit Kernel Image Copying............[    ]");
	if (!copy_kernel_64_image())
	{
		printk(40, 9, "Fail");

		while (TRUE);
	}
	else
		printk(40, 9, "Pass");

	printk(0, 10, "Switching to IA-32e Mode...............[    ]");
	switch_kernel_64();

	while (TRUE);
}

void
printk(int x, int y, const char* string)
{
	struct video_mode_character *screen = (struct video_mode_character *)0xb8000;

	int i;

	screen += (y * 80) + x;

	for (i=0 ; string[i]!=0 ; i++)
		screen[i].character = string[i];
}

BOOL
check_memory_size(void)
{
	DWORD *check_pointer = (DWORD *)0x100000;

	while ( (DWORD)check_pointer < 0x4000000 )
	{
		*check_pointer = 0x12345678;

		if ( *check_pointer != 0x12345678 )
			return FALSE;

		check_pointer += 0x100000 / 4;
	}

	return TRUE;
}

BOOL
initialize_kernel_64_area(void)
{
	DWORD *area_pointer = (DWORD *)0x100000;

	while ( (DWORD)area_pointer < 0x600000 )
	{
		*area_pointer = 0x00;

		if ( *area_pointer != 0x00 )
			return FALSE;

		area_pointer++;
	}

	return TRUE;
}

BOOL
copy_kernel_64_image(void)
{
	WORD total_sector_number = *((WORD *)0x7c05);
	WORD kernel_32_sector_number = *((WORD *)0x7c07);
	
	int kernel_64_size = (total_sector_number - kernel_32_sector_number) * 512;

	BYTE *kernel_64_image_area = (BYTE *)(0x10000 + kernel_32_sector_number * 512);
	BYTE *kernel_64_area = (BYTE *)0x200000;

	int i;

	for (i=0 ; i<kernel_64_size ; i++)
	{
		kernel_64_area[i] = kernel_64_image_area[i];

		if (kernel_64_area[i] != kernel_64_image_area[i])
			return FALSE;
	}

	return TRUE;
}
