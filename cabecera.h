#ifndef cabecera_h
#define cabecera_h

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string>
#include <arpa/inet.h>
#include <string>

namespace containers{
  class Server {
  public:
      int server, client;
      struct sockaddr_in serverAddr, clientAddr;
      char buffer[1024];
      Server();
      char* Recibir();
      void Enviar(const char *mensaje);
      void CerrarSocket();


  };
  
  int obtenerNumeroPuertoArchivo(const char *nombreArchivo);
  
  
  class ReservaServicio{
    private:
        int idReserva;
        int idReservaHotel;
        char DNI[10];
        int numPersonas;
        int numDias;
        double precio;

    public:
        ReservaServicio();
        ReservaServicio(int, char*, int);
        ~ReservaServicio();

        virtual double calcularPrecio() = 0;
        void setIdReserva(int);
        void setIdReservaHotel(int);
        void setDNI(char*);
        void setNumPersonas(int);
        void setNumDias(int);
        void setPrecio(double);

        int getIdReserva();
        int getIdReservaHotel();
        char* getDNI();
        int getNumPersonas();
        int getNumDias();
        double getPrecio();


};

class ReservaGym : public ReservaServicio {
    private:
        char tipo[10];
        
    public:
        ReservaGym();
        ReservaGym(int, char* , int, char tipo[10]);
        ~ReservaGym();
        double calcularPrecio() override;
        void setTipo(char tipo[10]);
        char* getTipo();

};

class ReservaComedor : public ReservaServicio{
    private:
        int numeroComidasPorDia;
    public:
        ReservaComedor();
        ReservaComedor(int, char* , int, int);
        ~ReservaComedor();
        double calcularPrecio() override;
        void setNumeroComidasPorDia(int);
        int getNumeroComidasPorDia();
};
  
  
  
}

extern "C"{

int realizarReservaComedor(containers::ReservaComedor*, containers::Server *s);
int realizarReservaGym(containers::ReservaGym*, containers::Server *s);

typedef struct{
    int dia;
    int mes;
    int anyo;
} Fecha;

typedef struct{
    char DNI[10];
    char nombre[15];
    char apellido[15];
    char telefono[10];
    char num_tarjeta[20];
    Fecha fecha_nac;
} Cliente;

typedef struct{
    char DNI[10];
    char nombre[15];
    char apellido[15];
    char contrasena[15];
} Usuario;


typedef struct{
    int id_tipo_comida;
    int precio_comida;
    char *nombre;
} Tipo_comida;

typedef struct{
    char id_tipo_habitacion;
    int precio;
} Tipo_habitacion;

typedef struct{
    int id_habitacion;
    char id_tipo_habitacion;
    int capacidad;
    char nombre[15];
    
} Habitacion;

typedef struct{
    int id_reserva_hotel;
    char DNI[10];
    int id_habitacion;
    int numPersona;
    Fecha fecha_ini;
    Fecha fecha_fin;
} Reserva;

void crearBD();

int registrarCliente(Cliente *cliente, containers::Server *s);

int comprobarCliente(char *c, containers::Server *s);

int realizarReserva(Reserva *r, containers::Server *s);

int registrarUsuario(Usuario *u, containers::Server *s);

int loggear(Usuario *usuario, containers::Server *s);

int anularReserva(char *c, containers::Server *s);

int calcularOcupacion();

void excepcionNumeros(char *ve, containers::Server *s);

void excepcionDNI(char *str, containers::Server *s);

void excepcionNombre(char *str, containers::Server *s);

void excepcionApellido(char *str, containers::Server *s);

void excepcionContrasena(char *str, containers::Server *s);

int crearTipoHabitaciones(containers::Server *s);

void crearHabitaciones(containers::Server *s);

void mostrarHabitaciones(containers::Server *s);

int* disponibilidadHabitaciones(Fecha fechaini, Fecha fechafin, containers::Server *s);

void excepcionAnyoReserva(int *anyo, containers::Server *s);

void excepcionMesReserva(int *mes, containers::Server *s);

void excepcionDiaReserva(int *mes , int *dia, containers::Server *s);

void excepcionNumeroPersonas(int *num, containers::Server *s);

void excepcionNumeroTelefono(char *str, containers::Server *s);

void excepcionNumeroTarjeta(char *str, containers::Server *s);

void logInicioSesion(char *message);

void excepcionAnyoNacimiento(int *anyo, containers::Server *s);

int informacionUsuario(char *c, containers::Server *s);

void mostrarReservasCliente(char *dni_cliente, containers::Server *s);

int existeBD();

void main2(containers::Server *s);


}



#endif