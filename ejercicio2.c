#include "util/network.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define RECV_BUFF_SZ 1024

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

    while(1)
    {
        char recvBuff[RECV_BUFF_SZ];
        int usedBuff; 

        int mainSk = OpenServer(puerto);
        if(mainSk < 0)
        {
            printf("Error iniciando servidor\n");
            return -1;
        }

        usedBuff = recv(mainSk, recvBuff, RECV_BUFF_SZ, 0);
        
        recvBuff[usedBuff] = '\0';
        reverseStr(recvBuff);
        strcat(recvBuff, "\n");

        send(mainSk, recvBuff, strlen(recvBuff), 0);

        CloseServer(mainSk);
    }

    return 0;
}
