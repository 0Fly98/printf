#include "main.h"

/************************* PRINT UNSIGNED NUMBER *************************/

/**
 * print_unsigned - Handles the formatting and printing of an unsigned integer.
 * @types: A va_list containing the variable argument list.
 * @buffer: A character array where the formatted data is stored.
 * @flags: Flags for formatting (e.g., left-justify, zero-fill).
 * @width: Minimum field width for printing.
 * @precision: Minimum number of digits to be printed (not used).
 * @size: Size modifier for formatting (e.g., h, l).
 *
 * This function retrieves an unsigned integer argument from the va_list,
 * handles formatting according to specified flags, width, and size, and
 * writes the formatted unsigned integer to the buffer.
 *
 * Return: The number of characters written to the buffer.
 */


int print_unsigned(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int i = BUFF_SIZE - 2;
	unsigned long int num = va_arg(types, unsigned long int);

	num = convert_size_unsgnd(num, size);

	if (num == 0)
		buffer[i--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';

	while (num > 0)
	{
		buffer[i--] = (num % 10) + '0';
		num /= 10;
	}

	i++;

	return (write_unsgnd(0, i, buffer, flags, width, precision, size));
}

/************* PRINT UNSIGNED NUMBER IN OCTAL ****************/

/**
 * print_octal - Handles the formatting and printing of an octal number.
 * @types: A va_list containing the variable argument list.
 * @buffer: A character array where the formatted data is stored.
 * @flags: Flags for formatting (e.g., include octal prefix).
 * @width: Minimum field width for printing (not used).
 * @precision: Minimum number of digits to be printed (not used).
 * @size: Size modifier for formatting (e.g., h, l).
 *
 * This function retrieves an unsigned integer argument from the va_list,
 * handles formatting according to specified flags, and writes the formatted
 * octal number to the buffer.
 *
 * Return: The number of characters written to the buffer.
 */




int print_octal(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{

	int i = BUFF_SIZE - 2;
	unsigned long int num = va_arg(types, unsigned long int);
	unsigned long int init_num = num;

	UNUSED(width);

	num = convert_size_unsgnd(num, size);

	if (num == 0)
		buffer[i--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';

	while (num > 0)
	{
		buffer[i--] = (num % 8) + '0';
		num /= 8;
	}

	if (flags & F_HASH && init_num != 0)
		buffer[i--] = '0';

	i++;

	return (write_unsgnd(0, i, buffer, flags, width, precision, size));
}

/************** PRINT UNSIGNED NUMBER IN HEXADECIMAL **************/

/**
 * print_hexadecimal - Handles the formatting and
 *			printing of a hexadecimal number.
 * @types: A va_list containing the variable argument list.
 * @buffer: A character array where the formatted data is stored.
 * @flags: Flags for formatting (e.g., left-justify, zero-fill).
 * @width: Minimum field width for printing.
 * @precision: Minimum number of digits to be printed (not used).
 * @size: Size modifier for formatting (e.g., h, l).
 *
 * This function retrieves an unsigned integer argument from the va_list,
 * handles formatting according to specified flags, and writes the formatted
 * hexadecimal number (in lowercase) to the buffer.
 *
 * Return: The number of characters written to the buffer.
 */


int print_hexadecimal(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	return (print_hexa(types, "0123456789abcdef", buffer,
		flags, 'x', width, precision, size));
}

/************* PRINT UNSIGNED NUMBER IN UPPER HEXADECIMAL **************/

/**
 * print_hexa_upper - Handles the formatting and printing
 *			of an uppercase hexadecimal number.
 * @types: A va_list containing the variable argument list.
 * @buffer: A character array where the formatted data is stored.
 * @flags: Flags for formatting (e.g., left-justify, zero-fill).
 * @width: Minimum field width for printing.
 * @precision: Minimum number of digits to be printed (not used).
 * @size: Size modifier for formatting (e.g., h, l).
 *
 * This function retrieves an unsigned integer argument from the va_list,
 * handles formatting according to specified flags, and writes the formatted
 * hexadecimal number (in uppercase) to the buffer.
 *
 * Return: The number of characters written to the buffer.
 */



int print_hexa_upper(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	return (print_hexa(types, "0123456789ABCDEF", buffer,
		flags, 'X', width, precision, size));
}

/************** PRINT HEXX NUM IN LOWER OR UPPER **************/


/**
 * print_hexa - Handles the formatting and printing of a hexadecimal number.
 * @types: A va_list containing the variable argument list.
 * @map_to: A character array mapping values to hexadecimal characters.
 * @buffer: A character array where the formatted data is stored.
 * @flags: Flags for formatting (e.g., include hexadecimal prefix).
 * @flag_ch: Character to prefix the hexadecimal value (e.g., 'x' or 'X').
 * @width: Minimum field width for printing (not used).
 * @precision: Minimum number of digits to be printed (not used).
 * @size: Size modifier for formatting (e.g., h, l).
 *
 * This function retrieves an unsigned integer argument from the va_list,
 * handles formatting according to specified flags and the mapping array,
 * and writes the formatted hexadecimal number to the buffer.
 *
 * Return: The number of characters written to the buffer.
 */


int print_hexa(va_list types, char map_to[], char buffer[],
	int flags, char flag_ch, int width, int precision, int size)
{
	int i = BUFF_SIZE - 2;
	unsigned long int num = va_arg(types, unsigned long int);
	unsigned long int init_num = num;

	UNUSED(width);

	num = convert_size_unsgnd(num, size);

	if (num == 0)
		buffer[i--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';

	while (num > 0)
	{
		buffer[i--] = map_to[num % 16];
		num /= 16;
	}

	if (flags & F_HASH && init_num != 0)
	{
		buffer[i--] = flag_ch;
		buffer[i--] = '0';
	}

	i++;

	return (write_unsgnd(0, i, buffer, flags, width, precision, size));
}
