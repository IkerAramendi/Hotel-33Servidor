#include"cabecera.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>



void logInicioSesion(char *message){
    FILE *f = fopen("log.txt", "a");

    if(f != NULL){
        time_t rawtime;
        struct tm *timeinfo;
        time(&rawtime);
        timeinfo = localtime(&rawtime);

         fprintf(f, "[%04d-%02d-%02d %02d:%02d:%02d] %s\n",
                timeinfo->tm_year + 1900, timeinfo->tm_mon + 1, timeinfo->tm_mday,
                timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec,
                message);

    }else{
        printf("Error al abrir el archivo log.");
    }

    fclose(f);

}