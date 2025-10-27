// SPDX-License-Identifier: BSD-3-Clause

#include <unistd.h>
#include <internal/syscall.h>
#include <errno.h>

int ftruncate(int fd, off_t length)
{
	/* TODO: Implement ftruncate(). */
	long result = syscall(__NR_ftruncate, fd, length);

	if (result < 0) {
		errno = -result; // se seteaza errno la valoarea pozitiva a erorii
		return -1; // returneaza -1 pentru a indica eroarea
	}

	return (int)result;
}
