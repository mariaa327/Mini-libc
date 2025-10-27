// SPDX-License-Identifier: BSD-3-Clause

#include <internal/io.h>
#include <internal/types.h>
#include <errno.h>
#include <stdio.h>


int puts(char *str)
{
    if (!str)
        return -1;

    size_t len = 0;
    while (str[len] != '\0')
        len++; // calculez lungimea sirului

    // scrie sirul
    if (len > 0) {
        ssize_t ret = write(1, str, len);
        if (ret < 0)
            return -1;
    }

    // adauga newline-ul
    ssize_t ret2 = write(1, "\n", 1);
    if (ret2 < 0)
        return -1;

    return 0;
}
