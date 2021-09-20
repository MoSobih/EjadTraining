/* Standard C++ headers */
#include <stdio.h>
#include <time.h>

/* Vector Library Headers */
#include "xlCANdemo.h"

/* Autosar C headers */
#include "Os.h"
#include "Os_Hal_Core.h"
#include "Os_Application_Cfg.h"
#include "EcuM.h"
#include "Rte_Main.h"

/*------------------------------------------------------------------*/
/*---------------------------- InitTask ----------------------------*/
/*------------------------------------------------------------------*/

TASK(InitTask)
{
  #ifdef DISABLED_FOR_THE_CURRENT_RELEASE_AS_OS_IS_NOT_FUNCTIONAL_YET
  EcuM_StartupTwo();
  #endif

  (void)Rte_Start();
  #ifdef DISABLED_FOR_THE_CURRENT_RELEASE_AS_OS_IS_NOT_FUNCTIONAL_YET
  (void)TerminateTask();
  #endif
}

/*------------------------------------------------------------------*/
/*---------------------------- Os APIs. ----------------------------*/
/*------------------------------------------------------------------*/

sint32 CANoeEmuProcessor_GetCoreNumber(void)
{
  /* Induction Training is a signle core system. */
  return 0;
}


void CANoeEmuProcessor_SetTaskToRunAndEnableInterrupts(sint32 taskNr)
{
	Os_Hal_CoreId2CurrentContext[0]->Config->Entry(FALSE);
}

/*------------------------------------------------------------------*/
/*---------------------- Communication APIs. -----------------------*/
/*------------------------------------------------------------------*/

void CANoeAPI_SendMessage(uint8 channel, uint32 id, int dlc, volatile uint8 data[8], uint32 flags)
{
  /* TODO: To Be Done */
}

void CANoeAPI_SendCanMessage(uint8 channel, uint32 id, uint32 flags, uint8 txReqCount, uint8 dataLength, const uint8* data)
{
  (void) XLCAN_Transmit(channel, id, flags, txReqCount, dataLength, data);
}

void CANoeAPI_ResetCan(uint8 channel)
{
  /* TODO: To Be Done */
}

void CANoeAPI_SetCanBtr(uint8 channel, uint8 btr0, uint8 btr1)
{
  /* TODO: To Be Done */
}

void CANoeAPI_SetCanConfiguration(uint8 channel,
  double arbBaudrate, uint8 arbTseg1, uint8 arbTseg2,
  uint8 arbSjw, uint8 arbSam, uint32 arbFlags,
  double dbrBaudrate, uint8 dbrTseg1, uint8 dbrTseg2,
  uint8 dbrSjw, uint8 dbrSam, uint32 dbrFlags)
{
  /* TODO: To Be Done */
}

void CANoeAPI_SetCanMsgHandler(VCanMsgHandler test)
{
  /* TODO: To Be Done */
}

void CANoeAPI_SetCanErrHandler(VCanErrHandler test)
{
  /* TODO: To Be Done */
}

void CANoeAPI_WakeupProcessor(void)
{
  /* TODO: To Be Done */
}

/*------------------------------------------------------------------*/
/*--------------------- Error Handling APIs. -----------------------*/
/*------------------------------------------------------------------*/

sint32 CANoeAPI_DetReportError(uint16 moduleId, uint8 instanceId, uint8 apiId, uint8 errorId)
{
  printf("DET Error is reported.\r\n");
  
  printf("DET Error Details:-\r\n");

  printf("Module ID: %d\r\n", moduleId);
  printf("Instance ID: %d\r\n", instanceId);
  printf("API ID: %d\r\n", apiId);
  printf("Error ID: %d\r\n", errorId);

  return 0;
}

void CANoeEmuProcessor_PowerOff(void)
{
  printf("Fatal Error.\r\n");
  while(1){}
}

void CANoeAPI_Printf(const char* format, ...)
{
  printf(format);
}

void CANoeAPI_WriteString(const char* s)
{
  printf("%s", s);
}

