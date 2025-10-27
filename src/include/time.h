/* SPDX-License-Identifier: BSD-3-Clause */

#ifndef __TIME_H__
#define __TIME_H__ 1

#ifdef __cplusplus
extern "C" {
#endif

/* Minimal time.h pentru temă */

struct timespec {
    long tv_sec; // secunde
    long tv_nsec; // nanosecunde
};

/* Sleep pentru intervalul din *req; dacă e întrerupt și rem != NULL,
 * scrie timpul rămas în *rem. Returnează 0 la succes, -1 la eroare și setează errno. */
int nanosleep(struct timespec *req, struct timespec *rem);

#ifdef __cplusplus
}
#endif

#endif /* __TIME_H__ */
