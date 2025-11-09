#include "util/network.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>

#define RECV_BUFF_SZ 1024
#define CLIENT_TIMEOUT_SEC 10

const char *meses[] = {"Enero", "Febrero", "Marzo", "Abril", "Mayo", "Junio", "Julio", "Agosto", "Septiembre", "Octubre", "Noviembre", "Diciembre"};
const char *semana[] = {"Lunes", "Martes", "Miercoles", "Jueves", "Viernes", "Sabado", "Domingo"};

void getTime(char* fechaStr, char* horaStr)
{
    time_t tiempo;
    struct tm* timeTm;
    tiempo = time(NULL);

    timeTm = localtime(&tiempo);

    sprintf(horaStr, "%d:%d:%d\n", timeTm->tm_hour, timeTm->tm_min, timeTm->tm_sec);
    sprintf(fechaStr, "%s %d de %s del %d\n", semana[timeTm->tm_wday], timeTm->tm_mday, meses[timeTm->tm_mon], timeTm->tm_year + 1900);
}

void reverseStr(char* str)
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

void* funcMain(void* clientSk)
{
    int sk = *(int*)clientSk; //posible problema??
    char recvBuff[RECV_BUFF_SZ];
    int usedBuff; 
    clock_t timeFlag;
    char auxMsj[RECV_BUFF_SZ];
    int boolMsj = 1;
    char fechaStr[64];
    char horaStr[16];
    fprintf(stdout,"pid: %d    thread-id: %ld    client-socket: %d\n", getpid(), pthread_self(), sk);
    strcpy(auxMsj, "Escriba /help para ver los comandos disponibles\n");
    send(sk, auxMsj, strlen(auxMsj), 0);
    while(1)
    {
        if(boolMsj){
            timeFlag = clock();
            boolMsj = 0;
        }

        if(((clock()-timeFlag)/CLOCKS_PER_SEC)>CLIENT_TIMEOUT_SEC){
            strcpy(auxMsj, "Conexion terminada por timeout\n");
            send(sk, auxMsj, strlen(auxMsj), 0);
            CloseServer(sk);
            break;
        }

        usedBuff = recv(sk, recvBuff, RECV_BUFF_SZ, MSG_DONTWAIT);

        if(usedBuff>0){
            boolMsj = 1;
            recvBuff[usedBuff] = '\0';
            if(!(strcmp(recvBuff, "Chau\r\n"))){
                strcpy(auxMsj, "Conexion terminada por str\n");
                send(sk, auxMsj, strlen(auxMsj), 0);
                CloseServer(sk);
                break;
            }
            if(!(strcmp(recvBuff, "/help\r\n"))){
                strcpy(auxMsj, "/time -> obtener la hora\n/date -> obtener la fecha\n");
                send(sk, auxMsj, strlen(auxMsj), 0);
                continue;
            }
            if(!(strcmp(recvBuff, "/time\r\n"))){
                getTime(fechaStr, horaStr);
                send(sk, horaStr, strlen(horaStr), 0);
                continue;
            }
            if(!(strcmp(recvBuff, "/date\r\n"))){
                getTime(fechaStr, horaStr);
                send(sk, fechaStr, strlen(fechaStr), 0);
                continue;
            }
            else{
            reverseStr(recvBuff);
            strcat(recvBuff, "\n");
            send(sk, recvBuff, strlen(recvBuff), 0);
            }
        }
    }
    pthread_exit(0);
    return NULL;
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

    pthread_t threadId; //puedo usar una sola varible??
    while(1){
        int clientSk = AcceptClient(mainSk);
        int ret;
        ret = pthread_create(&threadId, NULL, funcMain, (void*)&clientSk); //es seguro usar clientSk para todos los hilos sin un mutex??
        if(ret){
            fprintf(stderr,"Error al crear el thread. Error numero: %d\n", ret);
            exit(1);
        }
    }
    return 0;
}