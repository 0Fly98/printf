#include "main.h"

/**
 * get_width - Retrieves the minimum field width from a format string.
 * @format: The format string being parsed.
 * @i: A pointer to the current position in the format string.
 * @list: A va_list containing the variable argument list.
 *
 * This function searches for and extracts the minimum field width from the
 * format string, updating the current position pointer accordingly. The width
 * value can be specified as a numeric value or as an asterisk (*) followed by
 * an argument from the va_list.
 *
 * Return: The extracted minimum field width value.
 */

int get_width(const char *format, int *i, va_list list)
{
	int i2;
	int wid = 0;

	for (i2 = *i + 1; format[i2] != '\0'; i2++)
	{
		if (is_digit(format[i2]))
		{
			wid *= 10;
			wid += format[i2] - '0';
		}
		else if (format[i2] == '*')
		{
			i2++;
			wid = va_arg(list, int);
			break;
		}
		else
			break;
	}

	*i = i2 - 1;

	return (wid);
}
