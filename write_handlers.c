#include "main.h"

/************************* WRITE HANDLE *************************/

/**
 * handle_write_char - Handles writing a single character to the buffer.
 * @c: The character to write.
 * @buffer: The character array where the data is stored.
 * @flags: Flags for formatting (e.g., minus, plus, zero-fill).
 * @width: Minimum field width for printing.
 * @precision: Minimum number of digits to be printed.
 * @size: Size modifier for formatting (e.g., long, short).
 *
 * This function writes a single character to the buffer, considering the
 * specified formatting flags, width, and precision.
 *
 * Return: The number of characters written.
 */



int handle_write_char(char c, char buffer[],
	int flags, int width, int precision, int size)
{ /* char is stored at left and paddind at buffer's right */
	int i = 0;
	char padd = ' ';

	UNUSED(precision);
	UNUSED(size);

	if (flags & F_ZERO)
		padd = '0';

	buffer[i++] = c;
	buffer[i] = '\0';

	if (width > 1)
	{
		buffer[BUFF_SIZE - 1] = '\0';
		for (i = 0; i < width - 1; i++)
			buffer[BUFF_SIZE - i - 2] = padd;

		if (flags & F_MINUS)
			return (write(1, &buffer[0], 1) +
					write(1, &buffer[BUFF_SIZE - i - 1], width - 1));
		else
			return (write(1, &buffer[BUFF_SIZE - i - 1], width - 1) +
					write(1, &buffer[0], 1));
	}

	return (write(1, &buffer[0], 1));
}

/************************* WRITE NUMBER *************************/

/**
 * write_number - Writes a number to the buffer.
 * @is_negative: Flag indicating if the number is negative.
 * @ind: The index where the number should be written in the buffer.
 * @buffer: The character array where the data is stored.
 * @flags: Flags for formatting (e.g., minus, plus, zero-fill).
 * @width: Minimum field width for printing.
 * @precision: Minimum number of digits to be printed.
 * @size: Size modifier for formatting (e.g., long, short).
 *
 * This function writes a number to the buffer, considering the specified
 * formatting flags, width, and precision. It also handles negative numbers
 * and additional characters like '+' or '-'.
 *
 * Return: The number of characters written.
 */


int write_number(int is_negative, int ind, char buffer[],
	int flags, int width, int precision, int size)
{
	int length = BUFF_SIZE - ind - 1;
	char padd = ' ', extra_ch = 0;

	UNUSED(size);

	if ((flags & F_ZERO) && !(flags & F_MINUS))
		padd = '0';
	if (is_negative)
		extra_ch = '-';
	else if (flags & F_PLUS)
		extra_ch = '+';
	else if (flags & F_SPACE)
		extra_ch = ' ';

	return (write_num(ind, buffer, flags, width, precision,
		length, padd, extra_ch));
}

/**
 * write_num - Writes a number to the buffer.
 * @ind: The index where the number should be written in the buffer.
 * @buffer: The character array where the data is stored.
 * @flags: Flags for formatting (e.g., minus, plus, zero-fill).
 * @width: Minimum field width for printing.
 * @prec: Precision value.
 * @length: The length of the number.
 * @padd: Padding character (e.g., '0' or ' ').
 * @extra_c: Additional character (e.g., '+' or '-').
 *
 * This function writes a number to the buffer, considering the specified
 * formatting flags, width, precision, padding, and additional characters.
 *
 * Return: The number of characters written.
 */

int write_num(int ind, char buffer[],
	int flags, int width, int prec,
	int length, char padd, char extra_c)
{
	int i, padd_start = 1;

	if (prec == 0 && ind == BUFF_SIZE - 2 && buffer[ind] == '0' && width == 0)
		return (0); /* printf(".0d", 0) no char is printed */
	if (prec == 0 && ind == BUFF_SIZE - 2 && buffer[ind] == '0')
		buffer[ind] = padd = ' '; /* width is displayed with padding ' ' */
	if (prec > 0 && prec < length)
		padd = ' ';
	while (prec > length)
		buffer[--ind] = '0', length++;
	if (extra_c != 0)
		length++;
	if (width > length)
	{
		for (i = 1; i < width - length + 1; i++)
			buffer[i] = padd;
		buffer[i] = '\0';
		if (flags & F_MINUS && padd == ' ')/* Asign extra char to left of buffer */
		{
			if (extra_c)
				buffer[--ind] = extra_c;
			return (write(1, &buffer[ind], length) + write(1, &buffer[1], i - 1));
		}
		else if (!(flags & F_MINUS) && padd == ' ')/* extra char to left of buff */
		{
			if (extra_c)
				buffer[--ind] = extra_c;
			return (write(1, &buffer[1], i - 1) + write(1, &buffer[ind], length));
		}
		else if (!(flags & F_MINUS) && padd == '0')/* extra char to left of padd */
		{
			if (extra_c)
				buffer[--padd_start] = extra_c;
			return (write(1, &buffer[padd_start], i - padd_start) +
				write(1, &buffer[ind], length - (1 - padd_start)));
		}
	}
	if (extra_c)
		buffer[--ind] = extra_c;
	return (write(1, &buffer[ind], length));
}

