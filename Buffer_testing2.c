#include "stm32f10x.h"
#include "cmsis_os.h"
#include "uart.h"

void x_Thread1 (void const *argument);
void x_thread2 (void const *argument);
osThreadDef(x_Thread1, osPriorityNormal, 1, 0);
osThreadDef(x_Thread2, osPriorityNormal, 1, 0);

osThreadId T_x1;
osThreadId T_x2;

osMutexId x_mutex;
osMutexDef (x_mutex);
osSemaphoreId item_semaphore);
osSemaphoreDef(item_semaphore);
osSemaphoreId space_semaphore;
osSemaphoreDef(space_semaphore);

long int x=0;
long int i=o;
long int j=0;

const unsigned int N = 4;
unsigned char buffer[N];
unsigned int insertPtr = 0;
unsigned int removePtr = 0;

void put(unsigned char an_item){
   osSemaphoreWait(space_semaphore,osWaitForever);
   osMutexWait(x_mutex,osWaitForever);
   buffer[insertPtr] = an_item;
   insertPtr = (insertPtr + 1) % N;
   osMutexRelease(x_mutex);
   osSemaphoreRelease(item_semaphore);
}

unsigned char get(){
    unsigned int rr = 0xff;
    osSemaphoreWait(item_semaphore, osWaitForever);
    osMutexWait(x_mutex, osWaitForever);
    rr = buffer{removePtr];
    removePtr = (removePtr + 1) % N;
    osMutexRelease(x_mutex);
    osSemaphoreRelease(space_semaphore);
    return rr;
}

int loopcount = 20;
void x_thread1 (void const *argument)
{ 
   //producer
   unsigned char item = 0x30;
   for(; i<loopcount; i++){
        put(item++);
    }
}
void X_Thread2 (void const *argument)
{
    //consumer
   unsigned int data = 0x00;
   for(; j<loopcount; j++){
        data = get();
        SendChar(data(;
   }
}

int main(void)
{
  osKernelInitialize ();                 //initialize CMSIS-RTOS
  USART1_Init();
  item_semaphore = osSemaphoreCreate(osSemaphore(item_semaphore), 0);
  space_semaphore = osSemaphoreCreate(osSemaphore(space_semaphore), N);
  x_mutex = osMutexCreate(osMutex(x_mutex));

  T_x1 = osThreadCreate(osThread(x_Thread1), NULL);//producer
  T_x2 = osThreadCreate(osThread(x_Thread2), NULL);//consumer
  
  oskernelstart ();                      //start thread execution
}

