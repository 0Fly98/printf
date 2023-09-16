#include "main.h"

/************************* PRINT CHAR *************************/

/**
 * print_char - Handles the formatting and printing of a character.
 * @types: A va_list containing the variable argument list.
 * @buffer: A character array where the formatted data is stored.
 * @flags: Flags for formatting (e.g., left-justify, zero-fill).
 * @width: Minimum field width for printing.
 * @precision: Precision for printing.
 * @size: Size modifier for formatting (e.g., h, l).
 *
 * This function retrieves a character from the va_list and formats it
 * according to the specified flags, width, precision, and size. The
 * formatted character is then written to the buffer.
 *
 * Return: The number of characters written to the buffer.
 */
int print_char(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char c = va_arg(types, int);

	/* Assuming buffer has enough space */
	buffer[0] = c;
	buffer[1] = '\0';

	return (1); /* one character has been written to the buffer */
}

/************************* PRINT A STRING *************************/


/**
 * print_string - Handles the formatting and printing of a string.
 * @types: A va_list containing the variable argument list.
 * @buffer: A character array where the formatted data is stored (not used).
 * @flags: Flags for formatting (e.g., left-justify).
 * @width: Minimum field width for printing.
 * @precision: Maximum number of characters to be printed (not used).
 * @size: Size modifier for formatting (not used).
 *
 * This function retrieves a string argument from the va_list, handles
 * formatting according to specified flags and width, and writes the
 * formatted string to the standard output.
 *
 * Return: The number of characters written to the standard output.
 */
int print_string(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int length = 0;
	char *str = va_arg(types, char *);

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	if (str == NULL)
	{
		str = "(null)";
	}

	length = printf("%s", str);

	return length;
}

/************************* PRINT PERCENT SIGN *************************/


/**
 * print_percent - Handles the formatting and printing of a percent symbol.
 * @types: A va_list containing the variable argument list (not used).
 * @buffer: A character array where the formatted data is stored (not used).
 * @flags: Flags for formatting (not used).
 * @width: Minimum field width for printing (not used).
 * @precision: Maximum number of characters to be printed (not used).
 * @size: Size modifier for formatting (not used).
 *
 * This function prints a single percent symbol to the standard output.
 *
 * Return: Always returns 1, the number of characters printed.
 */
int print_percent(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	UNUSED(types);
	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	printf("%%");
	return 1;
}

/************************* PRINT INT *************************/


/**
 * print_int - Handles the formatting and printing of an integer.
 * @types: A va_list containing the variable argument list.
 * @buffer: A character array where the formatted data is stored.
 * @flags: Flags for formatting (e.g., left-justify, zero-fill).
 * @width: Minimum field width for printing.
 * @precision: Minimum number of digits to be printed (not used).
 * @size: Size modifier for formatting (e.g., h, l).
 *
 * This function retrieves an integer argument from the va_list, handles
 * formatting according to specified flags, width, and size, and writes
 * the formatted integer to the buffer.
 *
 * Return: The number of characters written to the buffer.
 */
int print_int(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int n = va_arg(types, int);

	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	int length = sprintf(buffer, "%d", n);

	return length;
}

/************************* PRINT BINARY *************************/


/**
 * print_binary - Handles the formatting and printing of a binary number.
 * @types: A va_list containing the variable argument list.
 * @buffer: A character array where the formatted data is stored (not used).
 * @flags: Flags for formatting (not used).
 * @width: Minimum field width for printing (not used).
 * @precision: Minimum number of digits to be printed (not used).
 * @size: Size modifier for formatting (not used).
 *
 * This function retrieves an unsigned integer argument from the va_list and
 * prints it as a binary number to the standard output.
 *
 * Return: The number of binary digits printed.
 */
void print_binary_recursive(unsigned int n)
{
    if (n == 0)
        return;

    print_binary_recursive(n / 2);

    printf("%d", n % 2);
}

int print_binary(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	unsigned int n = va_arg(types, unsigned int);

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	print_binary_recursive(n);

	return 1;
}
