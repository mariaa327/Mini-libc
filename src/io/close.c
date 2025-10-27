// SPDX-License-Identifier: BSD-3-Clause

#include <unistd.h>
#include <internal/syscall.h>
#include <stdarg.h>
#include <errno.h>

int close(int fd)
{
	/* TODO: Implement close(). */
	long result = syscall(__NR_close, fd);

	if (result < 0) {
		errno = -result; // se seteaza errno la valoarea pozitiva a erorii
		return -1; // returneaza -1 pentru a indica eroarea
	}

	return (int)result;
}
