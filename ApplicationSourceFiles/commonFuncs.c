#include "xlCANdemo.h"
#include <stdlib.h>
#include <stdio.h>
#include "Can.h"
#include "CanIf.h"
#include "CanSM.h"
#include "PduR.h"
#include "Com.h"
#include "CANoeApi.h"
#include "VttCntrl_Can.h"
#include "ComM.h"

#define COM_STACK_INIT_OK    0U
#define COM_STACK_INIT_NOT_OK  1U

/* Reception */
void can_recieve(uint8 canChannel, uint32 id, uint32 flags, uint8 dataLength, const uint8* data)
{
  Can_RxIndication(canChannel, id, flags, dataLength, data);
}

void can_confirm_transmission(uint8 channelId, uint32 id, uint32 flags, uint8 dataLength, const uint8* data)
{
  Can_TxConfirmation(channelId, id, flags, dataLength, data);
}

void InitializeCan()
{
  /* Initialize CAN */
  Can_InitMemory();
  Can_Init(Can_Config_Ptr);
}

void InitializeCanIf()
{
  /* Initialize CAN IF */
  CanIf_InitMemory();
  CanIf_Init(CanIf_Config_Ptr);
}

uint8 InitializeComStack() 
{
  Std_ReturnType retVal;

  /* Mandatory -> Changes state of CANoeAPI ECU State to ECUSTATE_PROCESSING. Required to be able to send data */
  VttCan_OnStateChange(CANOEAPI_ECUACTION_WAKEUP, CANOEAPI_ECUSTATE_INITIAL, CANOEAPI_ECUSTATE_PROCESSING);

  /* Initialize the CAN XL Demo Interface */
  demo_init(0U, NULL_PTR);

  InitializeCan();

  InitializeCanIf();

  //CanSM_Init(CanSM_Config_Ptr);

  Com_Init(Com_Config_Ptr);

  ComM_Init();

  /* PduR_Init must be called with a NULL_PTR or a valid post-build configuration */
  PduR_Init(PduR_Config_Ptr);

  /* Mandatory -> Changes CAN state from Init to Ready */
  Can_MainFunction_Mode();

  retVal = Can_SetControllerMode(0, CAN_T_START);

  if (retVal != CAN_OK)
  {
	  return COM_STACK_INIT_NOT_OK;
  }

  CanIf_ControllerModeIndication(0, CANIF_CS_STARTED);

  retVal = CanIf_SetPduMode(0, CANIF_SET_ONLINE);

  if (retVal != E_OK)
  {
    return COM_STACK_INIT_NOT_OK;
  }

  Can_MainFunction_Mode();

  return COM_STACK_INIT_OK;
}