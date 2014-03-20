#include "types.h"
#include "keyboard.h"
#include "assembly_util.h"

static struct keyboard_status keyboard_manager;

static struct keyboard_map keyboard_map_table[] = 
{
	/*	normal		combined		code	*/
	{	KEY_NONE,	KEY_NONE	},	/*	0	*/
	{	KEY_ESC,	KEY_ESC		},	/*	1	*/
	{	'1',		'!'			},	/*	2	*/
	{	'2',		'@'			},	/*	3	*/
	{	'3',		'#'			},	/*	4	*/
	{	'4',		'$'			},	/*	5	*/
	{	'5',		'%'			},	/*	6	*/
	{	'6',		'^'			},	/*	7	*/
	{	'7',		'&'			},	/*	8	*/
	{	'8',		'*'			},	/*	9	*/
	{	'9',		'('			},	/*	A	*/
	{	'0',		')'			},	/*	B	*/
	{	'-',		'_'			},	/*	C	*/
	{	'=',		'+'			},	/*	D	*/
	{	KEY_BS,		KEY_BS		},	/*	E	*/
	{	KEY_TAB,	KEY_TAB		},	/*	F	*/
	{	'q',		'Q'			},	/*	10	*/
	{	'w',		'W'			},	/*	11	*/
	{	'e',		'E'			},	/*	12	*/
	{	'r',		'R'			},	/*	13	*/
	{	't',		'T'			},	/*	14	*/
	{	'y',		'Y'			},	/*	15	*/
	{	'u',		'U'			},	/*	16	*/
	{	'i',		'I'			},	/*	17	*/
	{	'o',		'O'			},	/*	18	*/
	{	'p',		'P'			},	/*	19	*/
	{	'[',		'{'			},	/*	1A	*/
	{	']',		'}'			},	/*	1B	*/
	{	KEY_ENTER,	KEY_ENTER	},	/*	1C	*/
	{	KEY_CTRL,	KEY_CTRL	},	/*	1D	*/
	{	'a',		'A'			},	/*	1E	*/
	{	's',		'S'			},	/*	1F	*/
	{	'd',		'D'			},	/*	20	*/
	{	'f',		'F'			},	/*	21	*/
	{	'g',		'G'			},	/*	22	*/
	{	'h',		'H'			},	/*	23	*/
	{	'j',		'J'			},	/*	24	*/
	{	'k',		'K'			},	/*	25	*/
	{	'l',		'L'			},	/*	26	*/
	{	';',		':'			},	/*	27	*/
	{	'\'',		'\"'		},	/*	28	*/
	{	'`',		'~'			},	/*	29	*/
	{	KEY_LSHIFT,	KEY_LSHIFT	},	/*	2A	*/
	{	'\\',		'|'			},	/*	2B	*/
	{	'z',		'Z'			},	/*	2C	*/
	{	'x',		'X'			},	/*	2D	*/
	{	'c',		'C'			},	/*	2E	*/
	{	'v',		'V'			},	/*	2F	*/
	{	'b',		'B'			},	/*	30	*/
	{	'n',		'N'			},	/*	31	*/
	{	'm',		'M'			},	/*	32	*/
	{	',',		'<'			},	/*	33	*/
	{	'.',		'>'			},	/*	34	*/
	{	'/',		'?'			},	/*	35	*/
	{	KEY_RSHIFT,	KEY_RSHIFT	},	/*	36	*/
	{	KEY_PS,		KEY_PS		},	/*	37	*/
	{	KEY_LALT,	KEY_LALT	},	/*	38	*/
	{	KEY_SPACE,	KEY_SPACE	},	/*	39	*/
	{	KEY_CAPS,	KEY_CAPS	},	/*	3A	*/
	{	KEY_F1,		KEY_F1		},	/*	3B	*/
	{	KEY_F2,		KEY_F2		},	/*	3C	*/
	{	KEY_F3,		KEY_F3		},	/*	3D	*/
	{	KEY_F4,		KEY_F4		},	/*	3E	*/
	{	KEY_F5,		KEY_F5		},	/*	3F	*/
	{	KEY_F6,		KEY_F6		},	/*	40	*/
	{	KEY_F7,		KEY_F7		},	/*	41	*/
	{	KEY_F8,		KEY_F8		},	/*	42	*/
	{	KEY_F9,		KEY_F9		},	/*	43	*/
	{	KEY_F10,	KEY_F10		},	/*	44	*/
	{	KEY_NUM,	KEY_NUM		},	/*	45	*/
	{	KEY_SCROLL,	KEY_SCROLL	},	/*	46	*/
	{	KEY_PAD_HOME,	'7'		},	/*	47	*/
	{	KEY_PAD_UP,		'8'		},	/*	48	*/
	{	KEY_PAD_PGUP,	'9'		},	/*	49	*/
	{	'-',		'-'			},	/*	4A	*/
	{	KEY_PAD_LEFT,	'4'		},	/*	4B	*/
	{	KEY_PAD_CENTER,	'5'		},	/*	4C	*/
	{	KEY_PAD_RIGHT,	'6'		},	/*	4D	*/
	{	'+',		'+'			},	/*	4E	*/
	{	KEY_PAD_END,	'1'		},	/*	4F	*/
	{	KEY_PAD_DOWN,	'2'		},	/*	50	*/
	{	KEY_PAD_PGDN,	'3'		},	/*	51	*/
	{	KEY_INSERT,	KEY_INSERT	},	/*	52	*/
	{	KEY_DELETE,	KEY_DELETE	},	/*	53	*/
	{	KEY_F11,	KEY_F11		},	/*	57	*/
	{	KEY_F12,	KEY_F12		},	/*	58	*/
	{	KEY_PAD_ENTER,	KEY_PAD_ENTER	},	/*	E0 1C	*/
	{	KEY_RCTRL,	KEY_RCTRL	},	/*	E0 1D	*/
	{	'/',		'/'			},	/*	E0 35	*/
	{	KEY_RALT,	KEY_RALT	},	/*	E0 38	*/
	{	KEY_HOME,	KEY_HOME	},	/*	E0 47	*/
	{	KEY_UP,		KEY_UP		},	/*	E0 48	*/
	{	KEY_PGUP,	KEY_PGUP	},	/*	E0 49	*/
	{	KEY_LEFT,	KEY_LEFT	},	/*	E0 4B	*/
	{	KEY_RIGHT,	KEY_RIGHT	},	/*	E0 4D	*/
	{	KEY_END,	KEY_END		},	/*	E0 4F	*/
	{	KEY_DOWN,	KEY_DOWN	},	/*	E0 50	*/
	{	KEY_PGDN,	KEY_PGDN	},	/*	E0 51	*/
	{	KEY_PAD_INSERT,	'0'		},	/*	E0 52	*/
	{	KEY_PAD_DELETE,	'.'		},	/*	E0 53	*/
	{	KEY_PAUSE,	KEY_PAUSE	}	/*	E1 1D 45*/
};

