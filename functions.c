#include "main.h"

/************************* PRINT CHAR *************************/

/**
 * Function: print_char
 * Description: This function prints a character.
 * @types: Argument list.
 * @buffer: An array used for printing.
 * @flags: Used to calculate active flags.
 * @width: Specifies the width.
 * @precision: Specifies the precision.
 * @size: Specifies the size.
 * Return: The function returns the number of characters printed.
 */

int print_char(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char t = va_arg(types, int);

	return (handle_write_char(t, buffer, flags, width, precision, size));
}
/************************* PRINT A STRING *************************/
/**
 * Function: print_string
 * Description: This function is responsible for printing a string.
 * @types: A list of arguments.
 * @buffer: An array that is used for handling print operations.
 * @flags: Used for calculating active flags.
 * @width: Specifies the width.
 * @precision: Specifies the precision.
 * @size: Specifies the size.
 * Return: Returns the number of characters that were printed.
 */

int print_string(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int length = 0, u;
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
			for (u = width - length; u > 0; u--)
				write(1, " ", 1);
			return (width);
		}
		else
		{
			for (u = width - length; u > 0; u--)
				write(1, " ", 1);
			write(1, &str[0], length);
			return (width);
		}
	}

	return (write(1, str, length));
}
/************************* PRINT PERCENT SIGN *************************/
/**
 * Function: print_percent
 * Description: This function is designed to print a percent sign.
 * @types: A list of arguments.
 * @buffer: An array used for handling print operations.
 * @flags: Used for calculating active flags.
 * @width: Specifies the width.
 * @precision: Specifies the precision.
 * @size: Specifies the size.
 * Return: Returns the number of characters that were printed.
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
 * Function: print_int
 * Description: This function is used to print an integer.
 * @types: A list of arguments.
 * @buffer: An array used for handling print operations.
 * @flags: Used for calculating active flags.
 * @width: Specifies the width.
 * @precision: Specifies the precision.
 * @size: Specifies the size.
 * Return: Returns the number of characters that were printed.
 */
int print_int(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int u = BUFF_SIZE - 2;
	int is_negative = 0;
	long int n = va_arg(types, long int);
	unsigned long int num;

	k = convert_size_number(k, size);

	if (k == 0)
		buffer[u--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';
	num = (unsigned long int)k;

	if (k < 0)
	{
		num = (unsigned long int)((-1) * k);
		is_negative = 1;
	}

	while (num > 0)
	{
		buffer[i--] = (num % 10) + '0';
		num /= 10;
	}

	u++;

	return (write_number(is_negative, u, buffer, flags, width, precision, size));
}

/************************* PRINT BINARY *************************/
/**
 * Function: print_binary
 * Description: This function is used to print an unsigned number.
 * @types: A list of arguments.
 * @buffer: An array used for handling print operations.
 * @flags: Used for calculating active flags.
 * @width: Specifies the width.
 * @precision: Specifies the precision.
 * @size: Specifies the size.
 * Return: Returns the number of characters that were printed.
 */
int print_binary(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	unsigned int k, h, u, sum;
	unsigned int p[32];
	int count;

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	k = va_arg(types, unsigned int);
	h = 2147483648; /* (2 ^ 31) */
	p[0] = k / h;
	for (u = 1; u < 32; u++)
	{
		h /= 2;
		p[i] = (k / h) % 2;
	}
	for (u = 0, sum = 0, count = 0; u < 32; u++)
	{
		sum += p[u];
		if (sum || u == 31)
		{
			char b = '0' + p[u];

			write(1, &b, 1);
			count++;
		}
	}
	return (count);
}
