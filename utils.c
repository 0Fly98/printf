#include "main.h"

/**
 * is_char_printable - Checks if a character is printable.
 * @character: The character to be checked.
 *
 * Return: 1 if the character is printable, 0 otherwise.
 */
int is_char_printable(char character)
{
	if (character >= 32 && character < 127)
		return (1);

	return (0);
}

/**
 * append_hex_code - Appends a hexadecimal escape sequence to the buffer.
 * @hex_code: The ASCII code to be converted and appended.
 * @buffer: The character array where the data is stored.
 * @index: The index at which the escape sequence should be appended.
 *
 * Return: Always 3 (the number of characters appended to the buffer).
 */
int append_hex_code(char hex_code, char buffer[], int index)
{
	char hex_map[] = "0123456789ABCDEF";

	if (hex_code < 0)
		hex_code *= -1;

	buffer[index++] = '\\';
	buffer[index++] = 'x';

	buffer[index++] = hex_map[hex_code / 16];
	buffer[index] = hex_map[hex_code % 16];

	return (3);
}

/**
 * is_char_digit - Checks if a character is a digit.
 * @character: The character to be checked.
 *
 * Return: 1 if the character is a digit, 0 otherwise.
 */
int is_char_digit(char character)
{
	if (character >= '0' && character <= '9')
		return (1);

	return (0);
}

/**
 * convert_number_size - Converts a number based on the specified size.
 * @number: The number to be converted.
 * @size: The size modifier (e.g., S_LONG, S_SHORT).
 *
 * Return: The converted number.
 */
long int convert_number_size(long int number, int size)
{
	if (size == S_LONG)
		return (number);
	else if (size == S_SHORT)
		return ((short)number);

	return ((int)number);
}

/**
 * convert_unsigned_size - Converts an unsigned number based on the specified size.
 * @number: The unsigned number to be converted.
 * @size: The size modifier (e.g., S_LONG, S_SHORT).
 *
 * Return: The converted unsigned number.
 */
long int convert_unsigned_size(unsigned long int number, int size)
{
	if (size == S_LONG)
		return (number);
	else if (size == S_SHORT)
		return ((unsigned short)number);

	return ((unsigned int)number);
}