void CANoeAPI_DetSetModule(uint16 moduleId, const char* name)
{
  /* Empty Implementation */
}

void CANoeAPI_DetSetFunction(uint16 moduleId, uint8 apiId, const char* name)
{
  /* Empty Implementation */
}

void CANoeAPI_DetSetError(uint16 moduleId, uint8 errorId, const char* name)
{
  /* Empty Implementation */
}

/*------------------------------------------------------------------*/
/*----------------------  APIs. -----------------------*/
/*------------------------------------------------------------------*/

void CANoeAPI_ConsumeTicks(sint32 ticks)
{
  /* TODO: To Be Done */
}

void CANoeAPI_SetInterrupt(sint32 irqNumber)
{
  /* TODO: To Be Done */
}

sint32 CANoeEmuProcessor_MaskInterrupt(sint32 irqNumber)
{
  return 0;  /* TODO: To Be Done */
}

sint32 CANoeEmuProcessor_UnmaskInterrupt(sint32 irqNumber)
{
  return 0;  /* TODO: To Be Done */
}

uint8 CANoeEmuProcessor_DisableInterrupts(void)
{
  return 0;  /* TODO: To Be Done */
}

uint8 CANoeEmuProcessor_EnableInterrupts(void)
{
  return 0;  /* TODO: To Be Done */
}

long get_ns(void)
{
    struct timespec ts;
    timespec_get(&ts, TIME_UTC);
    return (long)ts.tv_sec * 1000000000L + ts.tv_nsec;
}

static unsigned long start_nanos;
static unsigned long prev_nanos;

static void UpdateOsCounterValues()
{
#ifdef DISABLED_FOR_THE_CURRENT_RELEASE_AS_OS_IS_NOT_FUNCTIONAL_YET
  unsigned long nanos;

  nanos = get_ns();

  for(int i=0; i<OS_COUNTERID_COUNT;i++)
  {
    //TODO: Need to find a way to use a generic MACRO for each timer
    if (nanos - prev_nanos > OSTICKDURATION_OsCounter)
    {
      //TODO: Remove debug code
      printf("current secs: %ld\n", nanos - start_nanos);
      IncrementCounter(i);
      prev_nanos = nanos;
    }
  }
#endif
}


void CANoeEmuProcessor_SetTaskToRun(sint32 taskNr)
{
#ifdef DISABLED_FOR_THE_CURRENT_RELEASE_AS_OS_IS_NOT_FUNCTIONAL_YET
  static uint8 FirstRunFlag = TRUE;

  if(TRUE == FirstRunFlag)
  {
    prev_nanos = get_nanos();
    FirstRunFlag = FALSE;
  }

  if (CANOEEMUPROCESSOR_IDLE == taskNr)
  {
    UpdateOsCounterValues();
    Schedule();
  }
  else
  {
    for(int i = 0U; i < OS_CFG_NUM_APP_SYSTEMAPPLICATION_OSCORE0_TASKS; i++)
    {
      int j = OsCfg_App_SystemApplication_OsCore0.TaskRefs[i]->Thread.ContextConfig->CANoeTask.Id;
    }
  }
#endif
}

void CANoeEmuProcessor_RollbackStack(void)
{
  /* TODO: To Be Done */
}

uint32 CANoeEmuHRTimer_GetCounterValue(sint32 hrtIndex)
{
  return 0;  /* TODO: To Be Done */
}

void CANoeEmuProcessor_ConfigureISR(sint32 irqNumber, void (*f)(void))
{
  /* TODO: To Be Done */
}

void CANoeEmuProcessor_ConfigureInterruptPriority(sint32 irqNumber, sint32 level)
{
  /* TODO: To Be Done */
}

void CANoeEmuProcessor_ConfigureInterruptName(sint32 irqNumber, const char* name)
{
  /* TODO: To Be Done */
}

void CANoeEmuProcessor_SetInterruptRoutingMask(sint32 irqNumber, uint32 routingMask)
{
  /* TODO: To Be Done */
}

