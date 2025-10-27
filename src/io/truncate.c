// SPDX-License-Identifier: BSD-3-Clause

#include <unistd.h>
#include <internal/syscall.h>
#include <errno.h>

int truncate(const char *path, off_t length)
{
	/* TODO: Implement truncate(). */
	long result = syscall(__NR_truncate, path, length);

	if (result < 0) {
		errno = -result; // se seteaza errno la valoarea pozitiva a erorii
		return -1; // returneaza -1 pentru a indica eroarea
	}

	return (int)result;
}
