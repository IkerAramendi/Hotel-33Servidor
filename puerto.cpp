#include "cabecera.h"
#include <string>
#include <iostream>
#include <fstream>
using namespace std;
using namespace containers;


int containers::obtenerNumeroPuertoArchivo(const char* nombreArchivo){
    int puerto = 0;
    ifstream archivo (nombreArchivo);
    if(archivo.is_open()){
        archivo >> puerto;

    }else{
        cout<<"Error al abrir el archivo"<<endl;
    }

    return puerto;

}