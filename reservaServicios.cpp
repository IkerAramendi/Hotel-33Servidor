#include "cabecera.h"
#include <iostream>
#include <cstring>
#include "sqlite3.h"


using namespace std;
using namespace containers;


ReservaServicio::ReservaServicio(){

    this->idReserva = 0;
    this->idReservaHotel = 0;
    strcpy(this->DNI ,"012345678");
    this->numPersonas = 0;
    this->precio = 0;
}
ReservaServicio::ReservaServicio(int idReservaHotel, char *dni, int numPersonas){

    this->idReservaHotel = idReservaHotel;
    strcpy(this->DNI ,dni);
    this->numPersonas = numPersonas;
}
ReservaServicio::~ReservaServicio(){

    delete this;
}

double ReservaGym::calcularPrecio() {
    double precio = 0;
    precio = this->getNumPersonas() * 10.5;
    this->setPrecio(precio);
    return precio;
}

double ReservaComedor::calcularPrecio() {
    double precio = 0;
    precio =  this->getNumeroComidasPorDia() * this->getNumPersonas() * 15.25;
    this->setPrecio(precio);
    return precio;
}

void ReservaServicio::setIdReserva(int id){
    this->idReserva = id;}

void ReservaServicio::setIdReservaHotel(int id){
    this->idReservaHotel = id;}

void ReservaServicio::setDNI(char *dni){
    strcpy(this->DNI, dni);}

void ReservaServicio::setNumPersonas(int numero){
    this->numPersonas = numero;}


void ReservaServicio::setPrecio(double precioTotal){
    this->precio = precioTotal;}

int ReservaServicio::getIdReserva(){
    return this->idReserva;

}
int ReservaServicio::getIdReservaHotel(){
    return this->idReservaHotel;
}
char* ReservaServicio::getDNI(){
    return this->DNI;
}
int ReservaServicio::getNumPersonas(){
    return this->numPersonas;

}

double ReservaServicio::getPrecio(){
        return this->precio;
}

//GYM
ReservaGym::ReservaGym(){
    strcpy(this->tipo, "");
}
ReservaGym::ReservaGym(int idReservaHotel, char *dni, int numPersonas, char tipo[10]):ReservaServicio(idReservaHotel,dni,numPersonas){
    strcpy(this->tipo, tipo);
}

void ReservaGym::setTipo(char tipo[10]){
    strcpy(this->tipo, tipo);

}
char* ReservaGym::getTipo(){
    return this->tipo;

}

ReservaGym::~ReservaGym(){
    delete this;
}

//COMEDOR
ReservaComedor::ReservaComedor(){
    this->numeroComidasPorDia = 0;
}

ReservaComedor::ReservaComedor(int idReservaHotel, char *dni, int numPersonas,int numeroComidasPorDia):ReservaServicio(idReservaHotel,dni,numPersonas){
    this->numeroComidasPorDia = numeroComidasPorDia;
}

void ReservaComedor::setNumeroComidasPorDia(int numero){
    this->numeroComidasPorDia = numero;
}
        
        
int ReservaComedor::getNumeroComidasPorDia(){
    return this->numeroComidasPorDia;
}

ReservaComedor::~ReservaComedor(){
    delete this;
}


