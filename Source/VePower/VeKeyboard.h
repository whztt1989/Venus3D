////////////////////////////////////////////////////////////////////////////
//
//  Venus Engine Header File.
//  Copyright (C), Venus Interactive Entertainment.2012
// -------------------------------------------------------------------------
//  Module:      VePower
//  File name:   VeKeyboard.h
//  Created:     2015/08/07 by Napoleon
//  Description: 
// -------------------------------------------------------------------------
//  History:
//  http://www.venusie.com
////////////////////////////////////////////////////////////////////////////

#pragma once

enum VeScancode
{
	VE_SCANCODE_UNKNOWN = 0,

	VE_SCANCODE_A = 4,
	VE_SCANCODE_B = 5,
	VE_SCANCODE_C = 6,
	VE_SCANCODE_D = 7,
	VE_SCANCODE_E = 8,
	VE_SCANCODE_F = 9,
	VE_SCANCODE_G = 10,
	VE_SCANCODE_H = 11,
	VE_SCANCODE_I = 12,
	VE_SCANCODE_J = 13,
	VE_SCANCODE_K = 14,
	VE_SCANCODE_L = 15,
	VE_SCANCODE_M = 16,
	VE_SCANCODE_N = 17,
	VE_SCANCODE_O = 18,
	VE_SCANCODE_P = 19,
	VE_SCANCODE_Q = 20,
	VE_SCANCODE_R = 21,
	VE_SCANCODE_S = 22,
	VE_SCANCODE_T = 23,
	VE_SCANCODE_U = 24,
	VE_SCANCODE_V = 25,
	VE_SCANCODE_W = 26,
	VE_SCANCODE_X = 27,
	VE_SCANCODE_Y = 28,
	VE_SCANCODE_Z = 29,

	VE_SCANCODE_1 = 30,
	VE_SCANCODE_2 = 31,
	VE_SCANCODE_3 = 32,
	VE_SCANCODE_4 = 33,
	VE_SCANCODE_5 = 34,
	VE_SCANCODE_6 = 35,
	VE_SCANCODE_7 = 36,
	VE_SCANCODE_8 = 37,
	VE_SCANCODE_9 = 38,
	VE_SCANCODE_0 = 39,

	VE_SCANCODE_RETURN = 40,
	VE_SCANCODE_ESCAPE = 41,
	VE_SCANCODE_BACKSPACE = 42,
	VE_SCANCODE_TAB = 43,
	VE_SCANCODE_SPACE = 44,

	VE_SCANCODE_MINUS = 45,
	VE_SCANCODE_EQUALS = 46,
	VE_SCANCODE_LEFTBRACKET = 47,
	VE_SCANCODE_RIGHTBRACKET = 48,
	VE_SCANCODE_BACKSLASH = 49,
	VE_SCANCODE_NONUSHASH = 50, 
	VE_SCANCODE_SEMICOLON = 51,
	VE_SCANCODE_APOSTROPHE = 52,
	VE_SCANCODE_GRAVE = 53,
	VE_SCANCODE_COMMA = 54,
	VE_SCANCODE_PERIOD = 55,
	VE_SCANCODE_SLASH = 56,

	VE_SCANCODE_CAPSLOCK = 57,

	VE_SCANCODE_F1 = 58,
	VE_SCANCODE_F2 = 59,
	VE_SCANCODE_F3 = 60,
	VE_SCANCODE_F4 = 61,
	VE_SCANCODE_F5 = 62,
	VE_SCANCODE_F6 = 63,
	VE_SCANCODE_F7 = 64,
	VE_SCANCODE_F8 = 65,
	VE_SCANCODE_F9 = 66,
	VE_SCANCODE_F10 = 67,
	VE_SCANCODE_F11 = 68,
	VE_SCANCODE_F12 = 69,

	VE_SCANCODE_PRINTSCREEN = 70,
	VE_SCANCODE_SCROLLLOCK = 71,
	VE_SCANCODE_PAUSE = 72,
	VE_SCANCODE_INSERT = 73,
	VE_SCANCODE_HOME = 74,
	VE_SCANCODE_PAGEUP = 75,
	VE_SCANCODE_DELETE = 76,
	VE_SCANCODE_END = 77,
	VE_SCANCODE_PAGEDOWN = 78,
	VE_SCANCODE_RIGHT = 79,
	VE_SCANCODE_LEFT = 80,
	VE_SCANCODE_DOWN = 81,
	VE_SCANCODE_UP = 82,

	VE_SCANCODE_NUMLOCKCLEAR = 83,
	VE_SCANCODE_KP_DIVIDE = 84,
	VE_SCANCODE_KP_MULTIPLY = 85,
	VE_SCANCODE_KP_MINUS = 86,
	VE_SCANCODE_KP_PLUS = 87,
	VE_SCANCODE_KP_ENTER = 88,
	VE_SCANCODE_KP_1 = 89,
	VE_SCANCODE_KP_2 = 90,
	VE_SCANCODE_KP_3 = 91,
	VE_SCANCODE_KP_4 = 92,
	VE_SCANCODE_KP_5 = 93,
	VE_SCANCODE_KP_6 = 94,
	VE_SCANCODE_KP_7 = 95,
	VE_SCANCODE_KP_8 = 96,
	VE_SCANCODE_KP_9 = 97,
	VE_SCANCODE_KP_0 = 98,
	VE_SCANCODE_KP_PERIOD = 99,

