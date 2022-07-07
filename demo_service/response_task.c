#include "response_task.h"
#include "udp_point.h"


void* Response_Task(const char* arg)
{
    UdpPoint* udp = UdpPoint_New(9999);

    printf("%s : enter response task...\n", __FUNCTION__);

    if( udp )
    {
        char remote[16] = {0};
        int port = 0;

        printf("%s : udp = %p\n", __FUNCTION__, udp);

        while(1)
        {
            Message* msg = UdpPoint_RecvMsg(udp, remote, &port);

            if( msg )
            {
                printf("%s : msg = %p\n", __FUNCTION__, msg);
                printf("%s : remote = %s\n", __FUNCTION__, remote);
                printf("%s : port = %d\n", __FUNCTION__, port);
                printf("%s : msg->type = %d\n", __FUNCTION__, msg->type);
                printf("%s : msg->cmd = %d\n", __FUNCTION__, msg->cmd);
            }
            else
            {
                printf("Error: msg is NULL...\n");
            }

            free(msg);
        }
    }

    return arg;
}
