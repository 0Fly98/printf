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
	int curr_i = *i + 1;
	int size = 0;

	if (format[curr_i] == 'l')
		size = S_LONG;
	else if (format[curr_i] == 'h')
		size = S_SHORT;

	if (size == 0)
		*i = curr_i - 1;
	else
		*i = curr_i;

	return (size);
}