BOOL
is_keyboard_input_buffer_full(void)
{
	if (keyboard_read(KEYBOARD_CONTROL_REGISTER) & INPB)
		return TRUE;
	else
		return FALSE;
}

BOOL
is_keyboard_output_buffer_full(void)
{
	if (keyboard_read(KEYBOARD_CONTROL_REGISTER) & OUTB)
		return TRUE;
	else
		return FALSE;
}

BOOL
activate_keyboard(void)
{
	int i, j;

	keyboard_write(KEYBOARD_CONTROL_REGISTER, CONTROLLER_ACTIVATE_KEYBOARD);

	for (i=0 ; i<0xffff ; i++ )
		if (!is_keyboard_input_buffer_full())
			break;

	keyboard_write(KEYBOARD_BUFFER, KEYBOARD_ACTIVATE_KEYBOARD);

	for (i=0 ; i<MAX_READ_DATA ; i++)
	{
		for (j=0 ; j<0xffff ; j++ )
			if (!is_keyboard_input_buffer_full())
				break;

		if (keyboard_read(KEYBOARD_BUFFER) == KEYBOARD_ACK)
			return TRUE;
	}

	return FALSE;
}

BYTE
get_keyboard_scan_code(void)
{
	while (!is_keyboard_output_buffer_full());

	return keyboard_read(KEYBOARD_BUFFER);
}

BOOL
change_keyboard_led(BOOL num_lock, BOOL caps_lock, BOOL scroll_lock)
{
	int i;

	while (!is_keyboard_input_buffer_full());

	keyboard_write(KEYBOARD_BUFFER, KEYBOARD_CHANGE_LED);

	for (i=0 ; i<MAX_READ_DATA ; i++)
	{
		while (is_keyboard_input_buffer_full());

		if (keyboard_read(KEYBOARD_BUFFER) == KEYBOARD_ACK)
		{
			keyboard_write(KEYBOARD_BUFFER, (caps_lock << 2) | (num_lock << 1) | scroll_lock);

			for (i=0 ; i<MAX_READ_DATA ; i++)
			{
				while (is_keyboard_input_buffer_full());

				if (keyboard_read(KEYBOARD_BUFFER) == KEYBOARD_ACK)
					return TRUE;
			}
		}
	}

	return FALSE;
}

