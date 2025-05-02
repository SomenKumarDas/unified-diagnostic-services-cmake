#include "diag_sess_cntl.h"
#include "state.h"
#include "timing.h"
#include "uds.h"
#include "utils.h"

enum SFB_CODES
{
    /* Each SID file has its own SFB codes. */
    DEFAULT_SESSION = 0x1,
    PROGRAM_SESSION = 0x2,
    EXTENDED_SESSION = 0x3,
    SAFETY_SESSION = 0x4,
};

void add_timing_params(u8 *resp_data, u16 *idx)
{
    insertIntoArray(resp_data, (ISOTP_P2 >> 8) & 0xFF, idx);
    insertIntoArray(resp_data, (ISOTP_P2) & 0xFF, idx);
    insertIntoArray(resp_data, (ISOTP_P2_EXT >> 8), idx);
    insertIntoArray(resp_data, (ISOTP_P2_EXT) & 0xFF, idx);
}

bool programming_session(UDS_Packet *rx, u8 *resp_data, u16 *idx)
{
    if (get_state(STATE_DIAGNOSTIC_SESSION) == EXTENDED_SESSION)
    {
        set_failure(rx, resp_data, idx, NRC_SECURITY_ACCESS_DENIED);
        return false;
    }
    set_state(STATE_DIAGNOSTIC_SESSION, PROGRAM_SESSION);
    add_timing_params(resp_data, idx);
    return true;
}

bool extended_session(UDS_Packet *rx, u8 *resp_data, u16 *idx)
{
    if (get_state(STATE_DIAGNOSTIC_SESSION) == PROGRAM_SESSION)
    {
        set_failure(rx, resp_data, idx, NRC_SECURITY_ACCESS_DENIED);
        return false;
    }
    set_state(STATE_DIAGNOSTIC_SESSION, EXTENDED_SESSION);
    add_timing_params(resp_data, idx);
    return true;
}

bool default_session(UDS_Packet *rx, u8 *resp_data, u16 *idx)
{
    set_state(STATE_DIAGNOSTIC_SESSION, DEFAULT_SESSION);
    add_timing_params(resp_data, idx);
    /** @todo generate P2 and P2extended values */
    /** @todo verify consistency in the P2 reply data format */
    return true;
}

bool safety_session(UDS_Packet *rx, u8 *resp_data, u16 *idx)
{
    set_state(STATE_DIAGNOSTIC_SESSION, SAFETY_SESSION);
    return true;
}

bool handle_diag_sess_cntl(UDS_Packet *rx, u8 *resp_data, u16 *idx)
{
    if (!(rx->dataLength == 1))
    {
        set_failure(rx, resp_data, idx, NRC_INCORRECT_MESSAGE_LENGTH);
        return false;
    }
    insertIntoArray(resp_data, rx->data[0], idx);
    bool opSuccess = true;

    switch (rx->data[0])
    {
    case PROGRAM_SESSION:
        opSuccess = programming_session(rx, resp_data, idx);
        break;
    case DEFAULT_SESSION:
        opSuccess = default_session(rx, resp_data, idx);
        break;
    case EXTENDED_SESSION:
        opSuccess = extended_session(rx, resp_data, idx);
        break;
    case SAFETY_SESSION:
        opSuccess = safety_session(rx, resp_data, idx);
        break;
    default:
        set_failure(rx, resp_data, idx, NRC_SERVICE_NOT_SUPPORTED);
        return false;
    }
    return true && opSuccess;
}
