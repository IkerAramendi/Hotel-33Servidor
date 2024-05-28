#include "cabecera.h"
#include "sqlite3.h"
#include <stdio.h>
#include <iostream>
#include <string.h>

using namespace containers;

int realizarReservaComedor(ReservaComedor *r, Server *s){
char* err_msg;

    sqlite3* db;
    sqlite3_open("base_datos.db", &db);
    sqlite3_stmt *stmt;

    const char *sql = "SELECT * FROM RESERVA_HOTEL WHERE ID_RESERVA_HOTEL LIKE ? AND DNI LIKE ? AND FECHA_FIN > DATE('now');";
    int result = sqlite3_prepare_v2(db,sql, -1, &stmt, NULL);
    if (result != SQLITE_OK){
        s->Enviar("\nERROR:517\n");
        s->Recibir();
        
        sqlite3_finalize(stmt);
        sqlite3_close(db);
    }
    sqlite3_bind_int(stmt,1,r->getIdReservaHotel());
    sqlite3_bind_text(stmt,2, r->getDNI(),-1,SQLITE_STATIC);

    int valor = 0;
    if( sqlite3_step(stmt) == SQLITE_DONE){
        s->Enviar("\nNo hay ningun registro con esos datos.");
        s->Recibir();

    }else {
        valor = 1;
        sqlite3_stmt *stmt1;
        const char *sql1 = "SELECT ID_RESERVA_COMEDOR FROM RESERVA_COMEDOR ORDER BY ID_RESERVA_COMEDOR DESC LIMIT 1;";
        int result1 = sqlite3_prepare_v2(db, sql, -1, &stmt1, NULL);
        if (result1 != SQLITE_OK){
            s->Enviar("\nRROR:519\n");
            s->Recibir();
            
            sqlite3_finalize(stmt);
            sqlite3_close(db);
        }
        sqlite3_step(stmt1);
        r->setIdReserva(sqlite3_column_int(stmt1,0)+ 1);

        sqlite3_finalize(stmt1);
    }
    sqlite3_finalize(stmt);
    if (valor == 1){
        sqlite3_stmt *stmt2;

        const char *sql2 = "INSERT INTO RESERVA_COMEDOR VALUES (?,?,?,?,?,?);";
        int result1 = sqlite3_prepare_v2(db,sql2,-1, &stmt2, NULL);
        if (result1 != SQLITE_OK){
            s->Enviar("\nRROR:519\n");
            s->Recibir();
            
            sqlite3_finalize(stmt2);
            sqlite3_close(db);
        }
        sqlite3_bind_int(stmt2,1,r->getIdReserva());
        sqlite3_bind_text(stmt2,2,r->getDNI(),strlen(r->getDNI()),SQLITE_STATIC);
        sqlite3_bind_int(stmt2,3,r->getIdReservaHotel());
        sqlite3_bind_int(stmt2,4,r->getNumPersonas());
        sqlite3_bind_int(stmt2,6,r->getNumeroComidasPorDia());
        sqlite3_bind_double(stmt2,7,r->getPrecio());

        sqlite3_step(stmt2);
        

        if (result != SQLITE_DONE) {
            s->Enviar("\nRROR:519\n");
            s->Recibir();
            
            sqlite3_finalize(stmt2);
            sqlite3_close(db);
        }

        sqlite3_finalize(stmt2);


    }

    sqlite3_close(db);
    return 1;
}