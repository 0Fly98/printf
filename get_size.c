#include "main.h"

/**
 * get_size - Retrieves the size modifier from a format string.
 * @format: The format string being parsed.
 * @i: A pointer to the current position in the format string.
 *
 * This function searches for and extracts the size modifier from the format
 * string, updating the current position pointer accordingly. The size modifier
 * can be 'l' for long or 'h' for short.
 *
 * Return: The extracted size modifier value
 *			(S_LONG or S_SHORT), or 0 if not found.
 */
int get_size(const char *format, int *i)
{
	int i2 = *i + 1;
	int s = 0;

	if (format[i2] == 'l')
		s = S_LONG;
	else if (format[i2] == 'h')
		s = S_SHORT;

	if (s == 0)
		*i = i2 - 1;
	else
		*i = i2;

	return (s);
}
