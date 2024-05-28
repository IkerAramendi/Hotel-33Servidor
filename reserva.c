#include<stdio.h>
#include<string.h>
#include<time.h>

#include"sqlite3.h"
#include"cabecera.h"
#include<stdlib.h>

using namespace containers;

int realizarReserva(Reserva *r, Server *s){

    sqlite3* db;
    sqlite3_open("base_datos.db", &db);
    sqlite3_stmt *stmt;

    const char *sql = "SELECT ID_RESERVA_HOTEL FROM RESERVA_HOTEL ORDER BY ID_RESERVA_HOTEL DESC LIMIT 1;";
    int result = sqlite3_prepare_v2(db, sql, -1, &stmt , NULL);
    if (result != SQLITE_OK) {
    		s->Enviar("\nERROR:512\n");
        s->Recibir();
        sqlite3_finalize(stmt);
        sqlite3_close(db);
 	      return 1;
	}
    result = sqlite3_step(stmt);
    (*r).id_reserva_hotel = sqlite3_column_int(stmt, 0) +1;


    sqlite3_finalize(stmt);


    sqlite3_stmt *stmt1;

    const char *sql1 = "INSERT INTO RESERVA_HOTEL VALUES (?,?,?,?,?,?);";
    int result1 = sqlite3_prepare_v2(db, sql1, -1, &stmt1, NULL);
    if (result1 != SQLITE_OK) {
    		s->Enviar("\nERROR:512\n");
        s->Recibir();
        sqlite3_finalize(stmt1);
        sqlite3_close(db);
 	      return 1;
	}


     char *fechaFormateadainicio = (char*)malloc(11);

    sprintf(fechaFormateadainicio, "%d-%02d-%02d", (*r).fecha_ini.anyo, (*r).fecha_ini.mes, (*r).fecha_ini.dia);
    

    char *fechaFormateadafin = (char*)malloc(11);

    sprintf(fechaFormateadafin, "%d-%02d-%02d", (*r).fecha_fin.anyo, (*r).fecha_fin.mes, (*r).fecha_fin.dia);
    sqlite3_bind_int(stmt1, 1, (*r).id_reserva_hotel);
    sqlite3_bind_text(stmt1, 2, fechaFormateadainicio, strlen(fechaFormateadainicio), SQLITE_STATIC);
    sqlite3_bind_text(stmt1, 3, fechaFormateadafin, strlen(fechaFormateadafin), SQLITE_STATIC);
    sqlite3_bind_text(stmt1, 4, (*r).DNI, strlen((*r).DNI), SQLITE_STATIC);
    sqlite3_bind_int(stmt1, 5, (*r).numPersona);
    sqlite3_bind_int(stmt1, 6, (*r).id_habitacion);
    
    result1 = sqlite3_step(stmt1);
    if (result1 != SQLITE_DONE) {
        s->Enviar("\nERROR:512\n");
        s->Recibir();
        sqlite3_finalize(stmt1);
        sqlite3_close(db);
        return 1;
    }
    sqlite3_finalize(stmt1);
    sqlite3_close(db);
    return 0;
}







int anularReserva(char *c, Server *s){
    
    sqlite3* db;
    sqlite3_open("base_datos.db", &db);
    sqlite3_stmt *stmt;

    const char *sql = "DELETE FROM RESERVA_HOTEL WHERE  DNI LIKE ?;";

    int result = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (result != SQLITE_OK) {
    		s->Enviar("\nERROR:512\n");
        s->Recibir();
        sqlite3_finalize(stmt);
        sqlite3_close(db);
    		return 1;
	}
    sqlite3_bind_text(stmt, 1,c, -1,SQLITE_STATIC);

    
    result = sqlite3_step(stmt);
      
    if (result == SQLITE_DONE && sqlite3_changes(db) == 0) {
        s->Enviar("\nERROR:504\n");
        s->Recibir();
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return 1; 
    }
    
    sqlite3_finalize(stmt);
    sqlite3_close(db);
    return 0;
}