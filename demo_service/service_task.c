#include "service_task.h"
#include <unistd.h>
#include <malloc.h>
#include <string.h>
#include "tcp_server.h"

static void EventListener(TcpClient* client, int evt)
{
    if( evt == EVT_CONN )
    {
        printf("%s : CONN - %p...\n", __FUNCTION__, client);
    }
    else if( evt == EVT_DATA )
    {
        Message* msg = NULL;

        printf("%s : DATA - %p...\n", __FUNCTION__, client);

        msg = TcpClient_RecvMsg(client);

        if( msg )
        {
            printf("%s : msg = %p\n", __FUNCTION__, msg);
            printf("%s : msg->type = %d\n", __FUNCTION__, msg->type);
            printf("%s : msg->cmd = %d\n", __FUNCTION__, msg->cmd);
        }

        free(msg);
    }
    else if( evt == EVT_CLOSE )
    {
        printf("%s : CLOSE - %p...\n", __FUNCTION__, client);
    }
}

void* Service_Task(const char* arg)
{
    TcpServer* server= TcpServer_New();

    printf("%s : enter server task...\n", __FUNCTION__);

    if( server )
    {
        printf("%s : server = %p\n", __FUNCTION__, server);

        TcpServer_SetListener(server, EventListener);
        TcpServer_Start(server, 8888, 10);
        TcpServer_DoWork(server);
    }
    return arg;
}