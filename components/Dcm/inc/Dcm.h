/**
 * @file Dcm.h
 * @brief Header file for Diagnostic Communication Manager (DCM) module.
 *
 * This file contains the declarations and macros for the DCM module.
 * It is part of the UDS over CAN project.
 *
 * @author Somen Das
 * @date 2023
 */

#ifndef DCM_H
#define DCM_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "common.h"
#include "uds.h"

#define NUM_SERVICES 5

    /* ====== STRUCTURES ====== */

    typedef struct service_functions
    {
        u8 SID;
        bool (*callback_function)(UDS_Packet *rx, u8 *resp_data, u16 *idx);
        bool (*security_check)(UDS_Packet *rx, u8 *resp_data, u16 *idx, u8 dgSess, u8 secAccess);
        u8 diag_sess;
        u8 security_level;
    } service_functions;

    extern service_functions service_table[NUM_SERVICES];

    /* ====== UTILITY ====== */

    /**
     * @brief Initialize the DCM module.
     * This function sets up the necessary configurations for the DCM module.
     * @return void.
     */
    void Dcm_Init(void);

    /**
     * @brief De-initialize the DCM module.
     * This function cleans up the configurations and resources used by the DCM module.
     * @return void.
     */
    void Dcm_DeInit(void);

    /**
     * @brief Main function for the DCM module.
     * This function is called periodically to handle the UDS communication.
     * @return void.
     */
    void Dcm_MainFunction(void);

    /**
     * @brief Set up the service table for referencing the SID wrapper functions.
     * The service table needs to be set up with all implemented UDS routines otherwise
     * they will be unreachable from the event loop.
     * @return void.
     */
    void init_service_table();

    /**
     * @brief Sets the outgoing UDS packet SID and data to report a failure.
     * @param rx The UDS Packet to process.
     * @param resp_data The response data to be edited.
     * @param idx The length of the response data.
     * @param fail_code The failure code of the operation.
     * @return void.
     */
    void set_failure(UDS_Packet *rx, u8 *resp_data, u16 *idx, enum NEG_RESPONSE_CODES fail_code);

    /**
     * @brief Return a pointer to a UDS Packet after processing data received from the bus.
     * @param rx The UDS Packet to process.
     * @param silenceTx The pointer to the flag that mutes any transmission.
     * @return A pointer to an UDS Packet object.
     */
    UDS_Packet *service_handler(UDS_Packet *rx, bool *silenceTx);

    /* ====== SERVICES ====== */

    /**
     * @brief Wrapper function for the subroutine, which returns the state of the internal variables.
     * @param rx The UDS Packet to process.
     * @param resp_data The returning response data to be edited.
     * @param idx The length of the response data.
     * @return void.
     */
    void handle_debug(UDS_Packet *rx, u8 *resp_data, u16 *idx);

    /**
     * @brief Wrapper function for the SID 0x3E, which is the tester present.
     * @param rx The UDS packet to process.
     * @param resp_data The returning response data.
     * @param idx The length of the response data.
     * @return True if the operation was successful.
     */
    bool handle_tester_present(UDS_Packet *rx, u8 *resp_data, u16 *idx);

    // Include necessary headers here

    // Define macros, constants, and types here

    // Declare public functions here

#ifdef __cplusplus
}
#endif

#endif // DCM_H