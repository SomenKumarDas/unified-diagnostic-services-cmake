/**
 * @file diag_sess_cntl.h
 * @brief Header file for Diagnostic Session Control (SID 0x10).
 * @author Somen Das
 * @date 2023
 */

#ifndef __DIAG_SESS_CNTL_H__
#define __DIAG_SESS_CNTL_H__

#ifdef __cplusplus
extern "C"
{
#endif

#include "common.h"
#include "uds.h"
#include "Dcm.h"

    /**
     * @brief Wrapper function for the SID 0x10, which is the diagnostic session control.
     * @param rx The UDS packet to process.
     * @param resp_data The returning response data to be edited.
     * @param idx The length of the the response data.
     * @return True if the operation was successful.
     */
    bool handle_diag_sess_cntl(UDS_Packet *rx, u8 *resp_data, u16 *idx);

#ifdef __cplusplus
}
#endif

#endif // __DIAG_SESS_CNTL_H__