	VE_SCANCODE_NONUSBACKSLASH = 100,
	VE_SCANCODE_APPLICATION = 101,
	VE_SCANCODE_POWER = 102,
	VE_SCANCODE_KP_EQUALS = 103,
	VE_SCANCODE_F13 = 104,
	VE_SCANCODE_F14 = 105,
	VE_SCANCODE_F15 = 106,
	VE_SCANCODE_F16 = 107,
	VE_SCANCODE_F17 = 108,
	VE_SCANCODE_F18 = 109,
	VE_SCANCODE_F19 = 110,
	VE_SCANCODE_F20 = 111,
	VE_SCANCODE_F21 = 112,
	VE_SCANCODE_F22 = 113,
	VE_SCANCODE_F23 = 114,
	VE_SCANCODE_F24 = 115,
	VE_SCANCODE_EXECUTE = 116,
	VE_SCANCODE_HELP = 117,
	VE_SCANCODE_MENU = 118,
	VE_SCANCODE_SELECT = 119,
	VE_SCANCODE_STOP = 120,
	VE_SCANCODE_AGAIN = 121,   /**< redo */
	VE_SCANCODE_UNDO = 122,
	VE_SCANCODE_CUT = 123,
	VE_SCANCODE_COPY = 124,
	VE_SCANCODE_PASTE = 125,
	VE_SCANCODE_FIND = 126,
	VE_SCANCODE_MUTE = 127,
	VE_SCANCODE_VOLUMEUP = 128,
	VE_SCANCODE_VOLUMEDOWN = 129,
	
	VE_SCANCODE_KP_COMMA = 133,
	VE_SCANCODE_KP_EQUALSAS400 = 134,

	VE_SCANCODE_INTERNATIONAL1 = 135,
	VE_SCANCODE_INTERNATIONAL2 = 136,
	VE_SCANCODE_INTERNATIONAL3 = 137,
	VE_SCANCODE_INTERNATIONAL4 = 138,
	VE_SCANCODE_INTERNATIONAL5 = 139,
	VE_SCANCODE_INTERNATIONAL6 = 140,
	VE_SCANCODE_INTERNATIONAL7 = 141,
	VE_SCANCODE_INTERNATIONAL8 = 142,
	VE_SCANCODE_INTERNATIONAL9 = 143,
	VE_SCANCODE_LANG1 = 144,
	VE_SCANCODE_LANG2 = 145,
	VE_SCANCODE_LANG3 = 146,
	VE_SCANCODE_LANG4 = 147,
	VE_SCANCODE_LANG5 = 148,
	VE_SCANCODE_LANG6 = 149,
	VE_SCANCODE_LANG7 = 150,
	VE_SCANCODE_LANG8 = 151,
	VE_SCANCODE_LANG9 = 152,

	VE_SCANCODE_ALTERASE = 153,
	VE_SCANCODE_SYSREQ = 154,
	VE_SCANCODE_CANCEL = 155,
	VE_SCANCODE_CLEAR = 156,
	VE_SCANCODE_PRIOR = 157,
	VE_SCANCODE_RETURN2 = 158,
	VE_SCANCODE_SEPARATOR = 159,
	VE_SCANCODE_OUT = 160,
	VE_SCANCODE_OPER = 161,
	VE_SCANCODE_CLEARAGAIN = 162,
	VE_SCANCODE_CRSEL = 163,
	VE_SCANCODE_EXSEL = 164,

