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


int registrarCliente(Cliente *cliente){
    sqlite3* db;
    sqlite3_open("base_datos.db", &db);

    sqlite3_stmt *stmt;

    const char *sql = "INSERT INTO CLIENTE VALUES (?,?,?,?,?,?);";
    int result = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (result != SQLITE_OK) {
		printf("Error en la preparación del statement (INSERT)\n");
		printf("%s\n", sqlite3_errmsg(db));
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
        fprintf(stderr, "Error al ejecutar el statement: %s\n", sqlite3_errmsg(db));
        return result;
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
    return 0;

}


int comprobarCliente(char *c){

    sqlite3* db;
    sqlite3_open("base_datos.db", &db);

    sqlite3_stmt *stmt;

    const char *sql = "SELECT DNI FROM CLIENTE WHERE DNI LIKE ?;";
    int result = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (result != SQLITE_OK) {
		printf("Error preparing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return 1;
	}

    
    char *DNI = c;
    sqlite3_bind_text(stmt, 1, DNI, -1, SQLITE_STATIC);
    
    result = sqlite3_step(stmt);

    const char *count1 = NULL;

    count1 = (char *)sqlite3_column_text(stmt, 0);
    if (strcmp(count1, c) != 0){
        printf("\nEste cliente no esta registrado");
        return 1;
    }
    else{
        printf("\nExiste cliente");
    }
    

    sqlite3_finalize(stmt);
    sqlite3_close(db);
    return 0;

}


void mostrarReservasCliente(char *dni_cliente) {
    sqlite3 *db;
    sqlite3_open("base_datos.db", &db);

    sqlite3_stmt *stmt;
    const char *sql = "SELECT * FROM RESERVA_HOTEL WHERE DNI LIKE ?;";
    int result = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (result != SQLITE_OK) {
        printf("Error preparando la sentencia (SELECT)\n");
        printf("%s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return;
    }

    sqlite3_bind_text(stmt, 1, dni_cliente, -1, SQLITE_STATIC);

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        int id_reserva = sqlite3_column_int(stmt, 0);
        const unsigned char *fecha_ini = sqlite3_column_text(stmt, 1);
        const unsigned char *fecha_fin = sqlite3_column_text(stmt, 2);
        const unsigned char *dni = sqlite3_column_text(stmt, 3);
        int num_personas = sqlite3_column_int(stmt, 4);
        int id_habitacion = sqlite3_column_int(stmt, 5);

        printf("\nReserva #%d:", id_reserva);
        printf("\nFecha de inicio: %s", fecha_ini);
        printf("\nFecha de fin: %s", fecha_fin);
        printf("\nDNI del cliente: %s", dni);
        printf("\nNúmero de personas: %d", num_personas);
        printf("\nID de la habitación: %d\n", id_habitacion);
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
}