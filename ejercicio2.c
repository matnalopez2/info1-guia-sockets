#include "util/network.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

#define RECV_BUFF_SZ 1024
#define CLIENT_TIMEOUT_SEC 300

void reverseStr(char * str)
{
    int i;
    char revStr[strlen(str)+1];

    for(i=strlen(str)-1;i>=0;i--)
    {
        if(str[i]!='\n')
            revStr[strlen(str)-i-1]=str[i];
    }
    revStr[strlen(str)]='\0';
    strcpy(str, revStr);
}

int main(int argc, char **argv)
{
    if(argc < 2)
    {
        printf("Missing arguments\n");
        return -1;
    }

    int puerto = atoi(argv[1]);

    int mainSk = CreateServerSocket(puerto);
    if(mainSk < 0)
    {
        printf("Error iniciando servidor\n");
        return -1;
    }

    while(1){
        int clientSk = AcceptClient(mainSk);
        char recvBuff[RECV_BUFF_SZ];
        int usedBuff; 
        clock_t timeFlag = clock();
        char disconnectMsj[] = "Conexion terminada por timeout\n";
        while(1)
        {
            if(((clock()-timeFlag)/CLOCKS_PER_SEC)>CLIENT_TIMEOUT_SEC){
                send(clientSk, disconnectMsj, strlen(disconnectMsj), 0);
                CloseServer(clientSk);
                break;
            }

            usedBuff = recv(clientSk, recvBuff, RECV_BUFF_SZ, MSG_DONTWAIT);

            if(usedBuff>0){
                recvBuff[usedBuff] = '\0';
                reverseStr(recvBuff);
                strcat(recvBuff, "\n");
                send(clientSk, recvBuff, strlen(recvBuff), 0);
                CloseServer(clientSk);
                break;
            }
        }
    }
    return 0;
}
