#include "types.h"
#include "keyboard.h"

void 	printk(int x, int y, const char* string);

void main(void)
{
	BYTE scan_code,ascii_code,flag;
	int i = 0;

	printk(40, 10, "Pass");
	printk(0, 11, "IA-32e Mode C Kernel Loading...........[Pass]");
	printk(0, 12, "Keyboard Activation....................[    ]");

	/*
	if (activate_keyboard())
	{
		printk(40, 12, "Pass");
		change_keyboard_led(FALSE, FALSE, FALSE);
	}
	else
	{
		printk(40, 12, "Fail");
		while (TRUE);
	}

	while (is_keyboard_output_buffer_full())
	{
		scan_code = get_keyboard_scan_code();

		if (convert_scan_code_to_ascii_code(scan_code, &ascii_code, &flag))
			printk(i++, 13, &ascii_code);
	}
	*/
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
