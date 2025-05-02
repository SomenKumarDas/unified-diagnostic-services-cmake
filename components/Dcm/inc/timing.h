/**
 * @file timing.h
 * @brief Header file for timing functions used in the UDS over CAN project.
 * @author Somen Das
 * @date 2023
 */

#ifndef __TIMING_H__
#define __TIMING_H__

#ifdef __cplusplus
extern "C"
{
#endif

#include "common.h"
#include <sys/time.h>

#define CLOCK_CYCLE 500

  /**
   * A -> sending first or single
   * B -> rx frames
   * C -> consec frame
   */
  /** @todo Check these values to be as least as possible. */
  enum ISO_TP_TIME_LIMITS
  {
    ISOTP_N_As = 1000,
    ISOTP_N_Bs = 1000,
    ISOTP_N_Cs = 500,

    ISOTP_N_Ar = 1000,
    ISOTP_N_Br = 1000,
    ISOTP_N_Cr = 5000,

    ISOTP_P2 = 25,
    ISOTP_P2_EXT = 2000
  };

  extern u64 CLOCK_TIME_AT_TX;
  extern u64 CLOCK_TIME_AT_RX;

  /**
   * @brief Gets the current UNIX timestamp.
   * @return Current UNIX timestamp.
   * @todo remove dependency on OS time() calls.
   */
  u64 getTime();

  /**
   * @brief Sets the current UNIX timestamp inside the passed variable.
   * @param CLOCK_VAR The 64-bit unsigned integer to put the timestamp in.
   * @return void.
   * @todo remove dependency on OS time() calls.
   */
  void setTime(u64 *VAR);

  /**
   * @brief Used to check if an activity has happened within time limits.
   * @param CLOCK_TIME The UNIX timestamp to be used for reference.
   * @param time_limit The time limit to check.
   * @return True if the time limit has not been exceeded.
   * */
  bool check_if_timeout(u64 CLOCK_TIME, enum ISO_TP_TIME_LIMITS time_limit);

  /**
   * @brief Hangs the current thread until for a defined period of time.
   * @param ms The amount of time to hang the thread in milli-secondds.
   * @return void.
   * @todo remove dependency on OS time() calls.
   */
  void _sleep(u64 ms);

#ifdef __cplusplus
}
#endif

#endif // __TIMING_H__
