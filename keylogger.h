#ifndef KEYLOGGER_H
#define KEYLOGGER_H

# define ASCII_UNDEFINED	'?'
# define KEYNAME_LEN		16

# define KEY(name, ascii)		{ #name, ascii, ascii }
# define KEYU(name, ascii, upper)	{ #name, ascii, upper }
# define KEY_SPECIAL(name)	{ name, ASCII_UNDEFINED, ASCII_UNDEFINED }
# define KEY_NONE	{ "Undefined", ASCII_UNDEFINED, ASCII_UNDEFINED }

# define SCANCODE_ARRAY_SIZE 0xFF

struct key_info {
	char	name[KEYNAME_LEN];
	char	ascii;
	char	ascii_uppercase;
};

struct key_info scancode_to_key[SCANCODE_ARRAY_SIZE] = {

	[0x00 ... SCANCODE_ARRAY_SIZE - 1] = KEY_NONE,

	[0x01] = KEY_SPECIAL("Escape"),

	[0x02] = KEYU(1, '1', '!'), [0x03] = KEYU(2, '2', '@'),
	[0x04] = KEYU(3, '3', '#'), [0x05] = KEYU(4, '4', '$'),
	[0x06] = KEYU(5, '5', '%'), [0x07] = KEYU(6, '6', '^'),
	[0x08] = KEYU(7, '7', '&'), [0x09] = KEYU(8, '8', '*'),
	[0x0a] = KEYU(9, '9', '('), [0x0b] = KEYU(0, '0', ')'),
	[0x0c] = KEYU(-, '-', '_'), [0x0d] = KEYU(=, '=', '+'),

	[0x0e] = KEY_SPECIAL("Backspace"), [0x0f] = KEY(Tab, '	'),

	[0x10] = KEYU(Q, 'q', 'Q'), [0x11] = KEYU(W, 'w', 'W'),
	[0x12] = KEYU(E, 'e', 'E'), [0x13] = KEYU(R, 'r', 'R'),
	[0x14] = KEYU(T, 't', 'T'), [0x15] = KEYU(Y, 'y', 'Y'),
	[0x16] = KEYU(U, 'u', 'U'), [0x17] = KEYU(I, 'i', 'I'),
	[0x18] = KEYU(O, 'o', 'O'), [0x19] = KEYU(P, 'p', 'P'),
	[0x1a] = KEYU([, '[', '{'), [0x1b] = KEYU(], ']', '}'),

	[0x1c] = KEY_SPECIAL("Enter"), [0x1d] = KEY_SPECIAL("Control Left"),

	[0x1e] = KEYU(A, 'a', 'A'), [0x1f] = KEYU(S, 's', 'S'),
	[0x20] = KEYU(D, 'd', 'D'), [0x21] = KEYU(F, 'f', 'F'),
	[0x22] = KEYU(G, 'g', 'G'), [0x23] = KEYU(H, 'h', 'H'),
	[0x24] = KEYU(J, 'j', 'J'), [0x25] = KEYU(K, 'k', 'K'),
	[0x26] = KEYU(L, 'l', 'L'), [0x27] = KEYU(;, ';', ':'),
	[0x28] = { "'", '\'', '"' }, [0x29] = KEYU(`, '`', '~'),

	[0x2a] = KEY_SPECIAL("Shift Left"), [0x2b] = KEYU(\\, '\\', '|'),

	[0x2c] = KEYU(Z, 'z', 'Z'), [0x2d] = KEYU(X, 'x', 'X'),
	[0x2e] = KEYU(C, 'c', 'C'), [0x2f] = KEYU(V, 'v', 'V'),
	[0x30] = KEYU(B, 'b', 'B'), [0x31] = KEYU(N, 'n', 'N'),
	[0x32] = KEYU(M, 'm', 'M'), [0x33] = { ",", ',', '<' },
	[0x34] = KEYU(., '.', '>'), [0x35] = KEYU(/, '/', '?'),

	[0x36] = KEY_SPECIAL("Shift Right"), [0x37] = KEY(Keypad *, '*'),
	[0x38] = KEY_SPECIAL("Alt Left"), [0x39] = KEY(Space, ' '),
	[0x3a] = KEY_SPECIAL("CapsLock"),

	[0x3b] = KEY_SPECIAL("F1"), [0x3c] = KEY_SPECIAL("F2"),
	[0x3d] = KEY_SPECIAL("F3"), [0x3e] = KEY_SPECIAL("F4"),
	[0x3f] = KEY_SPECIAL("F5"), [0x40] = KEY_SPECIAL("F6"),
	[0x41] = KEY_SPECIAL("F7"), [0x42] = KEY_SPECIAL("F8"),
	[0x43] = KEY_SPECIAL("F9"), [0x44] = KEY_SPECIAL("F10"),

	[0x45] = KEY_SPECIAL("NumberLock"), [0x46] = KEY_SPECIAL("ScrollLock"),

	[0x47] = KEY(Keypad 7, '7'), [0x48] = KEY(Keypad 8, '8'),
	[0x49] = KEY(Keypad 9, '9'), [0x4a] = KEY(Keypad -, '-'),
	[0x4b] = KEY(Keypad 4, '4'), [0x4c] = KEY(Keypad 5, '5'),
	[0x4d] = KEY(Keypad 6, '6'), [0x4e] = KEY(Keypad +, '+'),
	[0x4f] = KEY(Keypad 1, '1'), [0x50] = KEY(Keypad 2, '2'),
	[0x51] = KEY(Keypad 3, '3'), [0x52] = KEY(Keypad 0, '0'),
	[0x53] = KEY(Keypad ., '.'),

	[0x57] = KEY_SPECIAL("F11"), [0x58] = KEY_SPECIAL("F12"),

	[0x5c] = KEY_SPECIAL("Command Right"),
};


#endif