	VE_SCANCODE_KP_00 = 176,
	VE_SCANCODE_KP_000 = 177,
	VE_SCANCODE_THOUSANDSSEPARATOR = 178,
	VE_SCANCODE_DECIMALSEPARATOR = 179,
	VE_SCANCODE_CURRENCYUNIT = 180,
	VE_SCANCODE_CURRENCYSUBUNIT = 181,
	VE_SCANCODE_KP_LEFTPAREN = 182,
	VE_SCANCODE_KP_RIGHTPAREN = 183,
	VE_SCANCODE_KP_LEFTBRACE = 184,
	VE_SCANCODE_KP_RIGHTBRACE = 185,
	VE_SCANCODE_KP_TAB = 186,
	VE_SCANCODE_KP_BACKSPACE = 187,
	VE_SCANCODE_KP_A = 188,
	VE_SCANCODE_KP_B = 189,
	VE_SCANCODE_KP_C = 190,
	VE_SCANCODE_KP_D = 191,
	VE_SCANCODE_KP_E = 192,
	VE_SCANCODE_KP_F = 193,
	VE_SCANCODE_KP_XOR = 194,
	VE_SCANCODE_KP_POWER = 195,
	VE_SCANCODE_KP_PERCENT = 196,
	VE_SCANCODE_KP_LESS = 197,
	VE_SCANCODE_KP_GREATER = 198,
	VE_SCANCODE_KP_AMPERSAND = 199,
	VE_SCANCODE_KP_DBLAMPERSAND = 200,
	VE_SCANCODE_KP_VERTICALBAR = 201,
	VE_SCANCODE_KP_DBLVERTICALBAR = 202,
	VE_SCANCODE_KP_COLON = 203,
	VE_SCANCODE_KP_HASH = 204,
	VE_SCANCODE_KP_SPACE = 205,
	VE_SCANCODE_KP_AT = 206,
	VE_SCANCODE_KP_EXCLAM = 207,
	VE_SCANCODE_KP_MEMSTORE = 208,
	VE_SCANCODE_KP_MEMRECALL = 209,
	VE_SCANCODE_KP_MEMCLEAR = 210,
	VE_SCANCODE_KP_MEMADD = 211,
	VE_SCANCODE_KP_MEMSUBTRACT = 212,
	VE_SCANCODE_KP_MEMMULTIPLY = 213,
	VE_SCANCODE_KP_MEMDIVIDE = 214,
	VE_SCANCODE_KP_PLUSMINUS = 215,
	VE_SCANCODE_KP_CLEAR = 216,
	VE_SCANCODE_KP_CLEARENTRY = 217,
	VE_SCANCODE_KP_BINARY = 218,
	VE_SCANCODE_KP_OCTAL = 219,
	VE_SCANCODE_KP_DECIMAL = 220,
	VE_SCANCODE_KP_HEXADECIMAL = 221,

	VE_SCANCODE_LCTRL = 224,
	VE_SCANCODE_LSHIFT = 225,
	VE_SCANCODE_LALT = 226,
	VE_SCANCODE_LGUI = 227,
	VE_SCANCODE_RCTRL = 228,
	VE_SCANCODE_RSHIFT = 229,
	VE_SCANCODE_RALT = 230,
	VE_SCANCODE_RGUI = 231,

	VE_SCANCODE_MODE = 257,
	VE_SCANCODE_AUDIONEXT = 258,
	VE_SCANCODE_AUDIOPREV = 259,
	VE_SCANCODE_AUDIOSTOP = 260,
	VE_SCANCODE_AUDIOPLAY = 261,
	VE_SCANCODE_AUDIOMUTE = 262,
	VE_SCANCODE_MEDIASELECT = 263,
	VE_SCANCODE_WWW = 264,
	VE_SCANCODE_MAIL = 265,
	VE_SCANCODE_CALCULATOR = 266,
	VE_SCANCODE_COMPUTER = 267,
	VE_SCANCODE_AC_SEARCH = 268,
	VE_SCANCODE_AC_HOME = 269,
	VE_SCANCODE_AC_BACK = 270,
	VE_SCANCODE_AC_FORWARD = 271,
	VE_SCANCODE_AC_STOP = 272,
	VE_SCANCODE_AC_REFRESH = 273,
	VE_SCANCODE_AC_BOOKMARKS = 274,

	VE_SCANCODE_BRIGHTNESSDOWN = 275,
	VE_SCANCODE_BRIGHTNESSUP = 276,
	VE_SCANCODE_DISPLAYSWITCH = 277,
	VE_SCANCODE_KBDILLUMTOGGLE = 278,
	VE_SCANCODE_KBDILLUMDOWN = 279,
	VE_SCANCODE_KBDILLUMUP = 280,
	VE_SCANCODE_EJECT = 281,
	VE_SCANCODE_SLEEP = 282,

	VE_SCANCODE_APP1 = 283,
	VE_SCANCODE_APP2 = 284,

	VE_NUM_SCANCODES = 512
};

typedef VeInt32 VeKeycode;

#define VE_K_SCANCODE_MASK (1<<30)
#define VE_SCANCODE_TO_KEYCODE(X)  (X | VE_K_SCANCODE_MASK)

enum
{
	VE_K_UNKNOWN = 0,

	VE_K_RETURN = '\r',
	VE_K_ESCAPE = '\033',
	VE_K_BACKSPACE = '\b',
	VE_K_TAB = '\t',
	VE_K_SPACE = ' ',
	VE_K_EXCLAIM = '!',
	VE_K_QUOTEDBL = '"',
	VE_K_HASH = '#',
	VE_K_PERCENT = '%',
	VE_K_DOLLAR = '$',
	VE_K_AMPERSAND = '&',
	VE_K_QUOTE = '\'',
	VE_K_LEFTPAREN = '(',
	VE_K_RIGHTPAREN = ')',
	VE_K_ASTERISK = '*',
	VE_K_PLUS = '+',
	VE_K_COMMA = ',',
	VE_K_MINUS = '-',
	VE_K_PERIOD = '.',
	VE_K_SLASH = '/',
	VE_K_0 = '0',
	VE_K_1 = '1',
	VE_K_2 = '2',
	VE_K_3 = '3',
	VE_K_4 = '4',
	VE_K_5 = '5',
	VE_K_6 = '6',
	VE_K_7 = '7',
	VE_K_8 = '8',
	VE_K_9 = '9',
	VE_K_COLON = ':',
	VE_K_SEMICOLON = ';',
	VE_K_LESS = '<',
	VE_K_EQUALS = '=',
	VE_K_GREATER = '>',
	VE_K_QUESTION = '?',
	VE_K_AT = '@',

