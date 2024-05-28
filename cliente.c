#include"cabecera.h"
#include"sqlite3.h"
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "cabecera.h"
#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
#include <ctime>
#include "cabecera.h"

using namespace containers;

int registrarCliente(Cliente *cliente, Server *s){
    sqlite3* db;
    sqlite3_open("base_datos.db", &db);

    sqlite3_stmt *stmt;

    const char *sql = "INSERT INTO CLIENTE VALUES (?,?,?,?,?,?);";
    int result = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (result != SQLITE_OK) {
        s->Enviar("\nERROR:511\n");
        s->Recibir();
        
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        
        return 1;
	}

    char *nombre = (*cliente).nombre;
    char *apellido = (*cliente).apellido;
    char *DNI = (*cliente).DNI;
    char *telefono = (*cliente).telefono;
    char *num_tarjeta = (*cliente).num_tarjeta;
    int anyo = (*cliente).fecha_nac.anyo;
    int mes = (*cliente).fecha_nac.mes;
    int dia = (*cliente).fecha_nac.dia;
    char *fechaFormateada = (char*) malloc(11);

    sprintf(fechaFormateada, "%d-%02d-%02d", anyo, mes, dia);
    
    sqlite3_bind_text(stmt, 1, DNI, strlen(DNI), SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, nombre, strlen(nombre), SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, apellido, strlen(apellido), SQLITE_STATIC);
    sqlite3_bind_text(stmt, 4, telefono, strlen(telefono), SQLITE_STATIC);
    sqlite3_bind_text(stmt, 5, num_tarjeta, strlen(num_tarjeta), SQLITE_STATIC);
    sqlite3_bind_text(stmt, 6, fechaFormateada, -1, SQLITE_STATIC);

    result = sqlite3_step(stmt);
    if (result != SQLITE_DONE) {
        if (strstr(sqlite3_errmsg(db), "UNIQUE constraint failed: CLIENTE.DNI") != NULL) {
                s->Enviar("\nERROR:510\n");
                s->Recibir();
            }else{
                s->Enviar("\nERROR:511\n");
                s->Recibir();
            }
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        
        return 1;
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
    return 0;

}


int comprobarCliente(char *c, Server *s){

    sqlite3* db;
    sqlite3_open("base_datos.db", &db);

    sqlite3_stmt *stmt;

    const char *sql = "SELECT DNI FROM CLIENTE WHERE DNI LIKE ?;";
    int result = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (result != SQLITE_OK) {
    		s->Enviar("\nERROR:511\n");
        s->Recibir();
        sqlite3_finalize(stmt);
        sqlite3_close(db);
		    return 1;
	}

    
    char *DNI = c;
    sqlite3_bind_text(stmt, 1, DNI, -1, SQLITE_STATIC);
    
    result = sqlite3_step(stmt);

    const char *count1 = NULL;

    count1 = (char *)sqlite3_column_text(stmt, 0);
    if (strcmp(count1, c) != 0){
        s->Enviar("\nEste cliente no esta registrado");
        s->Recibir();
        
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return 1;
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
    return 0;

}


void mostrarReservasCliente(char *dni_cliente, Server *s) {
    sqlite3 *db;
    sqlite3_open("base_datos.db", &db);

    sqlite3_stmt *stmt;
    const char *sql = "SELECT * FROM RESERVA_HOTEL WHERE DNI LIKE ?;";
    int result = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (result != SQLITE_OK) {
        s->Enviar("\nERROR:512\n");
        s->Recibir();
        
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return;
    }

    sqlite3_bind_text(stmt, 1, dni_cliente, -1, SQLITE_STATIC);
    
    int found = 0;

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        found = 1;

        char* mensaje = (char*)malloc(500*sizeof(char));
        strcpy(mensaje, "\nReserva #");
        sprintf(mensaje,"%s%d",mensaje, sqlite3_column_int(stmt, 0));
        strcat(mensaje, "\nFecha de inicio: ");
        strcat(mensaje, (const char *)sqlite3_column_text(stmt, 1));
        strcat(mensaje, "\nFecha de fin: ");
        strcat(mensaje, (const char *)sqlite3_column_text(stmt, 2));
        strcat(mensaje, "\nDNI del cliente: ");
        strcat(mensaje, (const char *)sqlite3_column_text(stmt, 3));
        strcat(mensaje, "\nNumero de personas: ");
        sprintf(mensaje, "%s%d", mensaje, sqlite3_column_int(stmt, 4));
        strcat(mensaje, "\nID de la habitacion: ");
        sprintf(mensaje, "%s%d", mensaje, sqlite3_column_int(stmt, 5));
        strcat(mensaje, "\n");
        s->Enviar(mensaje);
        s->Recibir();
    }

    if(!found){
        s->Enviar("\nERROR:505!! DNI del cliente no encontrado.\n");
        s->Recibir();
    }else{
        s->Enviar("\nCODIGO:205\n");
        s->Recibir();
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
}