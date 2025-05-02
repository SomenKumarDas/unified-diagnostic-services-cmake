/**
 * @file read_data_by_id.h
 * @brief Header file for the Read Data by ID service in the UDS over CAN project.
 * This file contains the function declarations for handling the Read Data by ID service
 * and performing read operations on the ECU.
 * @details The Read Data by ID service allows the tester to request specific data from the ECU
 * based on a given identifier. The ECU responds with the requested data or an error code.
 * This service is commonly used for diagnostics and monitoring purposes.
 * @author Somen Das
 * @date 2023
 */

#ifndef __READ_DATA_BY_ID__H__
#define __READ_DATA_BY_ID__H__

#ifdef __cplusplus
extern "C"
{
#endif

#include "common.h"
#include "uds.h"

    /**
     * @brief Wrapper function for the SID 0x22, which is read data by id.
     * @param rx The UDS packet to process.
     * @param resp_data The returning response data.
     * @param idx The length of the response data.
     * @return True if the operation was successful.
     */
    bool handle_read_data_by_id(UDS_Packet *rx, u8 *resp_data, u16 *idx);

#ifdef __cplusplus
}
#endif

#endif // __READ_DATA_BY_ID__H__