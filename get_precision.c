#include "main.h"

/**
 * get_precision - Retrieves the precision value from a format string.
 * @format: The format string being parsed.
 * @i: A pointer to the current position in the format string.
 * @list: A va_list containing the variable argument list.
 *
 * This function searches for and extracts the precision value from the format
 * string, updating the current position pointer accordingly. The precision
 * value can be specified as a numeric value or as an asterisk (*) followed by
 * an argument from the va_list.
 *
 * Return: The extracted precision value, or -1 if not specified.
 */
int get_precision(const char *format, int *i, va_list list)
{
	int i2 = *i + 1;
	int prec = -1;

	if (format[i2] != '.')
		return (prec);

	prec = 0;

	for (i2 += 1; format[i2] != '\0'; i2++)
	{
		if (is_digit(format[i2]))
		{
			prec *= 10;
			prec += format[i2] - '0';
		}
		else if (format[i2] == '*')
		{
			i2++;
			prec = va_arg(list, int);
			break;
		}
		else
			break;
	}

	*i = i2 - 1;

	return (prec);
}
