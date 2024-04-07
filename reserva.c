#include<stdio.h>
#include<string.h>
#include"sqlite3.h"
#include"cabecera.h"
#include<stdlib.h>

//FUNCION PARA CALCULAR LA OCUPACION DE LAS HABITACIONES
int calcularOcupacion(Fecha fecha_ped_ini, Fecha fecha_ped_fin){



    sqlite3* db;
    sqlite3_open("base_datos.db", &db);

    sqlite3_stmt *stmt;
    //char *sql0 = "SELECT COUNT(*) FROM RESERVA_HOTEL;";
    //char *sql0 = "SELECT COUNT(*) FROM RESERVA_HOTEL WHERE FECHA_PED_FIN(?) < FECHA_INI OR FECHA_PED_INI(?) > FECHA_FIN;";

    char *sql0 = "SELECT COUNT(*) FROM RESERVA_HOTEL WHERE (? < FECHA_INI) OR (? > FECHA_FIN);";
    
    int result = sqlite3_prepare_v2(db, sql0, -1, &stmt, NULL);
    if (result != SQLITE_OK) {
		printf("Error preparing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}

    char *fechaFormateadaInicio = malloc(11);
    sprintf(fechaFormateadaInicio, "%d-%02d-%02d", fecha_ped_ini.anyo, fecha_ped_ini.mes, fecha_ped_ini.dia);

    char *fechaFormateadaFin = malloc(11);
    sprintf(fechaFormateadaFin, "%d-%02d-%02d", fecha_ped_fin.anyo, fecha_ped_fin.mes, fecha_ped_fin.dia);

    sqlite3_bind_text(stmt, 1, fechaFormateadaFin, -1,  SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, fechaFormateadaInicio, -1, SQLITE_STATIC);




    result = sqlite3_step(stmt);
    int count = sqlite3_column_int(stmt, 0);

    printf("\nEl resultado es: %i\n", count);
    sqlite3_finalize(stmt);
    sqlite3_close(db);
    printf("llegaop");

    return count;

    //FECHA_FIN
    //FECHA_INI
    //FECHA_PED_INI
    //FECHA_PED_FIN

    //FECHA_PED_FIN < FECHA_INI
    //FECHA_PED_INI > FECHA_FIN

}

int realizarReserva(Reserva *r){
    

    int resultado = calcularOcupacion((*r).fecha_ini, (*r).fecha_fin);
    if (resultado == 15){
        return 3;
    }

    sqlite3* db;
    sqlite3_open("base_datos.db", &db);

    sqlite3_stmt *stmt1;
    printf("llega");

    char *sql = "INSERT INTO RESERVA_HOTEL VALUES (?,?,?,?,?);";
    int result = sqlite3_prepare_v2(db, sql, -1, &stmt1, NULL);
    if (result != SQLITE_OK) {
		printf("Error preparing statement (INSERT)\n");
		printf("%s\n", sqlite3_errmsg(db));
	    return 0;
	}


    int ID_RESERVA_HOTEL = 3;
    
    int ID_HABITACION = 3;
    printf("llega");

    sqlite3_bind_int(stmt1, 1, ID_RESERVA_HOTEL);
    sqlite3_bind_text(stmt1, 2, DNI, strlen(DNI), SQLITE_STATIC);
    sqlite3_bind_int(stmt1, 3, ID_HABITACION);
    printf("llega");
    result = sqlite3_step(stmt1);
    if (result != SQLITE_DONE) {
        fprintf(stderr, "Error al ejecutar el statement: %s\n", sqlite3_errmsg(db));
        return 1;
    }
    sqlite3_finalize(stmt1);
    sqlite3_close(db);
    return 2;
}

void anularReserva(){

}