	VE_K_LEFTBRACKET = '[',
	VE_K_BACKSLASH = '\\',
	VE_K_RIGHTBRACKET = ']',
	VE_K_CARET = '^',
	VE_K_UNDERSCORE = '_',
	VE_K_BACKQUOTE = '`',
	VE_K_a = 'a',
	VE_K_b = 'b',
	VE_K_c = 'c',
	VE_K_d = 'd',
	VE_K_e = 'e',
	VE_K_f = 'f',
	VE_K_g = 'g',
	VE_K_h = 'h',
	VE_K_i = 'i',
	VE_K_j = 'j',
	VE_K_k = 'k',
	VE_K_l = 'l',
	VE_K_m = 'm',
	VE_K_n = 'n',
	VE_K_o = 'o',
	VE_K_p = 'p',
	VE_K_q = 'q',
	VE_K_r = 'r',
	VE_K_s = 's',
	VE_K_t = 't',
	VE_K_u = 'u',
	VE_K_v = 'v',
	VE_K_w = 'w',
	VE_K_x = 'x',
	VE_K_y = 'y',
	VE_K_z = 'z',

	VE_K_CAPSLOCK = VE_SCANCODE_TO_KEYCODE(VE_SCANCODE_CAPSLOCK),

	VE_K_F1 = VE_SCANCODE_TO_KEYCODE(VE_SCANCODE_F1),
	VE_K_F2 = VE_SCANCODE_TO_KEYCODE(VE_SCANCODE_F2),
	VE_K_F3 = VE_SCANCODE_TO_KEYCODE(VE_SCANCODE_F3),
	VE_K_F4 = VE_SCANCODE_TO_KEYCODE(VE_SCANCODE_F4),
	VE_K_F5 = VE_SCANCODE_TO_KEYCODE(VE_SCANCODE_F5),
	VE_K_F6 = VE_SCANCODE_TO_KEYCODE(VE_SCANCODE_F6),
	VE_K_F7 = VE_SCANCODE_TO_KEYCODE(VE_SCANCODE_F7),
	VE_K_F8 = VE_SCANCODE_TO_KEYCODE(VE_SCANCODE_F8),
	VE_K_F9 = VE_SCANCODE_TO_KEYCODE(VE_SCANCODE_F9),
	VE_K_F10 = VE_SCANCODE_TO_KEYCODE(VE_SCANCODE_F10),
	VE_K_F11 = VE_SCANCODE_TO_KEYCODE(VE_SCANCODE_F11),
	VE_K_F12 = VE_SCANCODE_TO_KEYCODE(VE_SCANCODE_F12),

	VE_K_PRINTSCREEN = VE_SCANCODE_TO_KEYCODE(VE_SCANCODE_PRINTSCREEN),
	VE_K_SCROLLLOCK = VE_SCANCODE_TO_KEYCODE(VE_SCANCODE_SCROLLLOCK),
	VE_K_PAUSE = VE_SCANCODE_TO_KEYCODE(VE_SCANCODE_PAUSE),
	VE_K_INSERT = VE_SCANCODE_TO_KEYCODE(VE_SCANCODE_INSERT),
	VE_K_HOME = VE_SCANCODE_TO_KEYCODE(VE_SCANCODE_HOME),
	VE_K_PAGEUP = VE_SCANCODE_TO_KEYCODE(VE_SCANCODE_PAGEUP),
	VE_K_DELETE = '\177',
	VE_K_END = VE_SCANCODE_TO_KEYCODE(VE_SCANCODE_END),
	VE_K_PAGEDOWN = VE_SCANCODE_TO_KEYCODE(VE_SCANCODE_PAGEDOWN),
	VE_K_RIGHT = VE_SCANCODE_TO_KEYCODE(VE_SCANCODE_RIGHT),
	VE_K_LEFT = VE_SCANCODE_TO_KEYCODE(VE_SCANCODE_LEFT),
	VE_K_DOWN = VE_SCANCODE_TO_KEYCODE(VE_SCANCODE_DOWN),
	VE_K_UP = VE_SCANCODE_TO_KEYCODE(VE_SCANCODE_UP),

