#include "../util/network.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

const char *meses[] = {"Enero", "Febrero", "Marzo", "Abril", "Mayo", "Junio", "Julio", "Agosto", "Septiembre", "Octubre", "Noviembre", "Diciembre"};
const char *semana[] = {"Lunes", "Martes", "Miercoles", "Jueves", "Viernes", "Sabado", "Domingo"};

void getTime(char* fechaStr, char* horaStr)
{
    time_t tiempo;
    struct tm timeTm
    tiempo = time(NULL);

    timeTm = localtime(&tiempo);

    sprintf(fechaStr, "%s %d de %s del %d\n", semana[timeTm.tm_wday], tm_mday, meses[l_tm_mon], tm_año);
    sprintf(horaStr, "%d:%d:%d", tm_hora, min_tmm, tm_seg);
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
        int mainSk = OpenServer(puerto);
        if(mainSk < 0)
        {
            printf("Error iniciando servidor\n");
            return -1;
        }

        char fechaStr[64] = {0};
        char horaStr[16] = {0};

        getTime(fechaStr, horaStr);

        send(mainSk, fechaStr, strlen(fechaStr), 0);
        send(mainSk, " ", 1, 0);
        send(mainSk, horaStr, strlen(horaStr), 0);
        send(mainSk, "\n", 1, 0);

        CloseServer(mainSk);
    }
}
