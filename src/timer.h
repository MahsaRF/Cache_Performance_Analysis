#ifndef __TIMER_H__
#define __TIMER_H__

#include <stdio.h>

#ifdef _WIN32
#include <windows.h>
typedef LARGE_INTEGER TimeType;
#else
#include <sys/time.h>
typedef double TimeType;
#endif

TimeType Wtime();
double Wtime_diff ( TimeType endtime, TimeType starttime );

#endif
