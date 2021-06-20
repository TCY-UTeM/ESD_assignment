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
osThreadDef(cashier, osPriorityHigh, 1, 0);

osThreadId T_chef_1;
osThreadId T_chef_2;
osThreadId T_waiter_1;
osThreadId T_waiter_2;
osThreadId T_cashier;

osMutexId x_mutex;
osMutexDef(x_mutex);

osSemaphoreId ren_1;
osSemaphoreDef(ren_1);
osSemaphoreId ren_2;
osSemaphoreDef(ren_2);

osSemaphoreId items_1;
osSemaphoreDef(items_1);
osSemaphoreId items_2;
osSemaphoreDef(items_2);

osSemaphoreId space_1;
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

  unsigned int result = 0;
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

   unsigned int res = 0;
   osSemaphoreWait(items_2, osWaitForever);
   osMutexWait(x_mutex, osWaitForever);
   res = buffer_2[tail_2];
   tail_2 = (tail_2 + 1) % max_size;
   osMutexRelease(x_mutex);
   osSemaphoreRelease(space_2);
   return res;
}

void add_1 (unsigned char value)
{
    osSemaphoreWait(space_1, osWaitForever);
    osMutexWait(x_mutex, osWaitForever);
    buffer_1[head_1] = value;
    head_1 = (head_1 + 1) % N;
    osMutexRelease(x_mutex);
    osSemaphoreRelease(items_1);
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
    for(;;)
    {
	a:
	if(x<0x38)
	{
	  add_1(x++);
	  osDelay(1);
	}
	else
	{
	  x = 0x30;
	  goto a;
	}
    }
}

void chef_2 (void const *argument) //chef_2
{
    for(;;)
    {
	b:
	if(x<0x38)
	{
	  add_1(x++);
	  osDelay(1);
	}
	else
	{
	  x = 0x30;
	  goto b;
	}
    }
}

void waiter_1 (void const *argument) //waiter_1
{
    unsigned char data_1 = 0;
    unsigned int i = 0;
    for(;;)
    {
	osDelay(6);
	for(; i<4; i++)
	{
	  data_1 = get_1();
	  SendChar(data_1);
	  add_2(y++);
	  osSemaphoreRelease(ren1);
	  osSemaphoreWait(ren2, osWaitForever);
	}
	i = 0;
	y = 0x41;
	osDelay(4);
    }
}

void waiter_2 (void const *argument) //waiter_2
{
    unsigned char data_2 = 0;
    unsigned int j = 0;
    for(;;)
    {
	osDelay(6);
	for(; j<4; j++)
	{
	  data_2 = get_1();
	  SendChar(data_2);
	  add_2(y++);
	  osSemaphoreRelease(ren2);
	  osSemaphoreWait(ren1, osWaitForever);
	}
	j = 0;
	y = 0x41;
	osDelay(4);
	}
}

void chashier (void const *argument) //cashier
{
    unsigned char bill = 0;
    unsigned int k = 0;
    for(;;)
    {
	osDelay(10);
	for(; k<4; k++)
	{
	  bill = get_2();
	  SendChar(bill);
	}
	k = 0;
	osDelay(1);
	}
}


int main(void)
{

    osKernelInitialize ();      //initialize CMSIS_RTOS

    USART1_Init ();
    x_mutex = osMutexCreate(osMutex(x_mutex));
    ren1 = osSemaphoreCreate(osSemaphore(ren1), 0);
    ren2 = osSemaphoreCreate(osSemaphore(sren2), 0);
    items_1 = osSemaphoreCreate(osSemaphore(items_1), 0);
    space_1 = osSemaphoreCreate(osSemaphore(space_1), N);
    items_2 = osSemaphoreCreate(osSemaphore(items_2), 0);
    space_2 = osSemaphoreCreate(osSemaphore(space_2), max_size);
    T_chef_1= osThreadCreate(osThread(chef_1), NULL);
    T_chef_2= osThreadCreate(osThread(chef_2), NULL);
    T_waiter_1= osThreadCreate(osThread(waiter_1), NULL);
    T_waiter_2= osThreadCreate(osThread(waiter_2), NULL);
    T_cashier = osThreadCreate(osThread(cashier), NULL);
    
    osKernerStart ();          //start Thread execution
}


