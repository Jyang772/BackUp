#ifndef	__KEYBOARD_H__
#define __KEYBOARD_H__

#include "types.h"

#define KEYBOARD_CONTROL_REGISTER		0x64
#define KEYBOARD_BUFFER				0x60

#define OUTB					0x01
#define INPB					0x02

#define CONTROLLER_ACTIVATE_KEYBOARD		0xa8

#define	KEYBOARD_ACTIVATE_KEYBOARD		0xf4
#define	KEYBOARD_CHANGE_LED			0xf4
#define	KEYBOARD_ACK				0xf4

#define	MAX_READ_DATA				100

#define	KEY_FLAGS_UP				0x00
#define	KEY_FLAGS_DOWN				0x01
#define	KEY_FLAGS_EXTENDED			0x02

#define	KEY_NONE				0x00
#define KEY_ESC					0x1b
#define	KEY_BS					0x08
#define	KEY_TAB					'\t'	
#define	KEY_ENTER				'\n'	
#define	KEY_CTRL				0x70
#define	KEY_LSHIFT				0x71
#define	KEY_RSHIFT				0x72
#define	KEY_PS					0x73
#define	KEY_LALT				0x74
#define KEY_SPACE				0x75
#define KEY_CAPS				0x76
#define KEY_F1					0x77
#define KEY_F2					0x78
#define KEY_F3					0x79
#define KEY_F4					0x80
#define KEY_F5					0x8A
#define KEY_F6					0x8B
#define KEY_F7					0x8C
#define KEY_F8					0x8D
#define KEY_F9					0x8E
#define KEY_F10					0x8F
#define KEY_NUM					0x90
#define KEY_SCROLL				0x91
#define KEY_PAD_HOME				0x92
#define KEY_PAD_UP				0x93
#define KEY_PAD_PGUP				0x94
#define KEY_PAD_LEFT 				0x95
#define KEY_PAD_CENTER				0x96
#define KEY_PAD_RIGHT				0x97
#define KEY_PAD_END 				0x98
#define KEY_PAD_DOWN				0x99
#define KEY_PAD_PGDN				0x90
#define KEY_INSERT				0x9A
#define KEY_DELETE				0x9B
#define KEY_F11					0x9C
#define KEY_F12					0x9D
#define KEY_PAD_ENTER				0x9E
#define KEY_RCTRL				0x9F
#define KEY_RALT				0xA0
#define KEY_HOME				0xA1
#define KEY_UP					0xA2
#define KEY_PGUP				0xA3
#define KEY_LEFT				0xA4
#define KEY_RIGHT				0xA5
#define KEY_END					0xA6
#define KEY_DOWN				0xA7
#define KEY_PGDN				0xA8
#define KEY_PAD_INSERT				0xA9
#define KEY_PAD_DELETE				0xA0
#define KEY_PAUSE				0xAA

#pragma pack(push, 1)

struct keyboard_map
{
	BYTE	normal_code;
	BYTE	combined_code;
};

#pragma pack(pop)

struct keyboard_status
{
	BOOL is_shift_down;
	BOOL is_caps_lock_on;
	BOOL is_num_lock_on;
	BOOL is_scroll_lock_on;

	BOOL is_extended_key;
	int  is_pause_key;
};

BOOL is_keyboard_input_buffer_full(void);
BOOL is_keyboard_output_buffer_full(void);
BOOL activate_keyboard(void);
BYTE get_keyboard_scan_code(void);
BOOL change_keyboard_led(BOOL num_lock, BOOL caps_lock, BOOL scroll_lock);
BOOL is_alphabet_key(BYTE scan_code);
BOOL is_number_key(BYTE scan_code);
BOOL is_symbol_key(BYTE scan_code);
BOOL is_num_pad_key(BYTE scan_code);
void update_keyboard_status(BYTE scan_code);
BOOL convert_scan_code_to_ascii_code(BYTE scan_code, BYTE *ascii_code, BOOL *key_status);

#endif                                     
