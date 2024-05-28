#include<stdio.h>
#include"sqlite3.h"
#include"cabecera.h"
#include<string.h>

using namespace containers;

int registrarUsuario(Usuario *u, Server *s){
    sqlite3* db;
    sqlite3_open("base_datos.db", &db);

    sqlite3_stmt *stmt;

    const char *sql = "INSERT INTO USUARIO VALUES (?,?,?,?);";
    int result = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (result != SQLITE_OK) {
    		s->Enviar("\nERROR:518\n");
        s->Recibir();
        
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return 1;
	}


    char *nombre = (*u).nombre;
    char *apellido = (*u).apellido;
    char *DNI = (*u).DNI;
    char *contrasena = (*u).contrasena;

    sqlite3_bind_text(stmt, 1, DNI, strlen(DNI), SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, nombre, strlen(nombre), SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, apellido, strlen(apellido), SQLITE_STATIC);
    sqlite3_bind_text(stmt, 4, contrasena, strlen(contrasena), SQLITE_STATIC);

    result = sqlite3_step(stmt);
    
    if (result != SQLITE_DONE) {
        fprintf(stderr, "Error al ejecutar el statement: %s\n", sqlite3_errmsg(db));
        s->Enviar("\nERROR:502\n");
        s->Recibir();
        
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return 1;
    }
    sqlite3_finalize(stmt);
    sqlite3_close(db);
    return 0;
}


int loggear(Usuario *usuario, Server *s){

    sqlite3* db;
    sqlite3_open("base_datos.db", &db);
    sqlite3_stmt *stmt;

    const char *sql = "SELECT * FROM USUARIO WHERE contrasena LIKE ? AND DNI LIKE ?;";
    int result = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (result != SQLITE_OK) {
        s->Enviar("\nERROR:517\n");
        s->Recibir();
        
        sqlite3_finalize(stmt);
        sqlite3_close(db);
		return 1;
	}


    sqlite3_bind_text(stmt, 1, (*usuario).contrasena, -1,  SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, (*usuario).DNI, -1, SQLITE_STATIC);

    int numFilas = 0;
    int singleRow = 0;
    int acceder = 0;
    while ((result = sqlite3_step(stmt)) == SQLITE_ROW) {

        numFilas++;
        if (numFilas > 1) {
            singleRow = -1; 
            return 1;
        }

        
        if (strcmp((*usuario).contrasena, (char *)sqlite3_column_text(stmt, 3)) == 0 && strcmp((*usuario).DNI, (char *)sqlite3_column_text(stmt, 0)) == 0) {
            acceder = 1;
            strcpy((*usuario).nombre,(char *)sqlite3_column_text(stmt, 0));
            strcpy((*usuario).apellido,(char *)sqlite3_column_text(stmt, 1));        
        }
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
    if(singleRow == 0 && acceder == 1){
        return 0; //accedido con exito
    }
    else{
        return 1;
    }
}



int informacionUsuario(char *c, Server *s) {
    sqlite3 *db;
    sqlite3_open("base_datos.db", &db);

    sqlite3_stmt *stmt;
    const char *sql = "SELECT * FROM USUARIO WHERE DNI LIKE ?;";
    int result = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (result != SQLITE_OK) {
        s->Enviar("\nERROR:517\n");
        s->Recibir();
        
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return 1;
    }

    sqlite3_bind_text(stmt, 1, c, -1, SQLITE_STATIC);

    result = sqlite3_step(stmt);
    if (result == SQLITE_ROW) {
        char salida[150] = "\nInformacion del usuario.";
        
        strcat(salida, "\nDNI: ");
        strcat(salida, (char*)sqlite3_column_text(stmt, 0));
        strcat(salida, "\nNombre: ");
        strcat(salida, (char*)sqlite3_column_text(stmt, 1));
        strcat(salida, "\nApellido: ");
        strcat(salida, (char*)sqlite3_column_text(stmt, 2));
        s->Enviar(salida);
        s->Recibir();
    } else {
        s->Enviar("\nERROR:506!! DNI del usuario no encontrado.\n");
        s->Recibir();
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
    return 0;
}