/* alphabet key may be effected by shift or caps lock key */
BOOL
is_alphabet_key(BYTE scan_code)
{
	if (keyboard_map_table[scan_code].normal_code >= 'a' && keyboard_map_table[scan_code].normal_code <= 'z')
		return TRUE;
	else
		return FALSE;
}

/* number key may be effected by shift key */
BOOL
is_number_key(BYTE scan_code)
{
	if (scan_code >= 0x02 && scan_code <= 0x0b)
		return TRUE;
	else
		return FALSE;
}

/* symbol key may be effected by shift key */
BOOL
is_symbol_key(BYTE scan_code)
{
	if ((scan_code >= 0x0c && scan_code <= 0x0d) || (scan_code >= 0x1a && scan_code <= 0x1b) || (scan_code >= 0x27 && scan_code <= 0x29) || scan_code ==0x2b)
		return TRUE;
	else
		return FALSE;
}

/* number pad key may be effected by num lock key */
BOOL
is_num_pad_key(BYTE scan_code)
{
	if ((scan_code >= 0x47 && scan_code <= 0x49) || (scan_code >= 0x4b && scan_code <= 0x4d) || (scan_code >= 0x4f && scan_code <= 0x51))
		return TRUE;
	else
		return FALSE;
}

void
update_keyboard_status(BYTE scan_code)
{
	BOOL is_key_down;
	BOOL changed_lock_status = FALSE;

	if (scan_code & 0x80)
		is_key_down = FALSE;
	else
		is_key_down = TRUE;

	if (keyboard_map_table[scan_code].normal_code == KEY_RSHIFT || keyboard_map_table[scan_code].normal_code == KEY_LSHIFT)
		if (is_key_down)
			keyboard_manager.is_shift_down = TRUE;
		else
			keyboard_manager.is_shift_down = FALSE;

	if (keyboard_map_table[scan_code].normal_code == KEY_CAPS)
	{
		changed_lock_status = TRUE;
		if (is_key_down)
			keyboard_manager.is_caps_lock_on = TRUE;
		else
			keyboard_manager.is_caps_lock_on = FALSE;
	}

	if (keyboard_map_table[scan_code].normal_code == KEY_NUM)
	{
		changed_lock_status = TRUE;
		if (is_key_down)
			keyboard_manager.is_num_lock_on = TRUE;
		else
			keyboard_manager.is_num_lock_on = FALSE;
	}

	if (keyboard_map_table[scan_code].normal_code == KEY_SCROLL)
	{
		changed_lock_status = TRUE;
		if (is_key_down)
			keyboard_manager.is_scroll_lock_on = TRUE;
		else
			keyboard_manager.is_scroll_lock_on = FALSE;
	}

	if (changed_lock_status)
		change_keyboard_led(keyboard_manager.is_num_lock_on, keyboard_manager.is_caps_lock_on, keyboard_manager.is_scroll_lock_on);
}

BOOL
convert_scan_code_to_ascii_code(BYTE scan_code, BYTE *ascii_code, BOOL *key_status)
{
	if (keyboard_manager.is_pause_key)
	{
		if (keyboard_manager.is_pause_key == 1)
			keyboard_manager.is_pause_key = 2;
		else
			keyboard_manager.is_pause_key = 0;

		return FALSE;
	}

	if (scan_code == 0xe1)
	{
		keyboard_manager.is_pause_key = 1;
		*ascii_code = KEY_PAUSE;
		*key_status = KEY_FLAGS_DOWN;

		return TRUE;
	}
	else if (scan_code == 0xe0)
	{
		*key_status = KEY_FLAGS_EXTENDED;

		return FALSE;
	}

	if ((keyboard_manager.is_shift_down && (is_alphabet_key(scan_code)) || is_number_key(scan_code) || is_symbol_key(scan_code)) || (keyboard_manager.is_caps_lock_on && is_alphabet_key(scan_code)) || (keyboard_manager.is_num_lock_on && is_num_pad_key(scan_code)))
		*ascii_code = keyboard_map_table[scan_code].combined_code;
	else
		*ascii_code = keyboard_map_table[scan_code].normal_code;

	if (scan_code & 0x80)
		*key_status = KEY_FLAGS_UP;
	else
		*key_status = KEY_FLAGS_DOWN;

	update_keyboard_status(scan_code);

	return TRUE;
}
