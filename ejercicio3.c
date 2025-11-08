#include "util/network.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

#define RECV_BUFF_SZ 1024
#define CLIENT_TIMEOUT_SEC 3

void reverseStr(char * str)
{
    int i;
    char revStr[strlen(str)+1];

    for(i=strlen(str)-1;i>=0;i--)
    {
        if((str[i]!='\n')&&(str[i]!='\r'))
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
        clock_t timeFlag;
        char disconnectMsj[RECV_BUFF_SZ];
        int boolMsj = 1;
        while(1)
        {
            if(boolMsj){
                timeFlag = clock();
                boolMsj = 0;
            }

            if(((clock()-timeFlag)/CLOCKS_PER_SEC)>CLIENT_TIMEOUT_SEC){
                strcpy(disconnectMsj, "Conexion terminada por timeout\n");
                send(clientSk, disconnectMsj, strlen(disconnectMsj), 0);
                CloseServer(clientSk);
                break;
            }

            usedBuff = recv(clientSk, recvBuff, RECV_BUFF_SZ, MSG_DONTWAIT);

            if(usedBuff>0){
                recvBuff[usedBuff] = '\0';
                if(!(strcmp(recvBuff, "Chau\r\n"))){
                    strcpy(disconnectMsj, "Conexion terminada por str\n");
                    send(clientSk, disconnectMsj, strlen(disconnectMsj), 0);
                    CloseServer(clientSk);
                    break;
                }
                reverseStr(recvBuff);
                strcat(recvBuff, "\n");
                send(clientSk, recvBuff, strlen(recvBuff), 0);
                boolMsj = 1;
            }
        }
    }
    return 0;
}