/**
 * write_unsgnd - Writes an unsigned number to the buffer.
 * @is_negative: Flag indicating if the number is negative.
 * @ind: The index where the number should be written in the buffer.
 * @buffer: The character array where the data is stored.
 * @flags: Flags for formatting (e.g., minus, plus, zero-fill).
 * @width: Minimum field width for printing.
 * @precision: Minimum number of digits to be printed.
 * @size: Size modifier for formatting (e.g., long, short).
 *
 * This function writes an unsigned number to the buffer, considering the
 * specified formatting flags, width, and precision. It also handles padding
 * and additional characters like '+' or '-'.
 *
 * Return: The number of characters written.
 */

int write_unsgnd(int is_negative, int ind,
	char buffer[],
	int flags, int width, int precision, int size)
{
	/* The number is stored at the bufer's right and starts at position i */
	int length = BUFF_SIZE - ind - 1, i = 0;
	char padd = ' ';

	UNUSED(is_negative);
	UNUSED(size);

	if (precision == 0 && ind == BUFF_SIZE - 2 && buffer[ind] == '0')
		return (0); /* printf(".0d", 0) no char is printed */

	if (precision > 0 && precision < length)
		padd = ' ';

	while (precision > length)
	{
		buffer[--ind] = '0';
		length++;
	}

	if ((flags & F_ZERO) && !(flags & F_MINUS))
		padd = '0';

	if (width > length)
	{
		for (i = 0; i < width - length; i++)
			buffer[i] = padd;

		buffer[i] = '\0';

		if (flags & F_MINUS) /* Asign extra char to left of buffer [buffer>padd]*/
		{
			return (write(1, &buffer[ind], length) + write(1, &buffer[0], i));
		}
		else /* Asign extra char to left of padding [padd>buffer]*/
		{
			return (write(1, &buffer[0], i) + write(1, &buffer[ind], length));
		}
	}

	return (write(1, &buffer[ind], length));
}

/**
 * write_pointer - Writes a pointer to the buffer.
 * @buffer: The character array where the data is stored.
 * @ind: The index where the pointer should be written in the buffer.
 * @length: The length of the pointer.
 * @width: Minimum field width for printing.
 * @flags: Flags for formatting (e.g., minus, plus, zero-fill).
 * @padd: Padding character (e.g., '0' or ' ').
 * @extra_c: Additional character (e.g., '+' or '-').
 * @padd_start: Starting position for padding.
 *
 * This function writes a pointer to the buffer, considering the specified
 * formatting flags, width, padding, and additional characters.
 *
 * Return: The number of characters written.
 */


int write_pointer(char buffer[], int ind, int length,
	int width, int flags, char padd, char extra_c, int padd_start)
{
	int i;

	if (width > length)
	{
		for (i = 3; i < width - length + 3; i++)
			buffer[i] = padd;
		buffer[i] = '\0';
		if (flags & F_MINUS && padd == ' ')/* Asign extra char to left of buffer */
		{
			buffer[--ind] = 'x';
			buffer[--ind] = '0';
			if (extra_c)
				buffer[--ind] = extra_c;
			return (write(1, &buffer[ind], length) + write(1, &buffer[3], i - 3));
		}
		else if (!(flags & F_MINUS) && padd == ' ')/* extra char to left of buffer */
		{
			buffer[--ind] = 'x';
			buffer[--ind] = '0';
			if (extra_c)
				buffer[--ind] = extra_c;
			return (write(1, &buffer[3], i - 3) + write(1, &buffer[ind], length));
		}
		else if (!(flags & F_MINUS) && padd == '0')/* extra char to left of padd */
		{
			if (extra_c)
				buffer[--padd_start] = extra_c;
			buffer[1] = '0';
			buffer[2] = 'x';
			return (write(1, &buffer[padd_start], i - padd_start) +
				write(1, &buffer[ind], length - (1 - padd_start) - 2));
		}
	}
	buffer[--ind] = 'x';
	buffer[--ind] = '0';
	if (extra_c)
		buffer[--ind] = extra_c;
	return (write(1, &buffer[ind], BUFF_SIZE - ind - 1));
}
