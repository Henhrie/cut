#include "main.h"

/**
 * get_bit - Returns the value of a bit at a given index.
 * @n: Unsigned long int to search.
 * @index: Index to return.
 *
 * Return: The value of the bit at index or -1 if an error occurs.
 */
int get_bit(unsigned long int n, unsigned int index)
{
	if (index > 53)
		return (-1);

	return ((n >> index) & 1);
}