	VE_K_NUMLOCKCLEAR = VE_SCANCODE_TO_KEYCODE(VE_SCANCODE_NUMLOCKCLEAR),
	VE_K_KP_DIVIDE = VE_SCANCODE_TO_KEYCODE(VE_SCANCODE_KP_DIVIDE),
	VE_K_KP_MULTIPLY = VE_SCANCODE_TO_KEYCODE(VE_SCANCODE_KP_MULTIPLY),
	VE_K_KP_MINUS = VE_SCANCODE_TO_KEYCODE(VE_SCANCODE_KP_MINUS),
	VE_K_KP_PLUS = VE_SCANCODE_TO_KEYCODE(VE_SCANCODE_KP_PLUS),
	VE_K_KP_ENTER = VE_SCANCODE_TO_KEYCODE(VE_SCANCODE_KP_ENTER),
	VE_K_KP_1 = VE_SCANCODE_TO_KEYCODE(VE_SCANCODE_KP_1),
	VE_K_KP_2 = VE_SCANCODE_TO_KEYCODE(VE_SCANCODE_KP_2),
	VE_K_KP_3 = VE_SCANCODE_TO_KEYCODE(VE_SCANCODE_KP_3),
	VE_K_KP_4 = VE_SCANCODE_TO_KEYCODE(VE_SCANCODE_KP_4),
	VE_K_KP_5 = VE_SCANCODE_TO_KEYCODE(VE_SCANCODE_KP_5),
	VE_K_KP_6 = VE_SCANCODE_TO_KEYCODE(VE_SCANCODE_KP_6),
	VE_K_KP_7 = VE_SCANCODE_TO_KEYCODE(VE_SCANCODE_KP_7),
	VE_K_KP_8 = VE_SCANCODE_TO_KEYCODE(VE_SCANCODE_KP_8),
	VE_K_KP_9 = VE_SCANCODE_TO_KEYCODE(VE_SCANCODE_KP_9),
	VE_K_KP_0 = VE_SCANCODE_TO_KEYCODE(VE_SCANCODE_KP_0),
	VE_K_KP_PERIOD = VE_SCANCODE_TO_KEYCODE(VE_SCANCODE_KP_PERIOD),

	VE_K_APPLICATION = VE_SCANCODE_TO_KEYCODE(VE_SCANCODE_APPLICATION),
	VE_K_POWER = VE_SCANCODE_TO_KEYCODE(VE_SCANCODE_POWER),
	VE_K_KP_EQUALS = VE_SCANCODE_TO_KEYCODE(VE_SCANCODE_KP_EQUALS),
	VE_K_F13 = VE_SCANCODE_TO_KEYCODE(VE_SCANCODE_F13),
	VE_K_F14 = VE_SCANCODE_TO_KEYCODE(VE_SCANCODE_F14),
	VE_K_F15 = VE_SCANCODE_TO_KEYCODE(VE_SCANCODE_F15),
	VE_K_F16 = VE_SCANCODE_TO_KEYCODE(VE_SCANCODE_F16),
	VE_K_F17 = VE_SCANCODE_TO_KEYCODE(VE_SCANCODE_F17),
	VE_K_F18 = VE_SCANCODE_TO_KEYCODE(VE_SCANCODE_F18),
	VE_K_F19 = VE_SCANCODE_TO_KEYCODE(VE_SCANCODE_F19),
	VE_K_F20 = VE_SCANCODE_TO_KEYCODE(VE_SCANCODE_F20),
	VE_K_F21 = VE_SCANCODE_TO_KEYCODE(VE_SCANCODE_F21),
	VE_K_F22 = VE_SCANCODE_TO_KEYCODE(VE_SCANCODE_F22),
	VE_K_F23 = VE_SCANCODE_TO_KEYCODE(VE_SCANCODE_F23),
	VE_K_F24 = VE_SCANCODE_TO_KEYCODE(VE_SCANCODE_F24),
	VE_K_EXECUTE = VE_SCANCODE_TO_KEYCODE(VE_SCANCODE_EXECUTE),
	VE_K_HELP = VE_SCANCODE_TO_KEYCODE(VE_SCANCODE_HELP),
	VE_K_MENU = VE_SCANCODE_TO_KEYCODE(VE_SCANCODE_MENU),
	VE_K_SELECT = VE_SCANCODE_TO_KEYCODE(VE_SCANCODE_SELECT),
	VE_K_STOP = VE_SCANCODE_TO_KEYCODE(VE_SCANCODE_STOP),
	VE_K_AGAIN = VE_SCANCODE_TO_KEYCODE(VE_SCANCODE_AGAIN),
	VE_K_UNDO = VE_SCANCODE_TO_KEYCODE(VE_SCANCODE_UNDO),
	VE_K_CUT = VE_SCANCODE_TO_KEYCODE(VE_SCANCODE_CUT),
	VE_K_COPY = VE_SCANCODE_TO_KEYCODE(VE_SCANCODE_COPY),
	VE_K_PASTE = VE_SCANCODE_TO_KEYCODE(VE_SCANCODE_PASTE),
	VE_K_FIND = VE_SCANCODE_TO_KEYCODE(VE_SCANCODE_FIND),
	VE_K_MUTE = VE_SCANCODE_TO_KEYCODE(VE_SCANCODE_MUTE),
	VE_K_VOLUMEUP = VE_SCANCODE_TO_KEYCODE(VE_SCANCODE_VOLUMEUP),
	VE_K_VOLUMEDOWN = VE_SCANCODE_TO_KEYCODE(VE_SCANCODE_VOLUMEDOWN),
	VE_K_KP_COMMA = VE_SCANCODE_TO_KEYCODE(VE_SCANCODE_KP_COMMA),
	VE_K_KP_EQUALSAS400 =
	VE_SCANCODE_TO_KEYCODE(VE_SCANCODE_KP_EQUALSAS400),

