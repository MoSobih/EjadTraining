#include "stdio.h"

#include <Os.h>
#include "EcuM.h"
#include "Com.h"

uint8 InitializeComStack();
long get_ns(void);
#define TASK_DUR (1000000000) /* 10ms ~= 10 Million Nano Seconds */

int main( int argc, const char* argv[] )
{
  unsigned long prev_ns;

  //Os_InitMemory();
  //Os_Init();    /* Init only OS Apis */

  EcuM_Init();    /* start OS never returns */

  if (E_OK != InitializeComStack())
  {
    printf("Initialization Failed, Exit Program.\r\n");
    return 1;
  }

  Os_Task_InitTask();

  unsigned long curr_ns;
  prev_ns = get_ns();

  uint8 data[] = { 0x15,0x22,0x15,0x22,0x15,0x22,0x15,0x22 };
  uint8 recieved_data[8] = { 0 };

  while (TRUE)
  {
    curr_ns = get_ns();
    if (curr_ns - prev_ns > TASK_DUR)
    {
      printf("current secs: %ld\n", curr_ns - prev_ns);

      Com_SendSignal(0, data);
      Com_TriggerIPDUSend(0);
      Com_ReceiveSignal(0, recieved_data);
      Com_ReceiveSignal(1, recieved_data);
      Com_ReceiveSignal(2, recieved_data);

      Os_Task_PeriodicTask();
      prev_ns = curr_ns;
    }
  }

  return 0;
}