#include <stdio.h>

#include "Dcm.h"

static void diagnostic_session_tests(void);

int main()
{
    printf("Application Started\n");

    Dcm_Init();

    diagnostic_session_tests();

    return 0;
}

void print_UDS_Packet(const char *tag, UDS_Packet *packet)
{
    printf("\n\n");
    printf("%s\n", tag);
    printf("Response SID: %02X Data: [", packet->SID);
    for (int i = 0; i < packet->dataLength; i++)
    {
        printf("%02X ", packet->data[i]);
    }
    printf("]\n\n");
}

static void diagnostic_session_tests(void)
{
    UDS_Packet *tx;
    bool silenceTransmit;

    UDS_Packet rx = {
        .SID = 0x10,
        .data = {0x01, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA},
        .dataLength = 1,
    };

    tx = service_handler(&rx, &silenceTransmit);
    print_UDS_Packet("T1", tx);

    UDS_Packet rx1 = {
        .SID = 0x10,
        .data = {0x01, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA},
        .dataLength = 0,
    };

    tx = service_handler(&rx1, &silenceTransmit);
    print_UDS_Packet("T2", tx);
}