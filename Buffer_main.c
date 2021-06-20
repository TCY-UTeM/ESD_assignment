#include "stm32f10x.h"
#include "cmsis_os.h"
#include "uart.h"

void chef_1(void const *argument);      //chef_1
void chef_2(void const *argument);      //chef_2
void waiter_1(void const *argument);    //waiter_1
void waiter_2(void const *argument);    //waiter_2
void cashier(void const *argument);     //cashier

osThreadDef(chef_1, osPriorityNormal, 1, 0);
osThreadDef(chef_2, osPriorityNormal, 1, 0);
osThreadDef(waiter_1, osPriorityAboveNormal, 1, 0);
osThreadDef(waiter_2, osPriorityAboveNormal, 1, 0);
osThreadDef(cashier, osPriorityAboveNormal, 1, 0);

osThreadId T_chef_1;
osThreadId T_chef_2;
osThreadId T_waiter_1;
osThreadId T_waiter_2;
osThreadId T_cashier;

osMutexId x_mutex;
osMutexDef(x_mutex);

osSemaphoreId items_1;

osSemaphoreDef(items_1);
osSemaphoreId items_2;

osSemaphoreDef(items_2);

osSemaphoreId space_1;

osSemaphoreDef(items_1);
osSemaphoreId items_2;

osSemaphore space_1;

osSemaphoreDef(space_1);
osSemaphoreId space_2;

osSemaphoreDef(space_1);
osSemaphoreId space_2;

osSemaphoreDef(space_1);
osSemaphoreId space_2;

osSemaphoreDef(space_2);

const unsigned int N = 8;
unsigned char buffer_1[N];
const unsigned int max_size = 8;
unsigned char buffer_2[max_size];
unsigned int head_1 = 0;
unsigned int tail_1 = 0;
unsigned int head_2 = 0;
unsigned int tail_2 = 0;
unsigned char x = 0x30;
unsigned char y = 0x41;

unsigned char get_1 ()
{

  unsigned int result = 0xff;
  osSemaphoreWait(items_1, osWaitForever);
  osMutexWait(x_mutex, osWaitForever);
  result = buffer_1[tail_1];
  tail_1 = (tail_1 + 1) % N;
  osMutexRelease(x_mutex);
  osSemaphoreRelease(space_1);
  return result;
}

unsigned char get_2()
{

   unsigned int res = 0xff;
   osSemaphoreWait(items_2, osWaitForever);
   osMutexWait(x_mutex, osWaitForever);
   res = buffer_2[tail_2];
   tail_2 = (tail_2 + 1) % max_size;
   osMutexRelease(x_mutex);
   osSemaphoreRelease(space_2);
   return res;
}

void add_2 (unsigned char value_1)
{
    osSemaphoreWait(space_2, osWaitForever);
    osMutexWait(x_mutex, osWaitForever);
    res = buffer_2[tail_2];
    tail_2 = (tail_2 +1) % max_size;
    osMutexRelease(x_mutex);
    osSemaphoreRelease(space_2);
    return res;
}
void add_2 (unsigned char value_1)
{
     osSemaphoreWait(space_2, osWaitForever);
     osMutexWait(x_mutex, osWaitForever);
     buffer_2[head_2] = value_1;
     head_2 =(head_2 + 1) % max_size;
     osMutexRelease(x_mutex);
     osSemaphoreRelease(items_2);
}

void chef_1 (void const *argument) //chef_1
{

}

void chef_2 (void const *argument) //chef_2
{

}

void waiter_1 (void const *argument) //waiter_1
{

}

void waiter_2 (void const *argument) //waiter_2
{

}

void chashier (void const *argument) //cashier
{

}


int main(void)
{

    osKernelInitialize ();      //initialize CMSIS_RTOS

    USART1_Init ();
    x_mutex = osMutexCreate(osMutex(x_mutex));
    items_1 = osSemaphoreCreate(osSemaphore(items_1), 0);
    space_1 = osSemaphoreCreate(osSemaphore(space_1), N);
    items_2 = osSemaphoreCreate(osSemaphore(items_2), 0);
    space_2 = osSemaphoreCreate(osSemaphore(space_2), N);
    T_chef_1= osThreadCreate(osThread(chef_1), NULL);
    T_chef_2= osThreadCreate(osThread(chef_2), NULL);
    T_waiter_1= osThreadCreate(osThread(waiter_1), NULL);
    T_waiter_2= osThreadCreate(osThread(waiter_2), NULL);
    T_cashier = osThreadCreate(osThread(cashier_1), NULL);
    
    osKernerStart ();          //start Thread execution
}


