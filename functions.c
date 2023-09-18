#include "main.h"

/************************* PRINT CHARACTER *************************/

/**
 * print_char - Prints a character
 * @arg_list: List of arguments
 * @buf: Buffer array to handle print
 * @flag: Calculates active flags
 * @wid: Width
 * @prec: Precision specification
 * @sz: Size specifier
 * Return: Number of characters printed
 */
int print_char(va_list arg_list, char buf[],
	int flag, int wid, int prec, int sz)
{
	char character = va_arg(arg_list, int);

	return (handle_write_char(character, buf, flag, wid, prec, sz));
}
/************************* PRINT A STRING *************************/
/**
 * print_string - Prints a string
 * @arg_list: List of arguments
 * @buf: Buffer array to handle print
 * @flag: Calculates active flags
 * @wid: Width.
 * @prec: Precision specification
 * @sz: Size specifier
 * Return: Number of characters printed
 */
int print_string(va_list arg_list, char buf[],
	int flag, int wid, int prec, int sz)
{
	int str_len = 0, index;
	char *string = va_arg(arg_list, char *);

	UNUSED(buf);
	UNUSED(flag);
	UNUSED(wid);
	UNUSED(prec);
	UNUSED(sz);
	if (string == NULL)
	{
		string = "(null)";
		if (prec >= 6)
			string = " ";
	}

	while (string[str_len] != '\0')
		str_len++;

	if (prec >= 0 && prec < str_len)
		str_len = prec;

	if (wid > str_len)
	{
		if (flag & F_MINUS)
		{
			write(1, &string[0], str_len);
			for (index = wid - str_len; index > 0; index--)
				write(1, " ", 1);
			return (wid);
		}
		else
		{
			for (index = wid - str_len; index > 0; index--)
				write(1, " ", 1);
			write(1, &string[0], str_len);
			return (wid);
		}
	}

	return (write(1, string, str_len));
}

/************************* PRINT PERCENT SIGN *************************/

/**
 * print_percent - Prints a percent sign
 * @arg_list: List of arguments
 * @buf: Buffer array to handle print
 * @flag: Calculates active flags
 * @wid: Width
 * @prec: Precision specification
 * @sz: Size specifier
 * Return: Number of characters printed
 */
int print_percent(va_list arg_list, char buf[],
	int flag, int wid, int prec, int sz)
{
	UNUSED(arg_list);
	UNUSED(buf);
	UNUSED(flag);
	UNUSED(wid);
	UNUSED(prec);
	UNUSED(sz);
	return (write(1, "%%", 1));
}

/************************* PRINT INTEGER *************************/

/**
 * print_int - Prints an integer
 * @arg_list: List of arguments
 * @buf: Buffer array to handle print
 * @flag: Calculates active flags
 * @wid: Width.
 * @prec: Precision specification
 * @sz: Size specifier
 * Return: Number of characters printed
 */
int print_int(va_list arg_list, char buf[],
	int flag, int wid, int prec, int sz)
{
	int index = BUFF_SIZE - 2;
	int is_neg = 0;
	long int num = va_arg(arg_list, long int);
	unsigned long int abs_num;

	num = convert_size_number(num, sz);

	if (num == 0)
		buf[index--] = '0';

	buf[BUFF_SIZE - 1] = '\0';
	abs_num = (unsigned long int)num;

	if (num < 0)
	{
		abs_num = (unsigned long int)((-1) * num);
		is_neg = 1;
	}

	while (abs_num > 0)
	{
		buf[index--] = (abs_num % 10) + '0';
		abs_num /= 10;
	}

	index++;

	return (write_number(is_neg, index, buf, flag, wid, prec, sz));
}

/************************* PRINT BINARY *************************/
/**
 * print_binary - Prints an unsigned number
 * @types: Lista of arguments
 * @buffer: Buffer array to handle print
 * @flags: Calculates active flags
 * @width: get width.
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Numbers of char printed.
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
