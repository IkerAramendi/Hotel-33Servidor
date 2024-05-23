#ifndef cabecera_h
#define cabecera_h

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

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
}
extern "C"{
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

int registrarCliente(Cliente *cliente);

int comprobarCliente(char *c);

int realizarReserva(Reserva *r);

int registrarUsuario(Usuario *u);

int loggear(Usuario *usuario);

int anularReserva(char *c);

int calcularOcupacion();

void excepcionNumeros(char *ve, containers::Server *s);

void excepcionDNI(char *str, containers::Server *s);

void excepcionNombre(char *str, containers::Server *s);

void excepcionApellido(char *str, containers::Server *s);

void excepcionContrasena(char *str, containers::Server *s);

int crearTipoHabitaciones();

void crearHabitaciones();

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

void mostrarReservasCliente(char *dni_cliente);

int existeBD();

void main2(containers::Server *s);


}

//#ifdef __cplusplus



//#endif
//}


#endif