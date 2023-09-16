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
	int curr_i = *i + 1;
	int precision = -1;

	if (format[curr_i] != '.')
		return (precision);

	precision = 0;

	for (curr_i += 1; format[curr_i] != '\0'; curr_i++)
	{
		if (is_digit(format[curr_i]))
		{
			precision *= 10;
			precision += format[curr_i] - '0';
		}
		else if (format[curr_i] == '*')
		{
			curr_i++;
			precision = va_arg(list, int);
			break;
		}
		else
			break;
	}

	*i = curr_i - 1;

	return (precision);
}
