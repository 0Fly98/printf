#include "main.h"

void output_to_buffer(char buf[], int *buf_idx);

/**
 * _printf - Printf function
 * @format: format.
 * Return: Printed chars.
 */
int _printf(const char *format, ...)
{
	int idx, count = 0, total_chars = 0;
	int flags, width, precision, size, buffer_idx = 0;
	va_list args;
	char buf[BUFF_SIZE];

	if (format == NULL)
		return (-1);

	va_start(args, format);

	for (idx = 0; format && format[idx] != '\0'; idx++)
	{
		if (format[idx] != '%')
		{
			buf[buffer_idx++] = format[idx];
			if (buffer_idx == BUFF_SIZE)
				output_to_buffer(buf, &buffer_idx);
			total_chars++;
		}
		else
		{
			output_to_buffer(buf, &buffer_idx);
			flags = get_flags(format, &idx);
			width = get_width(format, &idx, args);
			precision = get_precision(format, &idx, args);
			size = get_size(format, &idx);
			idx++;
			count = handle_print(format, &idx, args, buf,
				flags, width, precision, size);
			if (count == -1)
				return (-1);
			total_chars += count;
		}
	}

	output_to_buffer(buf, &buffer_idx);

	va_end(args);

	return (total_chars);
}

/**
 * output_to_buffer - Outputs the contents of the buffer if it exist
 * @buf: Array of chars
 * @buf_idx: Index at which to add next char, represents the length.
 */
void output_to_buffer(char buf[], int *buf_idx)
{
	if (*buf_idx > 0)
		write(1, &buf[0], *buf_idx);

	*buf_idx = 0;
}
