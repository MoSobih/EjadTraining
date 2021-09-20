#ifndef xlCANdemo_H
#define xlCANdemo_H

#include "Platform_Types.h"
/*Initialization */
void demo_init(int argc, char* argv[]);

/* Tranmission */
void demo_send();
void demo_clean_up();
short XLCAN_Transmit(uint8 channelId, uint32 id, uint32 flags, uint8 txReqCount, uint8 dataLength, const uint8* data);

/* Reception */
void can_recieve(uint8 canChannel, uint32 id, uint32 flags, uint8 dataLength, const uint8* data);
void get_can_recieved_data(uint16 CanId, uint8 CanDlc, const uint8* CanSduPtr);
void print_com_recieved_data(const uint8* pduData, const uint8 length);
void can_confirm_transmission(uint8 channelId, uint32 id, uint32 flags, uint8 dataLength, const uint8* data);
#define USE_XL_CAN
#endif // !xlCANdemo_H

