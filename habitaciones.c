#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"sqlite3.h"
#include"cabecera.h"

using namespace containers;

int crearTipoHabitaciones(Server *s){
    sqlite3* db;
    sqlite3_open("base_datos.db", &db);
    sqlite3_stmt *stmt;

    const char *sql = "INSERT INTO TIPO_HABITACION VALUES (?,?);";
    int result = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (result != SQLITE_OK) {
        s->Enviar("\nERROR:515\n");
        s->Recibir();
        
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return 1;   
	}

    char tipoHabitacionA[2] = "A";
    int precioA = 50;

    sqlite3_bind_text(stmt, 1, tipoHabitacionA, 1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 2, precioA);

    result = sqlite3_step(stmt);

    if (result != SQLITE_DONE) {
        s->Enviar("\nERROR:515\n");
        s->Recibir();
        
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return 1;
    }
    sqlite3_finalize(stmt);



    sqlite3_stmt *stmt1;

    const char *sql1 = "INSERT INTO TIPO_HABITACION VALUES (?,?);";
    int result1 = sqlite3_prepare_v2(db, sql1, -1, &stmt1, NULL);
    if (result1 != SQLITE_OK) {
		    s->Enviar("\nERROR:515\n");
        s->Recibir();
            
        sqlite3_finalize(stmt1);
        sqlite3_close(db);
        return 1;
	}



    Tipo_habitacion tipoB;
    char tipoHabitacionB[2] = "B";
    int precioB = 80;

    sqlite3_bind_text(stmt1, 1, tipoHabitacionB, 1, SQLITE_STATIC);
    sqlite3_bind_int(stmt1, 2, precioB);

    result1 = sqlite3_step(stmt1);

    if (result1 != SQLITE_DONE) {
        s->Enviar("\nERROR:515\n");
        s->Recibir();
        
        sqlite3_finalize(stmt1);
        sqlite3_close(db);
        return 1;
    }
    sqlite3_finalize(stmt1);



    sqlite3_stmt *stmt2;

    const char *sql2 = "INSERT INTO TIPO_HABITACION VALUES (?,?);";
    int result2 = sqlite3_prepare_v2(db, sql2, -1, &stmt2, NULL);
    if (result2 != SQLITE_OK) {
		    s->Enviar("\nERROR:515\n");
        s->Recibir();
        
        sqlite3_finalize(stmt2);
        sqlite3_close(db);
	}

    Tipo_habitacion tipoC;
    char tipoHabitacionC[2] = "C";
    int precioC = 120;

    sqlite3_bind_text(stmt2, 1, tipoHabitacionC, 1, SQLITE_STATIC);
    sqlite3_bind_int(stmt2, 2, precioC);

    result2 = sqlite3_step(stmt2);

    if (result2 != SQLITE_DONE) {
        s->Enviar("\nERROR:515\n");
        s->Recibir();
        
        sqlite3_finalize(stmt2);
        sqlite3_close(db);
        return 1;
    }


    sqlite3_stmt *stmt3;

    const char *sql3 = "INSERT INTO TIPO_HABITACION VALUES (?,?);";
    int result3 = sqlite3_prepare_v2(db, sql3, -1, &stmt3, NULL);
    if (result3 != SQLITE_OK) {
        s->Enviar("\nERROR:515\n");
        s->Recibir();
       
        sqlite3_finalize(stmt);
        sqlite3_close(db);
	}
    Tipo_habitacion tipoD;
    char tipoHabitacionD[2] = "D";
    int precioD = 120;

    sqlite3_bind_text(stmt3, 1, tipoHabitacionD, 1, SQLITE_STATIC);
    sqlite3_bind_int(stmt3, 2, precioD);

    result3 = sqlite3_step(stmt3);

    if (result3 != SQLITE_DONE) {
        s->Enviar("\nERROR:515\n");
        s->Recibir();
        
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return 1;
    }
    sqlite3_finalize(stmt3);
    sqlite3_close(db);
    
    return 0;
}


