#include "main.h"

/**
 * get_flags - Retrieves formatting flags from a format string.
 * @format: The format string being parsed.
 * @i: A pointer to the current position in the format string.
 *
 * This function searches for and collects formatting flags from the format
 * string, updating the current position pointer accordingly.
 *
 * Return: An integer representing the collected flags.
 */

int get_flags(const char *format, int *i)
{
	int j, i2;
	int flag = 0;
	const char FLAGS_CH[] = {'-', '+', '0', '#', ' ', '\0'};
	const int FLAGS_ARR[] = {F_MINUS, F_PLUS, F_ZERO, F_HASH, F_SPACE, 0};

	for (i2 = *i + 1; format[i2] != '\0'; i2++)
	{
		for (j = 0; FLAGS_CH[j] != '\0'; j++)
		{
			if (format[i2] == FLAGS_CH[j])
			{
				flag |= FLAGS_ARR[j];
				break;
			}
		}

		if (FLAGS_CH[j] == 0)
			break;
	}

	*i = i2 - 1;

	return (flag);
}
