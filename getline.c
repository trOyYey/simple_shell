#include "shell.h"


#define CHUNKS 128

/**
 * _getline - Reads an entire line from stream, storing the address of the
 * buffer containing the text into *lineptr
 *
 * @lineptr: Stores the address the text from stream
 * @n: Size allocated for @lineptr
 * @stream: The stream to read from
 *
 * Return: number of bytes read, -1 indicating EOF or failure
 */
ssize_t _getline(char **lineptr, size_t *n,
				 FILE *stream)
{
	static char *temp;
	static short size = 128;

	int fd = fileno(stream); /* convert to a file descriptor */
	*n = size;

	/* temp = malloc(sizeof(char) * *n); /\* initial size *\/ */
	temp = realloc(*lineptr, sizeof(char) * size);

	if (temp == NULL)
		return (-1);

	*lineptr = temp;

	if (fd == STDOUT_FILENO || fd == STDERR_FILENO)
		return (-1);

	if (!fd)
		/* Handle standard input differently */
		return (readFromStdin(lineptr, n, fd));

	/* other streams */
	return (readFromStreams(lineptr, n, fd));
}

/**
 * handle_status - Handles the value to return
 *
 * @lineptr: A pointer to the text
 * @read_bytes: Checks for EOF
 * @bytes_read: Number of bytes read
 *
 * Return: number of bytes read, -1 on failure or EOF
 */
ssize_t handle_status(char **lineptr, ssize_t read_bytes,
					 ssize_t bytes_read)
{
	if (bytes_read > 0)
		return (bytes_read);

	if (read_bytes == -1)
	{
		free(*lineptr);
		return (-1);
	}
	return (-1);
}

/**
 * findNewLine - Finds a new line in @buf
 *
 * @position: The position to start looking from new line from
 * after each calls position updates to the next newline in @buf
 * @buf: The buffer that contains the text
 * @status: Status is 1, to indicate that a new line was not found
 *
 * Return: The index where this new line is found
 */
int findNewLine(const char buf[], int position, short *status)
{
	int i;

	i = position;
	while (buf[i])
	{
		/* found a new line */
		if (buf[i] == '\n')
			return (i);
		i++;
	}
	/* printf("i = %d\n", i); */
	/* no new line found */
	if (i < CHUNKS)
		*status = 1;

	return (i);
}

/**
 * readFromStdin - Reads from standard input stream only
 *
 * @lineptr: A reference to the buffer passed to getline
 * @n: size allocated to the memory @lineptr points to
 * @fd: The file descriptor always 0 for stdin
 *
 * Return: Number of bytes read
 */
ssize_t readFromStdin(char **lineptr, size_t *n, int fd)
{
	 size_t bytes_read;

	 bytes_read = read(fd, *lineptr, CHUNKS);

	 /* handles end of file */
	if (handle_EOF(bytes_read))
		return (-1);

	 /* Terminate on new line */
	if ((*lineptr)[bytes_read - 1] == '\n' && bytes_read < *n)
	{
		(*lineptr)[bytes_read] = '\0'; /* null terminate */
		return (bytes_read);
	}
	while (bytes_read > 0)
	{
		char *temp;

		if (bytes_read >= *n)
		{
			/* Increment as the input size grows */
			*n *= 2;
			temp = realloc(*lineptr, sizeof(char) * *n);

			if (temp == NULL)
				return (-1);

			*lineptr = temp;
		}
		bytes_read += read(fd, *lineptr + bytes_read, CHUNKS);
		/* handles end of file */
		if (handle_EOF(bytes_read))
			return (-1);

		if ((*lineptr)[bytes_read - 1] == '\n')
			break;
	}
	(*lineptr)[bytes_read] = '\0'; /* null terminate */
	return (bytes_read);
}

/**
 * readFromStreams - Reads from other streams apart from standard
 * input
 *
 * @lineptr: A reference to the pointer that stores the text
 * @n: The size to allocate to the memory pointer to by @lineptr
 * @fd: The file descriptor, indicating the stream
 *
 * Return: Number of bytes read from the stream
 */
ssize_t readFromStreams(char **lineptr, size_t *n, int fd)
{
	static char buf[CHUNKS], *temp;
	static short status, strLength, index, position, concat, size = 128;

	temp = realloc(*lineptr, sizeof(char) * size);
	if (temp == NULL)
		return (-1);
	*lineptr = temp;

	if (!position || index >= CHUNKS || status)
	{
		memset(buf, 0, CHUNKS); /* Empty the buffer */
		if (read(fd, buf, CHUNKS) <= 0)
			return (-1);
	}
	while ((index = findNewLine(buf, position, &status)) || !index)
	{
		int dif = index - position + 1;

		if (concat > 0) /* append */
			memcpy(*lineptr + concat, buf + position, dif);
		else
		{
			memset(*lineptr, 0, strlen(*lineptr)), size = CHUNKS; /* Empty the buffer */
			memcpy(*lineptr, buf + position, dif);
		}
		position = index + 1; /* Move past new line */
		if (index >= CHUNKS)
		{ /* End of buffer */
			concat += dif - 1, position = 0, size *= 2, *n = size;
			return (readFromStreams(lineptr, n, fd));
		}
		else
		{ /* new line present */
			concat = 0, strLength = strlen(*lineptr);
			if (!strLength)
				return (-1);
			return (strLength);
		}
	}
	return (-1); /* Failure */
}