void crearHabitaciones(Server *s){

    sqlite3* db;
    int status = sqlite3_open("base_datos.db", &db);
    sqlite3_stmt *stmt;

    char *error_message = 0;


   //INSERTS DE HABITACION TIPO A
    for ( int i = 1; i< 6 ; i++){
        char insert_sql[100];
        sprintf(insert_sql, "INSERT INTO HABITACION VALUES (%d,'%s','%s',%d);", i,"A","Habitacion",2);
        status = sqlite3_exec(db, insert_sql, 0, 0, &error_message);
        if (status != SQLITE_OK) {
            s->Enviar("\nERROR:516\n");
            s->Recibir();
            
            sqlite3_finalize(stmt);
            sqlite3_close(db);
        }
    }

    for ( int i = 6; i< 11 ; i++){
        char insert_sql[100];
        sprintf(insert_sql, "INSERT INTO HABITACION VALUES (%d,'%s','%s',%d);", i,"B","Habitacion",3);
        status = sqlite3_exec(db, insert_sql, 0, 0, &error_message);
        if (status != SQLITE_OK) {
            s->Enviar("\nERROR:516\n");
            s->Recibir();
            
            sqlite3_finalize(stmt);
            sqlite3_close(db);
        }
    }

    for ( int i = 11; i< 14 ; i++){
        char insert_sql[100];
        sprintf(insert_sql, "INSERT INTO HABITACION VALUES (%d,'%s','%s',%d);", i,"C","Habitacion",4);
        status = sqlite3_exec(db, insert_sql, 0, 0, &error_message);
        if (status != SQLITE_OK) {
            s->Enviar("\nERROR:516\n");
            s->Recibir();
            
            sqlite3_finalize(stmt);
            sqlite3_close(db);
        }


    }

    for ( int i = 14; i< 16 ; i++){
        char insert_sql[100];
        sprintf(insert_sql, "INSERT INTO HABITACION VALUES (%d,'%s','%s',%d);", i,"D","Habitacion",4);
        status = sqlite3_exec(db, insert_sql, 0, 0, &error_message);
        if (status != SQLITE_OK) {
            s->Enviar("\nERROR:516\n");
            s->Recibir();
            
            sqlite3_finalize(stmt);
            sqlite3_close(db);
        }


    }
    sqlite3_finalize(stmt);
    sqlite3_close(db);



}
int* disponibilidadHabitaciones(Fecha fechaini, Fecha fechafin, Server *s){
    sqlite3* db;
    int status = sqlite3_open("base_datos.db", &db);
    sqlite3_stmt *stmt;

    const char *sql = "SELECT HABITACION.ID_HABITACION FROM HABITACION INNER JOIN RESERVA_HOTEL ON HABITACION.ID_HABITACION=RESERVA_HOTEL.ID_HABITACION WHERE (RESERVA_HOTEL.FECHA_FIN > ? AND RESERVA_HOTEL.FECHA_INI < ?)   OR (RESERVA_HOTEL.FECHA_INI > ?  AND RESERVA_HOTEL.FECHA_INI < ?);";
    int result = sqlite3_prepare_v2(db,sql,-1,&stmt, NULL);
    if (result != SQLITE_OK){
        s->Enviar("\nERROR:516\n");
        s->Recibir();
        
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return nullptr;
    }
    char *fechaFormateadaInicio = (char*) malloc(11);
    sprintf(fechaFormateadaInicio, "%d-%02d-%02d", fechaini.anyo, fechaini.mes, fechaini.dia);

    char *fechaFormateadaFin = (char*)malloc(11);
    sprintf(fechaFormateadaFin, "%d-%02d-%02d", fechafin.anyo, fechafin.mes, fechafin.dia);

    sqlite3_bind_text(stmt, 1, fechaFormateadaInicio, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, fechaFormateadaFin, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, fechaFormateadaInicio, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 4, fechaFormateadaFin, -1, SQLITE_STATIC);
    int lista[16] = {0};
    int valor = 0;
    int i = 0;
    while((result = sqlite3_step(stmt)) != SQLITE_DONE){
        valor = sqlite3_column_int(stmt, 0);
        lista[valor] = valor;
        i++;
    }
    if ( i == 15){
        s->Enviar("\nTodas las habitaciones estan ocupadas en las fechas seleccionadas.");
        s->Recibir();
        
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return nullptr;
    }
    int *lista2 = (int*) malloc(16 * sizeof(int));
    for (int i = 0; i < 16; i++) {
        lista2[i] = i;
    }

    for (int j = 0; j< 16;j++){
        if(lista[j] == j){
            lista2[j] = 0;
        }        
    }
   
    char lis[55];
    for(int k = 0; k<16; k++){
        if (lista2[k]!= 0){
            char numero[16];
            snprintf(numero,16, "%d", lista2[k]);
            strcat(lis, numero);
            strcat(lis, "\n");      
        }  
    }
    strcat(lis, "Elige una habitacion disponible: ");
    s->Enviar(lis);
    
    sqlite3_finalize(stmt);
    sqlite3_close(db);
    return lista2;
}

void mostrarHabitaciones(Server *s){
    s->Enviar("\n------------------TIPO HABITACIONES------------------\n\n\tHABITACIONES TIPO A:\n\t\tPRECIO: 50 $ x dia\n\t\tCapacidad: 1-2\n\t\tCama individual: 0\n\t\tCama matrimonial: 1\n\t\tServicio adicional: Ninguna\n\n\tHABITACIONES TIPO B:\n\t\tPRECIO: 80$ x dia\n\t\tCapacidad: 2-3\n\t\tCama individual: 1\n\t\tCama matrimonial: 1\n\t\tServicio adicional: Vistas al mar\n\n\tHABITACIONES TIPO C:\n\t\tPRECIO: 120$ x dia\n\t\tCapacidad: 4\n\t\tCama individual: 4\n\t\tCama matrimonial: 0\n\t\tServicio adicional: Terraza\n\n\tHABITACIONES TIPO D:\n\t\tPRECIO: 130$ x dia\n\t\tCapacidad: 3-4\n\t\tCama individual: 2\n\t\tCama matrimonial: 1\n\t\tServicio adicional: Wifi\n\n\t(todas las habitaciones incluyen banos y duchas)\n\n");

}