#include <internal/syscall.h>
#include <internal/arch/x86_64/syscall_list.h>
#include <errno.h>
#include <time.h>

int nanosleep(struct timespec *req, struct timespec *rem)
{
    // req = timpul cat vreau sa dureze nanosleep
    // rem = cat timp a ramas in cazul in care procesul a fost intrerupt
    long result = syscall(__NR_nanosleep, req, rem);
    if (result < 0) {
        errno = -result; // se seteaza errno la valoarea pozitiva a erorii
        return -1; // returneaza -1 pentru a indica eroarea
    }
    return 0;
}
