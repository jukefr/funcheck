#include <sys/time.h>
#include <stdio.h>
#include "time.h"

/**
 * @brief Return the current time.
 *
 * @return timeval_t the current time
 */
timeval_t get_time(void)
{
    timeval_t time;
    gettimeofday(&time, NULL);
    return time;
}

/**
 * @brief Return the time lapse between two time in ms.
 * 
 * @param start start time
 * @param end end time
 * @return msseconds_t 
 */
msseconds_t get_timelapse(timeval_t start)
{
    timeval_t end = get_time();
    return (end.tv_sec - start.tv_sec) * 1000
        + (end.tv_usec - start.tv_usec) / 1000;
}

/**
 * @brief return a string representation 10min 30sec for example
 * 
 * @param lapse time lapse in ms
 * @return const char*  string representation
 */
const char *get_time_string(msseconds_t lapse)
{
    static char buffer[1024];
    int seconds = lapse / 1000;
    int minutes = seconds / 60;

    if (minutes > 0)
        sprintf(buffer, "%dmin %ds", minutes, seconds % 60);
    else
        sprintf(buffer, "%dsec", seconds % 60);
    return buffer;
}