// SPDX-License-Identifier: BSD-3-Clause

#include <internal/io.h>
#include <internal/syscall.h>
#include <internal/types.h>
#include <errno.h>

ssize_t write(int fd, const void *buf, size_t len)
{
	long result = syscall(__NR_write, fd, buf, len);

	if (result < 0) {
		errno = -result; // se seteaza errno la valoarea pozitiva a erorii
		return -1; // returneaza -1 pentru a indica eroarea
	}

	return result;
}

ssize_t read(int fd, void *buf, size_t len)
{
	long result =  syscall(__NR_read, fd, buf, len);

	if (result < 0) {
		errno = -result; // se seteaza errno la valoarea pozitiva a erorii
		return -1; // returneaza -1 pentru a indica eroarea
	}

	return result;
}
