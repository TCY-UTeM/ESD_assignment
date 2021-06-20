#include "stm32f10x.h"
#include "cmsis_os.h"
#include "uart.h"


void get_Thread (void const *argument*);
void add_Thread (void const *argument*);
osThreadDef(get_Thread, osPriorityNormal, 1, 0);
osThreadDef(add_Thread, osPriorityNormal, 1, 0);

osThread T_get;
osThread T_add;

osMutexId x_mutex;
osMutexDef(x_mutex);

osSemaphoreId items;
osSemaphoreDef(items);

osSemaphoreId buffer_size;
osSemaphoreDef (buffer_size);

int *head = 0x00;
int *tail = 0x00;
int max_size = 8;
int y = 0;
int x = 0;

void get_Thread (void const *argument)
{
  for(;;)
  {
  osSemaphoreWait(items, osWaitForever);
  osMutexWait(x_mutex, osWaitForever);
    y = *tail;
    tail++
  osMutexRelease(x_mutex);
  osSemaphoreRelease(buffer_size);
  }
}

void add_Thread (void const *argument)
{
  for(;;)
  {
  osSemaphoreWait(buffer_size, osWaitForever);
  osMutexWait(x_mutex, osWaitForever);
    x = x+2;
    *head = x;
    head+
  osMutexRelease(x_mutex);
  osSemaphoreRelease(items);
}

int main(void)
{
   osKernelInitialize ();        // initialize CMSIS-RTOS

  x_mutex = osMutexCreate(osMutex(x_mutex));
  items = osSemaphoreCreate(osSemaphore(items), 0);
  buffer_size = osSemaphoreCreate(osSemaphore(buffer_size),8);
  T_get = osThreadCreate(osThread(get_Thread), NULL);
  T_add = osThreadCreate(osThread(add_Thread), NULL);

 osKernelStart();               //start thread execution

}


