#include "common.h"
#include "timing.h"
#include <unistd.h>

/* This can stay hidden and work inside the functions. */
struct timeval tp;

u64 getTime()
{
  gettimeofday(&tp, NULL);
  u64 ret_val = (tp.tv_sec * 1000) + (tp.tv_usec / 1000);
  return ret_val;
}

void setTime(u64 *CLOCK_VAR)
{
  gettimeofday(&tp, NULL);
  *CLOCK_VAR = (tp.tv_sec * 1000) + (tp.tv_usec / 1000);
}

bool check_if_timeout(u64 CLOCK_TIME, enum ISO_TP_TIME_LIMITS time_limit)
{
  return getTime() < CLOCK_TIME + time_limit;
}

void _sleep(u64 ms)
{
  u64 curtime;
  setTime(&curtime);
  while (getTime() < curtime + ms)
  {
    ;
  }
}
