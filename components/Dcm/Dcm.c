#include "Dcm.h"
#include "diag_sess_cntl.h"
#include "ecu_reset.h"
#include "state.h"
#include "security_access.h"
#include "read_data_by_id.h"

u8 resp_data[4096];
service_functions service_table[NUM_SERVICES];

void Dcm_Init(void)
{
    // Initialize the DCM module
    init_service_table();
}

void Dcm_DeInit(void)
{
    // De-initialize the DCM module
}

void Dcm_MainFunction(void)
{
    // Main function for the DCM module
}

void set_failure(UDS_Packet *rx, u8 *resp_data, u16 *idx, enum NEG_RESPONSE_CODES fail_code)
{
    // limit the length to two automatically for sending failure data.
    resp_data[0] = rx->SID;
    resp_data[1] = fail_code;
    *idx = 2;
}

void init_service_table()
{
    service_table[0].SID = SID_DIAGNOSTIC_SESS_CNTL;
    service_table[0].callback_function = handle_diag_sess_cntl;
    service_table[0].security_check = NULL;
    service_table[0].security_level = 0x0;
    service_table[0].diag_sess = 0x1;

    service_table[1].SID = SID_ECU_RESET;
    service_table[1].callback_function = handle_ecu_reset;
    service_table[1].security_check = NULL;
    service_table[1].security_level = 0x0;
    service_table[1].diag_sess = 0x1;

    service_table[2].SID = SID_TESTER_PRESENT;
    service_table[2].callback_function = handle_tester_present;
    service_table[2].security_check = NULL;
    service_table[2].security_level = 0x0;
    service_table[2].diag_sess = 0x1;

    service_table[3].SID = SID_SECURITY_ACCESS_SERVICE;
    service_table[3].callback_function = handle_security_access;
    service_table[3].security_check = security_check_security_access;
    service_table[3].security_level = 0x0;
    service_table[3].diag_sess = 0x2 | 0x3; /* programming/extended diagnostic session */

    service_table[4].SID = SID_READ_DATA_BY_IDENT;
    service_table[4].callback_function = handle_read_data_by_id;
    service_table[4].security_check = NULL;
    service_table[4].security_level = 0x0; /** @todo add the security level check for RDID */
    service_table[4].diag_sess = 0x1;
}

UDS_Packet *service_handler(UDS_Packet *rx, bool *silenceTx)
{
    UDS_Packet *tx;
    u8 response_code = 0x00;
    u16 idx = 0;

    // set_last_client_call();

    for (int i = 0; i < NUM_SERVICES; i++)
    {
        if (rx->SID == service_table[i].SID)
        {
            if (service_table[i].security_check)
            {
                if (!service_table[i].security_check(rx, resp_data, &idx, service_table[i].diag_sess, service_table[i].security_level))
                {
                    response_code = NRC_NEGATIVE_RESPONSE;
                    break;
                }
            }
            if (!service_table[i].callback_function(rx, resp_data, &idx))
            {
                response_code = NRC_NEGATIVE_RESPONSE;
            }
            else
            {
                response_code = rx->SID + 0x40;
            }
            /** @todo add in value checkers and callback function */
        }
    }

    tx = generate_UDS_packet(response_code, resp_data, idx);
    return tx;
}

bool handle_tester_present(UDS_Packet *rx, u8 *resp_data, u16 *idx)
{
    /** @todo under which condition does this function return false? */
    if (rx->dataLength == 0)
    {
        return true;
    }
    return true;
}
