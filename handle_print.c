#include "main.h"


/**
 * handle_print - Handles the formatting and printing of various data types.
 * @fmt: The format string containing format specifiers.
 * @ind: A pointer to the current position in the format string.
 * @list: A va_list containing the variable argument list.
 * @buffer: A character array where the formatted data is stored.
 * @flags: Flags for formatting (e.g., minus, plus, zero-fill).
 * @width: Minimum field width for printing.
 * @precision: Minimum number of digits to be printed.
 * @size: Size modifier for formatting (e.g., long, short).
 *
 * This function processes format specifiers in the format string, extracts
 * corresponding arguments from the va_list, and prints the formatted data to
 * the buffer. It supports a variety of format specifiers for different data
 * types.
 *
 * Return: The number of characters written to the buffer or -1 on failure.
 */



int handle_print(const char *fmt, int *ind, va_list list, char buffer[],
	int flags, int width, int precision, int size)
{
	int i, len = 0, chars = -1;
	fmt_t fmt_types[] = {
		{'c', print_char}, {'s', print_string}, {'%', print_percent},
		{'i', print_int}, {'d', print_int}, {'b', print_binary},
		{'u', print_unsigned}, {'o', print_octal}, {'x', print_hexadecimal},
		{'X', print_hexa_upper}, {'p', print_pointer}, {'S', print_non_printable},
		{'r', print_reverse}, {'R', print_rot13string}, {'\0', NULL}
	};
	for (i = 0; fmt_types[i].fmt != '\0'; i++)
		if (fmt[*ind] == fmt_types[i].fmt)
			return (fmt_types[i].fn(list, buffer, flags, width, precision, size));

	if (fmt_types[i].fmt == '\0')
	{
		if (fmt[*ind] == '\0')
			return (-1);
		len += write(1, "%%", 1);
		if (fmt[*ind - 1] == ' ')
			len += write(1, " ", 1);
		else if (width)
		{
			--(*ind);
			while (fmt[*ind] != ' ' && fmt[*ind] != '%')
				--(*ind);
			if (fmt[*ind] == ' ')
				--(*ind);
			return (1);
		}
		len += write(1, &fmt[*ind], 1);
		return (len);
	}
	return (chars);
}