void CANoeEmuHRTimer_SetIrqNumber(sint32 hrtIndex, sint32 irqNumber)
{
  /* TODO: To Be Done */
}

void CANoeEmuHRTimer_SetSecondsPerTick(sint32 hrtIndex, float64 duration)
{
  /* TODO: To Be Done */
}

void CANoeEmuProcessor_ConfigureTaskFunction(sint32 taskNr, void (*f)(void) )
{
  /* TODO: To Be Done */
}

typedef sint32 CANoeAPI_UserTimer2_Handle;
typedef void(*CANoeAPI_UserTimer2_Handler)(sint32 userparam, const char* name);

CANoeAPI_UserTimer2_Handle CANoeAPI_UserTimer2_Create(const char* name)
{
  return 0;  /* TODO: To Be Done */
}

void CANoeAPI_UserTimer2_Destroy(CANoeAPI_UserTimer2_Handle utHandle)
{
  /* TODO: To Be Done */
}

void CANoeAPI_UserTimer2_SetCallbackFunction(CANoeAPI_UserTimer2_Handle utHandle,
    CANoeAPI_UserTimer2_Handler f,
    sint32 userparam)
    {
  /* TODO: To Be Done */
    }

sint32 CANoeAPI_UserTimer2_SetCyclic(CANoeAPI_UserTimer2_Handle utHandle, sint64 nanoSeconds)
{
  return 0;  /* TODO: To Be Done */
}

sint32 CANoeEmuProcessor_RollbackStackOfTask(sint32 taskNr)
{
  return 0;  /* TODO: To Be Done */
}

void CANoeEmuProcessor_ConfigureTaskName(sint32 taskNr, const char* name)
{
  /* TODO: To Be Done */
}

uint32 CANoeEmuProcessor_InterlockedExchange(volatile uint32* destination, uint32 exchange)
{
  return 0;  /* TODO: To Be Done */
}

void CANoeEmuProcessor_ClearInterrupt(sint32 irqNumber)
{
  /* TODO: To Be Done */
}

sint32 CANoeEmuProcessor_IsInterruptRequested(sint32 irqNumber)
{
  return 0;  /* TODO: To Be Done */
}

sint32 CANoeEmuProcessor_IsInterruptMasked(sint32 irqNumber)
{
  return 0;  /* TODO: To Be Done */
}

void CANoeEmuProcessor_RequestInterruptOnCore(sint32 coreNumber, sint32 irqNumber)
{
  /* TODO: To Be Done */
}

void CANoeEmuProcessor_ConfigureNumberOfTasks(sint32 numberOfTasks)
{
  /* Is This Needed? */  /* TODO: To Be Done */
}

/*------------------------------------------------------------------*/
/*------------------ Below APIs are Not Needed. --------------------*/
/*------------------------------------------------------------------*/

uint32 CANoeAPI_BaseAddressOfDLL(void)
{
  return 0;
}

sint32 CANoeAPI_SysVar_DeclareInt(const char* nameSpace, const char* name, sint32 initValue)
{
  return 0;
}

sint32 CANoeAPI_SysVar_GetInt(sint32 svhandle)
{
  return 0;
}

sint32 CANoeEmuProcessor_GetInterruptLevel(void)
{
  return 0;
}

sint32 CANoeEmuProcessor_SetInterruptLevel(sint32 level)
{
  return 0;
}

void CANoeAPI_SysVar_SetInt(sint32 svhandle, sint32 value){}

void CANoeAPI_ResetProcessor(void){}

void CANoeEmuProcessor_GotoSleep(void){}

void CANoeEmuProcessor_InitInterruptRouter(void){}

void CANoeEmuProcessor_DisableInterruptsAtStartOfISR(uint8 disable){}

void CANoeEmuProcessor_StartCore(sint32 core){}

void CANoeEmuProcessor_SetStartAddr(sint32 core, void (*f)(void)){}

void CANoeEmuHRTimer_SetCompareValue(sint32 hrtIndex, uint32 expirationTime){}

void CANoeAPI_AtomicBegin(void){}

void CANoeAPI_AtomicEnd(void){}