#include "main.h"

/**
 * print_binary - Prints the binary representation of a number.
 * @n: Unsigned long int, the number to be represented in binary.
 */
void print_binary(unsigned long int n)
{
	if (n > 1)
		print_binary(n >> 1);

	(n & 1) ? _putchar('1') : _putchar('0');
}
