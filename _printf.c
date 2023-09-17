#include "main.h"

void print_buffer(char buffer[], int *buff_ind);

/**
 * _printf - Custom printf function that handles formatting and printing.
 * @format: A string containing format specifiers.
 * @...: Variable number of arguments to be formatted and printed.
 *
 * Return: The number of characters printed (excluding the null byte).
 *         Returns -1 on error.
 */

int _printf(const char *format, ...)
{
	int idx, count = 0, total_chars = 0;
	int flags, width, precision, size, buffer_idx = 0;
	va_list args;
	char buffer[BUFF_SIZE];

	if (format == NULL)
		return (-1);

	va_start(args, format);

	for (idx = 0; format && format[idx] != '\0'; idx++)
	{
		if (format[idx] != '%')
		{
			buffer[buffer_idx++] = format[idx];
			if (buffer_idx == BUFF_SIZE)
				print_buffer(buffer, &buffer_idx);
			total_chars++;
		}
		else
		{
			print_buffer(buffer, &buffer_idx);
			flags = get_flags(format, &idx);
			width = get_width(format, &idx, args);
			precision = get_precision(format, &idx, args);
			size = get_size(format, &idx);
			idx++;
			count = handle_print(format, &idx, args, buffer,
				flags, width, precision, size);
			if (count == -1)
				return (-1);
			total_chars += count;
		}
	}

	print_buffer(buffer, &buffer_idx);

	va_end(args);

	return (total_chars);
}

/**
 * output_buffer - Outputs the contents of a buffer to the standard output.
 * @buf: A character array containing the data to be printed.
 * @buf_idx: A pointer to the current index in the buffer.
 *
 * This function is used to flush the contents of the buffer to the standard
 * output when it is full or when printing is needed. After printing, the
 * buffer index is reset to zero.
 */
void output_buffer(char buf[], int *buf_idx)
{
	if (*buf_idx > 0)
		write(1, &buf[0], *buf_idx);

	*buf_idx = 0;
}
