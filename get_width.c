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
	int curr_i;
	int width = 0;

	for (curr_i = *i + 1; format[curr_i] != '\0'; curr_i++)
	{
		if (is_digit(format[curr_i]))
		{
			width *= 10;
			width += format[curr_i] - '0';
		}
		else if (format[curr_i] == '*')
		{
			curr_i++;
			width = va_arg(list, int);
			break;
		}
		else
			break;
	}

	*i = curr_i - 1;

	return (width);
}
