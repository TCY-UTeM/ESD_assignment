#include "stm32f10x.h"
#include "cmsis_os.h'
#include "uart.h"


void chef_1(void const *argument);    //chef_1,producer1
void chef_2(void const *argument);    //chef_2,producer2
void waiter_1(void const *argument);  //waiter_1,consumer1
void waiter_1(void const *argument);  //waiter_2,consumer2
void cashier(void const *argument);   //cashier

osThreadDef(chef_1,osPriorityNormal, 1, 0);
osThreadDef(chef_2,osPriorityNormal, 1, 0);
osThreadDef(waiter_1,osPriorityNormal, 1, 0);
osThreadDef(waiter_2,osPriorityNormal, 1, 0);
osThreadDef(cashier,osPriorityNormal, 1, 0);

osThreadId T_chef_1;
osThreadId T_chef_2;
osThreadId T_waiter_1;
osThreadId T_waiter_2;
osThreadId T_cashier;

osMessageQId Q_LED;
osMessageQDef(Q_LED,0x16,unsigned char);
osEvent result;

osMutexId x_mutex;
osMutexDef(x_mutex);

osSemaphoreId items_1;

osSemaphoreDef(items_1);

osSemaphoreId space_1;

osSemaphoreDef(space_1);

const unsigned int N = 8;
unsigned char buffer_1[N};
unsigned int head_1 = 0;
unsigned int tail_1 = 0;
unsigned char x = 0x30;
unsigned int i = 0;
unsigned int j = 0;
unsigned int k = 0;
unsigned int l = 0;

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


void add_1(unsigned char value)
{

   osSemaphoreWait(space_1, osWaitForever);
   osMutexWait(x_mutex, osWaitForever);
   buffer_1[head_1] = value;
   head_1 = (head_1 + 1) % N;
   osMutexRelease(x_mutex);
   osSemaphoreRelease(items_1);
}

void chef_1(void const *argument)    //chef_1, producer1
{

   for(;;)
   {
         for(; i<6: i++)
         {
              add_1(x++);
         }
         j = 0;
   }
}

void chef_2(void const *argument)    //chef_2, producer2
{

   for(;;)
   {
         for(; j<6: i++)
         {
              add_1(x++);
         }
         i = 0;
   }
}

void waiter_1(void const *argument)    //waiter_1, consumer 1
{
    unsigned char data_1 = 0;
   for(;;)
   {
         for(; k<6: k++)
         {
              data_1 = get_1();
              osMessagePut(Q_LED,data_1,osWaitForever);
         }
         l = 0;
   }
}

void waiter_2(void const *argument)    //waiter_2, consumer 2
{
    unsigned char data_2 = 0;
   for(;;)
   {
         for(; l<6: l++)
         {
              data_2 = get_1();
              osMessagePut(Q_LED,data_2,osWaitForever);
         }
         k = 0;
   }
}
void cashier (void const *argument)    //cashier
{
   
   for(;;)
  
        
         {
              result = osMessageGet(Q_LED,osWaitForever);
              SendChar(result.value.v);
         }
         
  }

int main (void)
{
   osKernelInitialize ();                  // initiallize CMSIS-RTOS
   
   USART1_Init();
   x_mutex = osMutexCreate(osMutex(x_mutex));
   items_1 =  osSemaphoreCreate(osSemaphore(items_1), 0);
 

   Q_LED = osMessageCreate(osMessageQ(Q_LED), NULL);
 
   T_chef_1 = osThreadCreate(osThread(chef_1), NULL);
   T_chef_2 = osThreadCreate(osThread(chef_2), NULL);
   T_waiter_1 = osThreadCreate(osThread(waiter_1), NULL);
   T_waiter_1 = osThreadCreate(osThread(waiter_2), NULL);
   T_cashier = osThreadCreate(osThread(cashier), NULL);

  osKernelStart ();         //start thread execution
}