	VE_K_ALTERASE = VE_SCANCODE_TO_KEYCODE(VE_SCANCODE_ALTERASE),
	VE_K_SYSREQ = VE_SCANCODE_TO_KEYCODE(VE_SCANCODE_SYSREQ),
	VE_K_CANCEL = VE_SCANCODE_TO_KEYCODE(VE_SCANCODE_CANCEL),
	VE_K_CLEAR = VE_SCANCODE_TO_KEYCODE(VE_SCANCODE_CLEAR),
	VE_K_PRIOR = VE_SCANCODE_TO_KEYCODE(VE_SCANCODE_PRIOR),
	VE_K_RETURN2 = VE_SCANCODE_TO_KEYCODE(VE_SCANCODE_RETURN2),
	VE_K_SEPARATOR = VE_SCANCODE_TO_KEYCODE(VE_SCANCODE_SEPARATOR),
	VE_K_OUT = VE_SCANCODE_TO_KEYCODE(VE_SCANCODE_OUT),
	VE_K_OPER = VE_SCANCODE_TO_KEYCODE(VE_SCANCODE_OPER),
	VE_K_CLEARAGAIN = VE_SCANCODE_TO_KEYCODE(VE_SCANCODE_CLEARAGAIN),
	VE_K_CRSEL = VE_SCANCODE_TO_KEYCODE(VE_SCANCODE_CRSEL),
	VE_K_EXSEL = VE_SCANCODE_TO_KEYCODE(VE_SCANCODE_EXSEL),

	VE_K_KP_00 = VE_SCANCODE_TO_KEYCODE(VE_SCANCODE_KP_00),
	VE_K_KP_000 = VE_SCANCODE_TO_KEYCODE(VE_SCANCODE_KP_000),
	VE_K_THOUSANDSSEPARATOR =
	VE_SCANCODE_TO_KEYCODE(VE_SCANCODE_THOUSANDSSEPARATOR),
	VE_K_DECIMALSEPARATOR =
	VE_SCANCODE_TO_KEYCODE(VE_SCANCODE_DECIMALSEPARATOR),
	VE_K_CURRENCYUNIT = VE_SCANCODE_TO_KEYCODE(VE_SCANCODE_CURRENCYUNIT),
	VE_K_CURRENCYSUBUNIT =
	VE_SCANCODE_TO_KEYCODE(VE_SCANCODE_CURRENCYSUBUNIT),
	VE_K_KP_LEFTPAREN = VE_SCANCODE_TO_KEYCODE(VE_SCANCODE_KP_LEFTPAREN),
	VE_K_KP_RIGHTPAREN = VE_SCANCODE_TO_KEYCODE(VE_SCANCODE_KP_RIGHTPAREN),
	VE_K_KP_LEFTBRACE = VE_SCANCODE_TO_KEYCODE(VE_SCANCODE_KP_LEFTBRACE),
	VE_K_KP_RIGHTBRACE = VE_SCANCODE_TO_KEYCODE(VE_SCANCODE_KP_RIGHTBRACE),
	VE_K_KP_TAB = VE_SCANCODE_TO_KEYCODE(VE_SCANCODE_KP_TAB),
	VE_K_KP_BACKSPACE = VE_SCANCODE_TO_KEYCODE(VE_SCANCODE_KP_BACKSPACE),
	VE_K_KP_A = VE_SCANCODE_TO_KEYCODE(VE_SCANCODE_KP_A),
	VE_K_KP_B = VE_SCANCODE_TO_KEYCODE(VE_SCANCODE_KP_B),
	VE_K_KP_C = VE_SCANCODE_TO_KEYCODE(VE_SCANCODE_KP_C),
	VE_K_KP_D = VE_SCANCODE_TO_KEYCODE(VE_SCANCODE_KP_D),
	VE_K_KP_E = VE_SCANCODE_TO_KEYCODE(VE_SCANCODE_KP_E),
	VE_K_KP_F = VE_SCANCODE_TO_KEYCODE(VE_SCANCODE_KP_F),
	VE_K_KP_XOR = VE_SCANCODE_TO_KEYCODE(VE_SCANCODE_KP_XOR),
	VE_K_KP_POWER = VE_SCANCODE_TO_KEYCODE(VE_SCANCODE_KP_POWER),
	VE_K_KP_PERCENT = VE_SCANCODE_TO_KEYCODE(VE_SCANCODE_KP_PERCENT),
	VE_K_KP_LESS = VE_SCANCODE_TO_KEYCODE(VE_SCANCODE_KP_LESS),
	VE_K_KP_GREATER = VE_SCANCODE_TO_KEYCODE(VE_SCANCODE_KP_GREATER),
	VE_K_KP_AMPERSAND = VE_SCANCODE_TO_KEYCODE(VE_SCANCODE_KP_AMPERSAND),
	VE_K_KP_DBLAMPERSAND =
	VE_SCANCODE_TO_KEYCODE(VE_SCANCODE_KP_DBLAMPERSAND),
	VE_K_KP_VERTICALBAR =
	VE_SCANCODE_TO_KEYCODE(VE_SCANCODE_KP_VERTICALBAR),
	VE_K_KP_DBLVERTICALBAR =
	VE_SCANCODE_TO_KEYCODE(VE_SCANCODE_KP_DBLVERTICALBAR),
	VE_K_KP_COLON = VE_SCANCODE_TO_KEYCODE(VE_SCANCODE_KP_COLON),
	VE_K_KP_HASH = VE_SCANCODE_TO_KEYCODE(VE_SCANCODE_KP_HASH),
	VE_K_KP_SPACE = VE_SCANCODE_TO_KEYCODE(VE_SCANCODE_KP_SPACE),
	VE_K_KP_AT = VE_SCANCODE_TO_KEYCODE(VE_SCANCODE_KP_AT),
	VE_K_KP_EXCLAM = VE_SCANCODE_TO_KEYCODE(VE_SCANCODE_KP_EXCLAM),
	VE_K_KP_MEMSTORE = VE_SCANCODE_TO_KEYCODE(VE_SCANCODE_KP_MEMSTORE),
	VE_K_KP_MEMRECALL = VE_SCANCODE_TO_KEYCODE(VE_SCANCODE_KP_MEMRECALL),
	VE_K_KP_MEMCLEAR = VE_SCANCODE_TO_KEYCODE(VE_SCANCODE_KP_MEMCLEAR),
	VE_K_KP_MEMADD = VE_SCANCODE_TO_KEYCODE(VE_SCANCODE_KP_MEMADD),
	VE_K_KP_MEMSUBTRACT =
	VE_SCANCODE_TO_KEYCODE(VE_SCANCODE_KP_MEMSUBTRACT),
	VE_K_KP_MEMMULTIPLY =
	VE_SCANCODE_TO_KEYCODE(VE_SCANCODE_KP_MEMMULTIPLY),
	VE_K_KP_MEMDIVIDE = VE_SCANCODE_TO_KEYCODE(VE_SCANCODE_KP_MEMDIVIDE),
	VE_K_KP_PLUSMINUS = VE_SCANCODE_TO_KEYCODE(VE_SCANCODE_KP_PLUSMINUS),
	VE_K_KP_CLEAR = VE_SCANCODE_TO_KEYCODE(VE_SCANCODE_KP_CLEAR),
	VE_K_KP_CLEARENTRY = VE_SCANCODE_TO_KEYCODE(VE_SCANCODE_KP_CLEARENTRY),
	VE_K_KP_BINARY = VE_SCANCODE_TO_KEYCODE(VE_SCANCODE_KP_BINARY),
	VE_K_KP_OCTAL = VE_SCANCODE_TO_KEYCODE(VE_SCANCODE_KP_OCTAL),
	VE_K_KP_DECIMAL = VE_SCANCODE_TO_KEYCODE(VE_SCANCODE_KP_DECIMAL),
	VE_K_KP_HEXADECIMAL =
	VE_SCANCODE_TO_KEYCODE(VE_SCANCODE_KP_HEXADECIMAL),

