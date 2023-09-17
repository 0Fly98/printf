#include "main.h"

/************************* PRINT CHAR *************************/

int print_character(va_list args, char buf[],
	int flg, int wd, int prc, int sz)
{
	char ch = va_arg(args, int);

	return (write_char(ch, buf, flg, wd, prc, sz));
}

/************************* PRINT A STRING *************************/

int print_str(va_list args, char buf[],
	int flg, int wd, int prc, int sz)
{
	int len = 0, i;
	char *s = va_arg(args, char *);

	UNUSED(buf);
	UNUSED(flg);
	UNUSED(wd);
	UNUSED(prc);
	UNUSED(sz);
	if (s == NULL)
	{
		s = "(null)";
		if (prc >= 6)
			s = " ";
	}

	while (s[len] != '\0')
		len++;

	if (prc >= 0 && prc < len)
		len = prc;

	if (wd > len)
	{
		if (flg & F_MINUS)
		{
			write(1, &s[0], len);
			for (i = wd - len; i > 0; i--)
				write(1, " ", 1);
			return (wd);
		}
		else
		{
			for (i = wd - len; i > 0; i--)
				write(1, " ", 1);
			write(1, &s[0], len);
			return (wd);
		}
	}

	return (write(1, s, len));
}

/************************* PRINT PERCENT SIGN *************************/

int print_pct(va_list args, char buf[],
	int flg, int wd, int prc, int sz)
{
	UNUSED(args);
	UNUSED(buf);
	UNUSED(flg);
	UNUSED(wd);
	UNUSED(prc);
	UNUSED(sz);
	return (write(1, "%%", 1));
}

/************************* PRINT INT *************************/

int print_integer(va_list args, char buf[],
	int flg, int wd, int prc, int sz)
{
	int idx = BUFF_SIZE - 2;
	int is_neg = 0;
	long int num = va_arg(args, long int);
	unsigned long int n;

	num = convert_size_number(num, sz);

	if (num == 0)
		buf[idx--] = '0';

	buf[BUFF_SIZE - 1] = '\0';
	n = (unsigned long int)num;

	if (num < 0)
	{
		n = (unsigned long int)((-1) * num);
		is_neg = 1;
	}

	while (n > 0)
	{
		buf[idx--] = (n % 10) + '0';
		n /= 10;
	}

	idx++;

	return (write_number(is_neg, idx, buf, flg, wd, prc, sz));
}

/************************* PRINT BINARY *************************/

int print_bin(va_list args, char buf[],
	int flg, int wd, int prc, int sz)
{
	unsigned int n;
	unsigned int m = 2147483648; /* (2 ^ 31) */
	unsigned int a[32];
	int count;

	UNUSED(buf);
	UNUSED(flg);
	UNUSED(wd);
	UNUSED(prc);
	UNUSED(sz);

	n = va_arg(args, unsigned int);

	a[0] = n / m;
	for (int i = 1; i < 32; i++)
	{
		m /= 2;
		a[i] = (n / m) % 2;
	}
	for (int i = 0; i < 32; i++)
	{
		char z = '0' + a[i];

		write(1, &z, 1);
		count++;

			count++;
		}
	}
	return (count);
}
