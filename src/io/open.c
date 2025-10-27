// SPDX-License-Identifier: BSD-3-Clause

#include <fcntl.h>
#include <internal/syscall.h>
#include <stdarg.h>
#include <errno.h>

int open(const char *filename, int flags, ...)
{
	/* TODO: Implement open system call. */
	mode_t mode = 0; // permisiunile fisierului
	va_list args; // lista de argumente care sunt variabile
	long result;

	if (flags & O_CREAT) {
		va_start(args, flags);
		mode = va_arg(args, mode_t);
		va_end(args);
	}

	result = syscall(__NR_open, filename, flags, mode);

	if (result < 0) {
		errno = -result; // se seteaza errno la valoarea pozitiva a erorii
		return -1; // returneaza -1 pentru a indica eroarea
	}

	return (int)result;
}