	VE_K_LCTRL = VE_SCANCODE_TO_KEYCODE(VE_SCANCODE_LCTRL),
	VE_K_LSHIFT = VE_SCANCODE_TO_KEYCODE(VE_SCANCODE_LSHIFT),
	VE_K_LALT = VE_SCANCODE_TO_KEYCODE(VE_SCANCODE_LALT),
	VE_K_LGUI = VE_SCANCODE_TO_KEYCODE(VE_SCANCODE_LGUI),
	VE_K_RCTRL = VE_SCANCODE_TO_KEYCODE(VE_SCANCODE_RCTRL),
	VE_K_RSHIFT = VE_SCANCODE_TO_KEYCODE(VE_SCANCODE_RSHIFT),
	VE_K_RALT = VE_SCANCODE_TO_KEYCODE(VE_SCANCODE_RALT),
	VE_K_RGUI = VE_SCANCODE_TO_KEYCODE(VE_SCANCODE_RGUI),

	VE_K_MODE = VE_SCANCODE_TO_KEYCODE(VE_SCANCODE_MODE),

	VE_K_AUDIONEXT = VE_SCANCODE_TO_KEYCODE(VE_SCANCODE_AUDIONEXT),
	VE_K_AUDIOPREV = VE_SCANCODE_TO_KEYCODE(VE_SCANCODE_AUDIOPREV),
	VE_K_AUDIOSTOP = VE_SCANCODE_TO_KEYCODE(VE_SCANCODE_AUDIOSTOP),
	VE_K_AUDIOPLAY = VE_SCANCODE_TO_KEYCODE(VE_SCANCODE_AUDIOPLAY),
	VE_K_AUDIOMUTE = VE_SCANCODE_TO_KEYCODE(VE_SCANCODE_AUDIOMUTE),
	VE_K_MEDIASELECT = VE_SCANCODE_TO_KEYCODE(VE_SCANCODE_MEDIASELECT),
	VE_K_WWW = VE_SCANCODE_TO_KEYCODE(VE_SCANCODE_WWW),
	VE_K_MAIL = VE_SCANCODE_TO_KEYCODE(VE_SCANCODE_MAIL),
	VE_K_CALCULATOR = VE_SCANCODE_TO_KEYCODE(VE_SCANCODE_CALCULATOR),
	VE_K_COMPUTER = VE_SCANCODE_TO_KEYCODE(VE_SCANCODE_COMPUTER),
	VE_K_AC_SEARCH = VE_SCANCODE_TO_KEYCODE(VE_SCANCODE_AC_SEARCH),
	VE_K_AC_HOME = VE_SCANCODE_TO_KEYCODE(VE_SCANCODE_AC_HOME),
	VE_K_AC_BACK = VE_SCANCODE_TO_KEYCODE(VE_SCANCODE_AC_BACK),
	VE_K_AC_FORWARD = VE_SCANCODE_TO_KEYCODE(VE_SCANCODE_AC_FORWARD),
	VE_K_AC_STOP = VE_SCANCODE_TO_KEYCODE(VE_SCANCODE_AC_STOP),
	VE_K_AC_REFRESH = VE_SCANCODE_TO_KEYCODE(VE_SCANCODE_AC_REFRESH),
	VE_K_AC_BOOKMARKS = VE_SCANCODE_TO_KEYCODE(VE_SCANCODE_AC_BOOKMARKS),

