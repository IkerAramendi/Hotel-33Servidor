#include "cabecera.h"
#include "sqlite3.h"
#include <stdio.h>
#include <iostream>
#include <string.h>

using namespace containers;

int realizarReservaGym(ReservaGym *r, Server *s){
char* err_msg;

    printf("\n%i",r->getIdReserva());
        printf("\n%s",r->getDNI());
        printf("\n%i",r->getNumPersonas());
        printf("\n%i",r->getIdReservaHotel());
        printf("\n%d",r->getPrecio());
    sqlite3* db;
    sqlite3_open("base_datos.db", &db);
    sqlite3_stmt *stmt;
    
    const char *sql = "SELECT * FROM RESERVA_HOTEL WHERE  DNI LIKE ? AND ID_RESERVA_HOTEL LIKE ? AND FECHA_FIN > DATE('now') AND FECHA_INI < DATE('now');";
    int result = sqlite3_prepare_v2(db,sql, -1, &stmt, NULL);
    if (result != SQLITE_OK){
        s->Enviar("\nERROR:517\n");
        s->Recibir();
        
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return 0;
    }
    sqlite3_bind_int(stmt,2,r->getIdReservaHotel());
    sqlite3_bind_text(stmt,1, r->getDNI(),-1,SQLITE_STATIC);

    int valor = 0;
    if( sqlite3_step(stmt) == SQLITE_DONE){
        
        s->Enviar("\nNo hay ningun registro con esos datos.");
        s->Recibir();
        
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return 0;

    }else {
    
        
        r->setNumPersonas((int)sqlite3_column_int(stmt,4));
        
        valor = 1;
        sqlite3_stmt *stmt1;
        const char *sql1 = "SELECT ID_RESERVA_GYM FROM RESERVA_GYM ORDER BY ID_RESERVA_GYM DESC LIMIT 1;";
        int result1 = sqlite3_prepare_v2(db, sql1, -1, &stmt1, NULL);
        if (result1 != SQLITE_OK){
            
            s->Enviar("\nERROR:520\n");
            s->Recibir();
            
            sqlite3_finalize(stmt1);
            sqlite3_close(db);
            return 0;

        }
        sqlite3_step(stmt1);
        r->setIdReserva(sqlite3_column_int(stmt1,0)+ 1);

        sqlite3_finalize(stmt1);
    }

    sqlite3_finalize(stmt);
    if (valor == 1){
        sqlite3_stmt *stmt2;

        const char *sql2 = "INSERT INTO RESERVA_GYM VALUES (?,?,?,?,?);";
        int result2 = sqlite3_prepare_v2(db,sql2,-1, &stmt2, NULL);
        if (result2 != SQLITE_OK){
        
           s->Enviar("\nERROR:520\n");
            s->Recibir();
            
            sqlite3_finalize(stmt2);
            sqlite3_close(db);
            return 0;
        }
        
        r->setPrecio(r->calcularPrecio());
        
        sqlite3_bind_int(stmt2,1,r->getIdReserva());
        sqlite3_bind_text(stmt2,2,r->getDNI(),strlen(r->getDNI()),SQLITE_STATIC);
        sqlite3_bind_int(stmt2,3,r->getNumPersonas());  
        sqlite3_bind_int(stmt2,4,r->getIdReservaHotel());
        sqlite3_bind_double(stmt2,5,r->getPrecio());

        result2 = sqlite3_step(stmt2);
        

        if (result2 != SQLITE_DONE) {
            s->Enviar("\n3333\n");
            s->Recibir();
            s->Enviar("\nERROR:520\n");
            s->Recibir();
            
            sqlite3_finalize(stmt2);
            sqlite3_close(db);
            return 0;
        }

        sqlite3_finalize(stmt2);


    }

    sqlite3_close(db);
    return 1;
}