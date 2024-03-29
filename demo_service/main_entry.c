#include <stdio.h>
#include <unistd.h>
#include "ohos_init.h"
#include "cmsis_os2.h"
#include "wifi_connect.h"
#include "response_task.h"
#include "service_task.h"

static void* Init_Task(const char* arg)
{
    Wifi_Init();
    Wifi_Connect("ZhangXing", "4413294x");
    Wifi_Start();

    if( Wifi_IsOk() )
    {
        osThreadAttr_t attr = {0};

        printf("IP: %s\n", Wifi_IpAddr());

        attr.name = "Response Task";
        attr.stack_size = 1024 * 4;
        attr.priority = 20;

        if(osThreadNew((osThreadFunc_t)Response_Task, NULL, &attr) == NULL)
        {
            printf("Failed to create Response Task!\n");
        }

        attr.name = "Service Task";
        attr.stack_size = 1024 * 4;
        attr.priority = 20;

        if(osThreadNew((osThreadFunc_t)Service_Task, NULL, &attr) == NULL)
        {
            printf("Failed to create Service Task!\n");
        }
    }

    return arg;
}

static void Main_Entry(void)
{
    osThreadAttr_t attr = {0};

    attr.name = "Init Task";
    attr.stack_size = 1024 * 4;
    attr.priority = 20;

    if(osThreadNew((osThreadFunc_t)Init_Task, NULL, &attr) == NULL)
    {
        printf("Failed to create task!\n");
    }
}

SYS_RUN(Main_Entry);

