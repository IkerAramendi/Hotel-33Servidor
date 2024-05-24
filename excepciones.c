#include"cabecera.h"
#include<stdio.h>
#include<ctype.h>
#include <string.h>
#include <time.h>
#include <cstdlib>

using namespace containers;

void excepcionNumeros(char *ve, Server *s){
    while(isdigit(*ve) == 0){
        s->Enviar("\nError! Introduce un numero:");
        *ve = (s->Recibir())[0];
    }
}


void excepcionDNI(char *str, Server *s) {
    int valido = 0;
    while (valido != 1) {
        if(strlen(str) == 9) {
            int numerosCorrectos = 0;
            int i;
            for (i = 0; i < strlen(str) - 1; i++) {
                if(isdigit(str[i])){
                    numerosCorrectos++;
                }
            }

            if(isalpha(str[8]) && numerosCorrectos == 8) {
                str[8] = toupper(str[8]);
                valido = 1;

            } else{
                s->Enviar("Formato incorrecto. Introduzcalo de nuevo:  ");
                char *buffer = s->Recibir();
                strncpy(str, buffer, 10);     
                       
                
                }
            
        } else {
            s->Enviar("Formato incorrecto.El DNI tiene 9 caracteres alfanumericos. Introduzcalo de nuevo:  ");
            char *buffer = s->Recibir();
            strncpy(str, buffer, 10);
        }
    }
}


void excepcionNombre(char *str, Server *s){
    int valido = 0;
    while(valido != 1){
        str[0] = toupper(str[0]);
        int existeNumero = 0;
        int i;

        for(i = 1; i < strlen(str); i++){
            str[i] = tolower(str[i]);

            if(isdigit(str[i])){
                existeNumero = 1;
                }
            }
        

        if(existeNumero == 0){
            if(strlen(str) < 2 || strlen(str) > 15){
                s->Enviar("El nombre debe contener entre 2 y 15 caracteres. Intentelo de nuevo:");
                strncpy(str, s->Recibir(), 10); 
            }

            else{
                valido = 1;
            }
        }

        else{
            s->Enviar("El nombre  no debe contener numeros. Intentelo de nuevo:");
            strncpy(str, s->Recibir(), 10);
        }
    } 
}






void excepcionApellido(char *str, Server *s){
    int valido = 0;
    while(valido != 1){
        str[0] = toupper(str[0]);
        int existeNumero = 0;
        int i;

        for(i = 1; i < strlen(str); i++){
            str[i] = tolower(str[i]);

            if(isdigit(str[i])){
                existeNumero = 1;
                }
            }
        

        if(existeNumero == 0){
            if(strlen(str) < 2 || strlen(str) > 15){
                s->Enviar("El apellido debe contener entre 2 y 15 caracteres. Intentelo de nuevo:");
                strncpy(str, s->Recibir(), 16);  
            }

            else{
                valido = 1;
            }
        }

        else{
            s->Enviar("El apellido  no debe contener numeros. Intentelo de nuevo:");
            strncpy(str, s->Recibir(), 16);
        }
    } 
}



void excepcionContrasena(char *str, Server *s){
    int valido = 0;
    while (valido != 1){
          if(strlen(str) >= 4 && strlen(str) <= 15){
            valido = 1;
            }
            else{
                s->Enviar("La contrasena debe contener entre 4 y 15 caracteres. Intentelo de nuevo:  ");
                strncpy(str, s->Recibir(), 16);  
            }

}
}


void excepcionAnyoReserva(int *anyo, Server *s){
    time_t tiempo_actual;
    struct tm* tiempo_info;
    time(&tiempo_actual);
    tiempo_info = localtime(&tiempo_actual);

    int anyo_actual = tiempo_info->tm_year + 1900;

    while (*anyo < anyo_actual || *anyo >= anyo_actual+50){
        s->Enviar("El ano introducido debe ser mayor que 2023. Intentelo de nuevo:  ");
        char subbuffer[5];
        subbuffer[4] = '\0';
        strncpy(subbuffer, s->Recibir(), 4);
        *anyo = atoi(subbuffer);
    }

}



void excepcionMesReserva(int *mes, Server *s){
    while(*mes < 1 || *mes > 12){
         s->Enviar("El mes introducido es incorrecto. Intentelo de nuevo:  ");
         char subbuffer[3];
         subbuffer[2] = '\0';
         strncpy(subbuffer, s->Recibir(), 2);
         *mes = atoi(subbuffer);
    }
}


void excepcionDiaReserva(int *mes , int *dia, Server *s){
    int valido = 0;
    while(valido != 1){
        if(*mes % 2 == 0 && *mes != 2 && *dia <= 31 && *dia >= 1){
            valido = 1;
        }
        else if(*mes % 2 != 0 && *dia <= 30 && *dia >= 1){
            valido = 1;
        }
        else if(*mes == 2 && *dia <= 28 && *dia >= 1 ){
            valido = 1;
        }
        else{
            s->Enviar("El dia introducido es incorrecto. Intentelo de nuevo:  ");
            char subbuffer[3];
            subbuffer[2] = '\0';
            strncpy(subbuffer, s->Recibir(), 2);
            *dia = atoi(subbuffer);

        }

    }
}



void excepcionNumeroPersonas(int *num, Server *s){
    while(*num >= 5 || *num <= 0){
        printf("El numero de personas tiene que estar entre 1 y 4. Intentelo de nuevo:");
        scanf("%i", num);
        fflush(stdin);
    }

}


void excepcionNumeroTelefono(char *str, Server *s){
    int numerosCorrectos = 0;
    int valido = 0;
    while(valido != 1){
        int numerosCorrectos = 0;
        
        for(int i = 0; i < strlen(str); i++){
            if(isdigit(str[i])){
                numerosCorrectos++;
            }
        }
        if(numerosCorrectos == 9){
            valido = 1;
        }
        else{
            s->Enviar("El numero de telefono debe tener 9 digitos. Intentelo de nuevo:");
            scanf("%s", str);
            fflush(stdin);
        }
    }

}



void excepcionNumeroTarjeta(char *str, Server *s){
    int numerosCorrectos = 0;
    int valido = 0;
    while(valido != 1){
        int numerosCorrectos = 0;
        
        for(int i = 0; i < strlen(str); i++){
            if(isdigit(str[i])){
                numerosCorrectos++;
            }
        }
        if(numerosCorrectos == 16){
            valido = 1;
        }
        else{
            printf("El numero de tarjeta debe tener 16 digitos. Intentelo de nuevo:");
            scanf("%s", str);
            fflush(stdin);
        }
    }

}


void excepcionAnyoNacimiento(int *anyo, Server *s){
    time_t tiempo_actual;
    struct tm* tiempo_info;
    time(&tiempo_actual);
    tiempo_info = localtime(&tiempo_actual);

    int anyo_actual = tiempo_info->tm_year + 1900;

    while (*anyo < anyo_actual - 120  || *anyo > anyo_actual - 18){
        printf("El ano introducido es incorrecto. Intentelo de nuevo: ");
        scanf("%d", anyo);
        fflush(stdin);
    }

}