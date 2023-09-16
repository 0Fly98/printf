#include "main.h"

/**
 * is_printable - Checks if a character is printable.
 * @c: The character to check.
 *
 * This function determines whether a character
 *			is a printable character, i.e., it falls within
 * the ASCII range of 32 to 126, inclusive.
 *
 * Return: 1 if the character is printable, 0 otherwise.
 */

int is_printable(char c)
{
	if (c >= 32 && c < 127)
		return (1);

	return (0);
}

/**
 * append_hexa_code - Appends a hexadecimal escape sequence to the buffer.
 * @ascii_code: The ASCII code to convert and append.
 * @buffer: The character array where the data is stored.
 * @i: The index at which the escape sequence should be appended.
 *
 * This function appends a hexadecimal escape sequence
 *			(e.g., "\xHH") to the buffer for a given
 * ASCII code. It returns the number of characters appended, which is always 3.
 *
 * Return: The number of characters appended to the buffer.
 */
int append_hexa_code(char ascii_code, char buffer[], int i)
{
	char map[] = "0123456789ABCDEF";
	/* The hexa format code is always 2 digits long */
	if (ascii_code < 0)
		ascii_code *= -1;

	buffer[i++] = '\\';
	buffer[i++] = 'x';

	buffer[i++] = map[ascii_code / 16];
	buffer[i] = map[ascii_code % 16];

	return (3);
}

/**
 * is_digit - Checks if a character is a digit.
 * @c: The character to check.
 *
 * This function determines whether a character
 *			is a digit by checking if it falls within
 * the ASCII range of '0' to '9'.
 *
 * Return: 1 if the character is a digit, 0 otherwise.
 */

int is_digit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);

	return (0);
}

/**
 * convert_size_number - Converts a number based on the specified size.
 * @num: The number to be converted.
 * @size: The size modifier (e.g., S_LONG, S_SHORT).
 *
 * This function converts a number to a different
 *			data type based on the specified size.
 * It can be used to convert a long integer (S_LONG),
 *				short integer (S_SHORT), or int (default).
 *
 * Return: The converted number.
 */

long int convert_size_number(long int num, int size)
{
	if (size == S_LONG)
		return (num);
	else if (size == S_SHORT)
		return ((short)num);

	return ((int)num);
}

/**
 * convert_size_unsgnd - Converts an unsigned number
 *				based on the specified size.
 * @num: The unsigned number to be converted.
 * @size: The size modifier (e.g., S_LONG, S_SHORT).
 *
 * This function converts an unsigned number to
 *				a different data type based on the specified size.
 * It can be used to convert an unsigned long integer
 *			(S_LONG), unsigned short integer (S_SHORT), or
 *				unsigned int (default).
 *
 * Return: The converted unsigned number.
 */

long int convert_size_unsgnd(unsigned long int num, int size)
{
	if (size == S_LONG)
		return (num);
	else if (size == S_SHORT)
		return ((unsigned short)num);

	return ((unsigned int)num);
}
