#include "shell.h"

/**
 * getNumLength - Calculates number of digits
 * in a number
 *
 * @number: The number to check
 *
 * Return: The number of digits
 */
int getNumLength(int number)
{
	int len;

	len = 0;
	while (number != 0)
	{
		number /= 10;
		len++;
	}

	return (len);
}

/**
 * toString - converts a number to string
 * representations
 *
 * @number: The number to convert
 *
 * Return: A pointer to the string
 */
char *toString(int number)
{
	char *num;
	bool neg = false;
	int i, length, temp;

	length = getNumLength(number);
	num = malloc(sizeof(char) * length + 1);

	if (number < 0)
	{
		length++;
		neg = true;
		number = -number;
	}

	/* Memory allocating failed */
	if (!num)
	{
		write(STDERR_FILENO, "malloc failed\n", 15);
		exit(EXIT_FAILURE);
	}

	for (i = (length - 1); i >= 0; i--)
	{
		/* convert right most digit to letter */
		if (neg && i == 0)
		{
			/* handles negative number */
			num[i] = '-';
			break;
		}

		temp = number % 10;

		num[i] = temp + '0';
		number /= 10;
	}
	num[length] = '\0'; /* NULL termintate */

	return (num);
}

/**
 * notValid - Checks if the exit status entered contains
 * natural numbers, including zero
 *
 * @status: The status entered
 *
 * Return: 1 if status is not a natural number otherwise 0
 */
int notValid(const char *status)
{
	int i;
	const char *excluding = "-0";


	if (!strcmp(status, excluding))
		return (0);

	i = 0;
	while (status[i])
	{
		if (!(status[i] >= '0' && status[i] <= '9'))
			return (1);
		i++;

	}

	return (0);
}