	VE_K_BRIGHTNESSDOWN =
	VE_SCANCODE_TO_KEYCODE(VE_SCANCODE_BRIGHTNESSDOWN),
	VE_K_BRIGHTNESSUP = VE_SCANCODE_TO_KEYCODE(VE_SCANCODE_BRIGHTNESSUP),
	VE_K_DISPLAYSWITCH = VE_SCANCODE_TO_KEYCODE(VE_SCANCODE_DISPLAYSWITCH),
	VE_K_KBDILLUMTOGGLE =
	VE_SCANCODE_TO_KEYCODE(VE_SCANCODE_KBDILLUMTOGGLE),
	VE_K_KBDILLUMDOWN = VE_SCANCODE_TO_KEYCODE(VE_SCANCODE_KBDILLUMDOWN),
	VE_K_KBDILLUMUP = VE_SCANCODE_TO_KEYCODE(VE_SCANCODE_KBDILLUMUP),
	VE_K_EJECT = VE_SCANCODE_TO_KEYCODE(VE_SCANCODE_EJECT),
	VE_K_SLEEP = VE_SCANCODE_TO_KEYCODE(VE_SCANCODE_SLEEP)
};

enum VeKeymod
{
	VE_KMOD_NONE = 0x0000,
	VE_KMOD_LSHIFT = 0x0001,
	VE_KMOD_RSHIFT = 0x0002,
	VE_KMOD_LCTRL = 0x0040,
	VE_KMOD_RCTRL = 0x0080,
	VE_KMOD_LALT = 0x0100,
	VE_KMOD_RALT = 0x0200,
	VE_KMOD_LGUI = 0x0400,
	VE_KMOD_RGUI = 0x0800,
	VE_KMOD_NUM = 0x1000,
	VE_KMOD_CAPS = 0x2000,
	VE_KMOD_MODE = 0x4000,
	VE_KMOD_RESERVED = 0x8000
} ;

#define VE_KMOD_CTRL   (VE_KMOD_LCTRL|VE_KMOD_RCTRL)
#define VE_KMOD_SHIFT  (VE_KMOD_LSHIFT|VE_KMOD_RSHIFT)
#define VE_KMOD_ALT    (VE_KMOD_LALT|VE_KMOD_RALT)
#define VE_KMOD_GUI    (VE_KMOD_LGUI|VE_KMOD_RGUI)

#define VE_RELEASED 0
#define VE_PRESSED 1

struct VeKeysym
{
	VeScancode m_eScancode;
	VeKeycode m_i32Sym;
	VeUInt16 m_u16Mod;
};

class VE_POWER_API VeKeyboard : public VeRefObject
{
public:
	VeKeyboard() noexcept;

	virtual ~VeKeyboard() noexcept;

	inline VeWindowPtr GetFocus() noexcept;

	inline const VeUInt8* GetState() noexcept;

	inline VeUInt16 GetModState() noexcept;

	void Init() noexcept;

	void Term() noexcept;

	void Reset() noexcept;

	void SetKeymap(VeUInt32 u32Start, VeKeycode* pkKeys, VeUInt32 u32Lenth) noexcept;

	void SetScancodeName(VeScancode eScancode, const VeChar8* pcName) noexcept;

	void SetFocus(VeWindow::Data* pkWindow) noexcept;

	void SendKey(VeUInt8 u8State, VeScancode eScancode) noexcept;

	static void GetDefaultKeymap(VeKeycode* pkKeymap) noexcept;	

protected:
	VeWindow::Data* m_pkFocus = nullptr;
	VeUInt16 m_u16ModState = 0;
	VeUInt8 m_au8KeyState[VE_NUM_SCANCODES];
	VeKeycode m_i32KeyMap[VE_NUM_SCANCODES];

};

VeSmartPointer(VeKeyboard);

#include "VeKeyboard.inl"
