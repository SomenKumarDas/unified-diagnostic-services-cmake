/**
 * @file state.h
 * @brief Header file for managing the state of the UDS over CAN module.
 * @author Somen Das
 * @date 2023
 */

#ifndef __STATE__H__
#define __STATE__H__

#ifdef __cplusplus
extern "C"
{
#endif

#include "common.h"
  // #include "session.h"

  /**
   * 0 => Used for maintaining information on device diagnostic session.
   * 1 => Status of the security access service.
   * All individual definitions are in the SERVICES/ files.
   */
  extern u8 DEVICE_STATE[3]; /* All the session states are stored in here. */

  enum STATE_CODES
  {
    STATE_DIAGNOSTIC_SESSION = 0,
    STATE_SECURITY_SERVICE = 1,
  };

#define EXTENDED_SESSION_TIMEOUT 50000
#define SECURITY_REQUEST_TIMEOUT 10000
#define SECURITY_REQUEST_MAX_TRY 3

  /**
   * @brief Sets the last communication with the client to the current time.
   * By design, it is called every time the service_handler() in '/SERVICES/services.h' fires,
   * which means a valid CAN arbitration ID has been detected.
   * @return void.
   */
  void set_last_client_call();

  /**
   * @brief Sets the time of the last security call for the security access service.
   * It is called every time the access_security_escalation() handler is called inside
   * the security access service function wrapper in `/SERVICES/security_access.c`
   * @return void.
   */
  void set_last_security_call();

  /**
   * @brief Sets the session state.
   * @param state The session state to alter.
   * @param code The configuration for the session state.
   * @return void.
   */
  void set_state(enum STATE_CODES state, u8 code);

  /**
   * @brief Gets the session state.
   * @param state The session state to get.
   * @return 1-byte configuration code for the current session state.
   */
  u8 get_state(enum STATE_CODES state);

  /**
   * @brief Called to update the internal server state.
   * This functions as a "maintainer" of sorts, where it sets the relevant states every x or so seconds.
   * For example, this checks if a "tester-present" service has been requested every 5000ms, otherwise
   * it switches from the extended diagnostic session back to the default session.
   * @return void.
   */
  void update_state();

  /**
   * @brief Called to initialize all the state variables to their appropriate values.
   * @return void.
   */
  void state_initialize();

  /**
   * @brief Initialize the security tables present inside the security access wrapper function.
   * This function is defined here for the purpose of convenience so as to not clutter up the services.h header file.
   * The C code for this exists in the *security access wrapper function*.
   * @return void.
   */
  extern void initialize_security_tables();

#ifdef __cplusplus
}
#endif

#endif // __STATE__H__