#include "shell.h"

/**
 * handle_EOF - Handles end of file condition from read
 * system call
 *
 * @bytes_read: Number of bytes read from read system call
 *
 * Return: 1 indicating end of file, 0 otherwise
 */
int handle_EOF(size_t bytes_read)
{
	/* End of file */
	if (!bytes_read)
		return (1);

	return (0);
}
