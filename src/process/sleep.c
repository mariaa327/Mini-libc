#include <time.h>
#include <unistd.h>

unsigned int sleep(unsigned int seconds)
{
    struct timespec req, rem;
    req.tv_sec = seconds;
    req.tv_nsec = 0;

    if (nanosleep(&req, &rem) == 0)
        return 0;

    //daca a fost intrerupt intoarce secunde ramase
    if (rem.tv_sec >= 0)
        return (unsigned int)rem.tv_sec;

    return seconds;
}
