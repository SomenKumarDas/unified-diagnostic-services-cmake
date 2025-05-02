/**
 * @file security_access.h
 * @brief Header file for the security access service in the UDS over CAN project.
 * This file contains the function declarations for handling the security access service
 * and performing security checks.
 * @author Somen Das
 * @date 2023
 */

#ifndef __SECURITY_ACCESS__H__
#define __SECURITY_ACCESS__H__

#ifdef __cplusplus
extern "C"
{
#endif

// #include "services.h"
#include "uds.h"

    /**
     * @brief Wrapper function for the SID 0x27, which is the security access service.
     * @param rx The UDS packet to process.
     * @param resp_data The returning response data.
     * @param idx The length of the response data.
     * @return True if the operation was successful.
     */
    bool handle_security_access(UDS_Packet *rx, u8 *resp_data, u16 *idx);

    /**
     * @brief Security check for the security access function.
     * @param rx The UDS packet to process.
     * @param resp_data The returning response data.
     * @param idx The length of the response data.
     * @param dgSess The required diagnostic session to be in.
     * @param secAccess The required security level to be in before executing the function.
     * @return True if the security check was passed.
     */
    bool security_check_security_access(UDS_Packet *rx, u8 *resp_data, u16 *idx, u8 dgSess, u8 secAccess);

#ifdef __cplusplus
}
#endif

#endif // __SECURITY_ACCESS__H__