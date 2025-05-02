/**
 * @file ecu_reset.h
 * @brief Header file for the ECU reset service in the UDS over CAN project.
 * This file contains the function declarations for handling the ECU reset service
 * and performing ECU reset operations.
 * @author Somen Das
 * @date 2023
 */

#ifndef __ECU_RESET__H__
#define __ECU_RESET__H__

#ifdef __cplusplus
extern "C"
{
#endif

#include "common.h"
#include "uds.h"

    /**
     * @brief Wrapper function for the SID 0x11, which is the ECU reset.
     * @param rx The UDS packet to process.
     * @param resp_data The returning response data.
     * @param idx The length of the response data.
     * @return True if the operation was successful.
     */
    bool handle_ecu_reset(UDS_Packet *rx, u8 *resp_data, u16 *idx);

#ifdef __cplusplus
}
#endif

#endif // __ECU_RESET__H__
