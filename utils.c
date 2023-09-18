#include "main.h"
#include <stdarg.h>
#include <stdio.h>

/**
 * is_printable - Checks if a character is printable.
 * @c: The character to check.
 *
 * Return: 1 if the character is printable, 0 otherwise.
 */
int is_printable(char c)
{
	return (c >= 32 && c <= 126);
}

/**
 * append_hexa_code - Appends a hexadecimal escape sequence to the buffer.
 * @ascii_code: The ASCII code to convert and append.
 * @buffer: The character array where the data is stored.
 * @i: The index at which the escape sequence should be appended.
 *
 * Return: The number of characters appended to the buffer.
 */
int append_hexa_code(char ascii_code, char buffer[], int i)
{
	char map[] = "0123456789ABCDEF";

	buffer[i++] = '\\';
	buffer[i++] = 'x';

	buffer[i++] = map[(ascii_code >> 4) & 0x0F];
	buffer[i] = map[ascii_code & 0x0F];

	return (3);
}

/**
 * is_digit - Checks if a character is a digit.
 * @c: The character to check.
 *
 * Return: 1 if the character is a digit, 0 otherwise.
 */
int is_digit(char c)
{
	return (c >= '0' && c <= '9');
}

/**
 * convert_size_number - Converts a number based on the specified size.
 * @num: The number to be converted.
 * @size: The size modifier (e.g., S_LONG, S_SHORT).
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
 * Return: The converted unsigned number.
 */
unsigned long int convert_size_unsgnd(unsigned long int num, int size)
{
	if (size == S_LONG)
		return (num);
	else if (size == S_SHORT)
		return ((unsigned short)num);

	return ((unsigned int)num);
}
