#include "main.h"

/************************* PRINT CHAR *************************/


/**
 * print_char - Handles the formatting and printing of a character.
 * @types: A va_list containing the variable argument list.
 * @buffer: A character array where the formatted data is stored.
 * @flags: Flags for formatting (e.g., left-justify, zero-fill).
 * @width: Minimum field width for printing.
 * @precision: Precision for printing.
 * @size: Size modifier for formatting (e.g., h, l).
 *
 * This function retrieves a character from the va_list and formats it
 * according to the specified flags, width, precision, and size. The
 * formatted character is then written to the buffer.
 *
 * Return: The number of characters written to the buffer.
 */
int print_char(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char c = va_arg(types, int);

	return (handle_write_char(c, buffer, flags, width, precision, size));
}
/************************* PRINT A STRING *************************/


/**
 * print_string - Handles the formatting and printing of a string.
 * @types: A va_list containing the variable argument list.
 * @buffer: A character array where the formatted data is stored (not used).
 * @flags: Flags for formatting (e.g., left-justify).
 * @width: Minimum field width for printing.
 * @precision: Maximum number of characters to be printed (not used).
 * @size: Size modifier for formatting (not used).
 *
 * This function retrieves a string argument from the va_list, handles
 * formatting according to specified flags and width, and writes the
 * formatted string to the standard output.
 *
 * Return: The number of characters written to the standard output.
 */
int print_string(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int length = 0, i;
	char *str = va_arg(types, char *);

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);
	if (str == NULL)
	{
		str = "(null)";
		if (precision >= 6)
			str = " ";
	}

	while (str[length] != '\0')
		length++;

	if (precision >= 0 && precision < length)
		length = precision;

	if (width > length)
	{
		if (flags & F_MINUS)
		{
			write(1, &str[0], length);
			for (i = width - length; i > 0; i--)
				write(1, " ", 1);
			return (width);
		}
		else
		{
			for (i = width - length; i > 0; i--)
				write(1, " ", 1);
			write(1, &str[0], length);
			return (width);
		}
	}

	return (write(1, str, length));
}
/************************* PRINT PERCENT SIGN *************************/


/**
 * print_percent - Handles the formatting and printing of a percent symbol.
 * @types: A va_list containing the variable argument list (not used).
 * @buffer: A character array where the formatted data is stored (not used).
 * @flags: Flags for formatting (not used).
 * @width: Minimum field width for printing (not used).
 * @precision: Maximum number of characters to be printed (not used).
 * @size: Size modifier for formatting (not used).
 *
 * This function prints a single percent symbol to the standard output.
 *
 * Return: Always returns 1, the number of characters printed.
 */
int print_percent(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	UNUSED(types);
	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);
	return (write(1, "%%", 1));
}

/************************* PRINT INT *************************/


/**
 * print_int - Handles the formatting and printing of an integer.
 * @types: A va_list containing the variable argument list.
 * @buffer: A character array where the formatted data is stored.
 * @flags: Flags for formatting (e.g., left-justify, zero-fill).
 * @width: Minimum field width for printing.
 * @precision: Minimum number of digits to be printed (not used).
 * @size: Size modifier for formatting (e.g., h, l).
 *
 * This function retrieves an integer argument from the va_list, handles
 * formatting according to specified flags, width, and size, and writes
 * the formatted integer to the buffer.
 *
 * Return: The number of characters written to the buffer.
 */
int print_int(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int i = BUFF_SIZE - 2;
	int is_negative = 0;
	long int n = va_arg(types, long int);
	unsigned long int num;

	n = convert_size_number(n, size);

	if (n == 0)
		buffer[i--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';
	num = (unsigned long int)n;

	if (n < 0)
	{
		num = (unsigned long int)((-1) * n);
		is_negative = 1;
	}

	while (num > 0)
	{
		buffer[i--] = (num % 10) + '0';
		num /= 10;
	}

	i++;

	return (write_number(is_negative, i, buffer, flags, width, precision, size));
}

/************************* PRINT BINARY *************************/


/**
 * print_binary - Handles the formatting and printing of a binary number.
 * @types: A va_list containing the variable argument list.
 * @buffer: A character array where the formatted data is stored (not used).
 * @flags: Flags for formatting (not used).
 * @width: Minimum field width for printing (not used).
 * @precision: Minimum number of digits to be printed (not used).
 * @size: Size modifier for formatting (not used).
 *
 * This function retrieves an unsigned integer argument from the va_list and
 * prints it as a binary number to the standard output.
 *
 * Return: The number of binary digits printed.
 */
int print_binary(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	unsigned int n, m, i, sum;
	unsigned int a[32];
	int count;

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	n = va_arg(types, unsigned int);
	m = 2147483648; /* (2 ^ 31) */
	a[0] = n / m;
	for (i = 1; i < 32; i++)
	{
		m /= 2;
		a[i] = (n / m) % 2;
	}
	for (i = 0, sum = 0, count = 0; i < 32; i++)
	{
		sum += a[i];
		if (sum || i == 31)
		{
			char z = '0' + a[i];

			write(1, &z, 1);
			count++;
		}
	}
	return (count);
}
