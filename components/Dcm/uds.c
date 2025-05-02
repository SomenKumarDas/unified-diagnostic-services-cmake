#include "uds.h"

/* uds_tx will be used for all outbound transmissions. */
UDS_Packet uds_tx;
/* uds_rx will be used for all inbound transmissions. */
UDS_Packet uds_rx;

/**
 * @todo Re-initialize the statically allocated memory if needed.
 */

UDS_Packet *generate_UDS_packet(u8 SID, u8 *data, u16 dataLength)
{
  uds_tx.SID = SID;
  // uds_tx.data = data;
  if (data != NULL)
    memcpy(uds_tx.data, data, dataLength);
  uds_tx.dataLength = dataLength;
  return &uds_tx;
}
