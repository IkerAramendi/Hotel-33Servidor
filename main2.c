#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include <cstring>
#include"cabecera.h"
#include"sqlite3.h"


using namespace containers;
void main2(Server* s){

    if (!existeBD()) {
        crearBD();
        crearTipoHabitaciones();
        crearHabitaciones();
    }
    char ve;
    while (ve != '3'){
        fflush(stdin);
        s->Enviar("\nBIENVENIDO A HOTEL 33\n1. Iniciar Sesion\n2. Registrar Usuario\n3. Salir del programa\nIntroduzca la opcion deseada:  ");
        ve = (s->Recibir())[0];
        
        fflush(stdin);
        excepcionNumeros(&ve, s);

        if (ve == '1'){
            while (ve != '6'){

                //INICIAR SESION


                Usuario *usuario = (Usuario*)malloc(sizeof(Usuario));

                
                s->Enviar("\n INICIO SESION\nIntroduzca su DNI:  ");
                strncpy((*usuario).DNI, s->Recibir(), 10);                  
                excepcionDNI((*usuario).DNI, s);
                

                s->Enviar("Introduzca su contrasena:  ");
                strncpy((*usuario).contrasena,s->Recibir(), 16);
                excepcionContrasena((*usuario).contrasena, s);


                int acceso = loggear(usuario);  

                if (acceso == 0){
                    s->Enviar("\nCODIGO:201\n");
                    char mensaje[100];
                    sprintf(mensaje, "El usuario con DNI %s ha iniciado sesión.", usuario->DNI);
                    logInicioSesion(mensaje);

                    while (acceso == 0){
                        s->Enviar("\n1. Realizar reserva\n2. Anular reserva\n3. Historial de reservas por cliente (DNI)\n4. Consultar datos habitaciones\n5. Consultar datos usuario\n6. Cerrar sesion\nIntroduzca la opcion deseada:  ");
                        
                        

                        ve = (s->Recibir())[0];
                        excepcionNumeros(&ve, s);


                        if (ve == '1'){
                            Reserva *r = (Reserva*) malloc(sizeof(Reserva));
                            s->Enviar("¿Tiene registrado sus datos? (Si es asi pulsa S):  ");
                            char registro = (s->Recibir())[0];

                            if ((registro == 'S') || (registro =='s')){
                                s->Enviar("\nIndique su DNI:  ");
                                strncpy((*r).DNI, s->Recibir(), 10);
                                excepcionDNI((*r).DNI, s);
                                
                                int valor = comprobarCliente((*r).DNI);
                                
                                while (valor != 0){
                                    s->Enviar("\n ERROR:503!! DNI no econtrado introduzcalo de nuevo:  \n");
                                    strncpy((*r).DNI, s->Recibir(), 10); 
                                    excepcionDNI((*r).DNI, s);
                                    valor = comprobarCliente((*r).DNI);
                                }                    

                            }
                            else{
                                Cliente *c =  (Cliente*) malloc(sizeof(Cliente));
                                if (c == NULL) {
                                    s->Enviar("\nERROR:507!! Error registrando cliente.\n");
                                    exit(1);
                                    }
                                s->Enviar("\nIndique su DNI: ");
                                strncpy((*c).DNI, s->Recibir(), 10);  
                                excepcionDNI((*c).DNI, s);
                                strcpy((*r).DNI,(*c).DNI);

                                s->Enviar("\nIndique su nombre:  ");
                                strncpy((*c).nombre, s->Recibir(), 16);
                                excepcionNombre((*c).nombre, s);
                            
                                s->Enviar("\nIndique su apellido:  ");
                                strncpy((*c).apellido, s->Recibir(), 16);
                                excepcionApellido((*c).apellido, s);

                                s->Enviar("\nIndique su telefono:  ");
                                strncpy((*c).telefono, s->Recibir(), 10);
                              
                                excepcionNumeroTelefono((*c).telefono, s);

                                s->Enviar("\nIndique su numero de tarjeta:  ");
                                strncpy((*c).num_tarjeta, s->Recibir(), 20); 
                                excepcionNumeroTarjeta((*c).num_tarjeta, s);

                                s->Enviar("\nIndique su anyo de nacimiento:  ");
                                char subbuffer[5];
                                subbuffer[4] = '\0';
                                strncpy(subbuffer, s->Recibir(), 4);
                                (*c).fecha_nac.anyo = atoi(subbuffer);
                                excepcionAnyoNacimiento(&(*c).fecha_nac.anyo, s);

                                char subbuffer2[3];
                                s->Enviar("\nIndique su mes de nacimiento:  ");
                                subbuffer2[2] = '\0';
                                strncpy(subbuffer2, s->Recibir(), 3);
                                (*c).fecha_nac.mes = atoi(subbuffer2);
                                excepcionMesReserva(&(*c).fecha_nac.mes, s);

                                char subbuffer3[3];
                                s->Enviar("\nIndique su dia de nacimiento:  ");
                                subbuffer3[2] = '\0';
                                strncpy(subbuffer3, s->Recibir(), 3); 
                                (*c).fecha_nac.dia = atoi(subbuffer3);
                                excepcionDiaReserva(&(*c).fecha_nac.mes, &(*c).fecha_nac.dia, s);                                

                                registrarCliente(c);
                                s->Enviar("\nCODIGO:208\n");

                            }
                            int correcto = 0;
                            while(correcto != 1){
                            
                                char subbuffer[5];
                                subbuffer[4] = '\0';
                                s->Enviar("\nAno inicio:  ");
                                strncpy(subbuffer, s->Recibir(), 5);
                                (*r).fecha_ini.anyo = atoi(subbuffer);
                                excepcionAnyoReserva(&(*r).fecha_ini.anyo, s);
                                
                                char subbuffer1[3];
                                subbuffer1[2] = '\0';
                                s->Enviar("\nMes inicio:  ");
                                strncpy(subbuffer1, s->Recibir(), 3);
                                (*r).fecha_ini.mes = atoi(subbuffer1);
                                excepcionMesReserva(&(*r).fecha_ini.mes, s);
                                
                                char subbuffer2[3];
                                subbuffer2[2] = '\0';
                                s->Enviar("\nDia inicio:  ");
                                strncpy(subbuffer2, s->Recibir(), 3);
                                (*r).fecha_ini.dia = atoi(subbuffer2);
                                excepcionDiaReserva(&(*r).fecha_ini.mes, &(*r).fecha_ini.dia, s);
                                
                                char subbuffer3[5];
                                subbuffer3[4] = '\0';
                                s->Enviar("\nAno fin:  ");
                                strncpy(subbuffer3, s->Recibir(), 5);
                                (*r).fecha_fin.anyo =atoi(subbuffer3);
                                excepcionAnyoReserva(&(*r).fecha_fin.anyo, s);
                                
                                char subbuffer4[3];
                                subbuffer4[2] = '\0';
                                s->Enviar("\nMes fin:  ");
                                strncpy(subbuffer4, s->Recibir(), 3);
                                (*r).fecha_fin.mes = atoi(subbuffer4);
                                excepcionMesReserva(&(*r).fecha_fin.mes, s);  
                                
                                char subbuffer5[3];
                                subbuffer5[2] = '\0';
                                s->Enviar("\nDia fin:  ");
                                strncpy(subbuffer5, s->Recibir(), 3);
                                (*r).fecha_fin.dia = atoi(subbuffer5);
                                excepcionDiaReserva(&(*r).fecha_fin.mes, &(*r).fecha_fin.dia, s);

                                if((*r).fecha_ini.anyo < (*r).fecha_fin.anyo){
                                    correcto = 1;
                                }
                                else if((*r).fecha_ini.anyo  == (*r).fecha_fin.anyo && (*r).fecha_ini.mes < (*r).fecha_fin.mes){
                                     correcto = 1;
                                }
                                else if((*r).fecha_ini.anyo  == (*r).fecha_fin.anyo && (*r).fecha_ini.mes == (*r).fecha_fin.mes && (*r).fecha_ini.dia < (*r).fecha_fin.dia){
                                    correcto = 1;
                                }
                            }   

                            s->Enviar("\nNumero de Personas:  ");
                            char buffer[2];
                            buffer[1] = '\0';
                            strncpy(buffer, s->Recibir(),2);
                            (*r).numPersona = atoi(buffer);
                            excepcionNumeroPersonas(&(*r).numPersona, s);
                            



                            mostrarHabitaciones(s);
                            s->Recibir();
                            int *lista;
                            lista = disponibilidadHabitaciones((*r).fecha_ini,(*r).fecha_fin, s);
                            
                            //s->Enviar("\nElige una habitacion disponible:  ");
                            char buffer1[3];
                            //buffer[2] = '\0';
                            //strncpy(buffer1, s->Recibir(),3);
                            //(*r).id_habitacion = atoi(buffer1);
                            

                            while (lista[(*r).id_habitacion] == 0){
                                s->Enviar("\nElige una habitacion disponible:  ");
                                
                                buffer[2] = '\0';
                                strncpy(buffer1, s->Recibir(),3);
                                (*r).id_habitacion = atoi(buffer1);

                            }

                            realizarReserva(r);
                            s->Enviar("\nCODIGO:203\n");
                            char mensaje[100];
                            sprintf(mensaje, "Se ha relizado la reserva %i.", (*r).id_reserva_hotel);
                            logInicioSesion(mensaje);
                            free(r);
                            r = NULL;

                            


                        }
                        else if (ve == '2'){
                            

                            Cliente *c = (Cliente*) malloc(sizeof(Cliente));
                            
                            s->Enviar("\nIndique el DNI:  ");
                            strncpy((*c).DNI, s->Recibir(), 10);  
                            excepcionDNI((*c).DNI, s);
                            anularReserva((*c).DNI);
                            s->Enviar("\nCODIGO:204\n");
                            char mensaje[100];
                            sprintf(mensaje, "Se han anulado todas las reservas de %s.", (*c).DNI);
                            logInicioSesion(mensaje);


                        }
                        else if (ve == '3'){
                            Cliente *c = (Cliente*) malloc(sizeof(Cliente));
                            
                            s->Enviar("\nIndique el DNI: ");
                            strncpy((*c).DNI, s->Recibir(), 10);  
                            excepcionDNI((*c).DNI, s);
                            mostrarReservasCliente((*c).DNI);
                            s->Enviar("\nCODIGO:205\n");
                            free(c);
                            c = NULL;

                        }
                        else if (ve == '4'){
                            mostrarHabitaciones(s);
                            s->Enviar("\nCODIGO:207\n");

                            
                        }
                        else if (ve == '5'){
                            Usuario *u =  (Usuario*) malloc(sizeof(Usuario));
                            s->Enviar("\nIndique el DNI del usuario que quieres informarte:  ");
                            strncpy((*u).DNI, s->Recibir(), 10);  
                            excepcionDNI((*u).DNI, s);  
                            informacionUsuario((*u).DNI, s);
                            s->Enviar("\nCODIGO:206\n");

                        }
                        else if (ve =='6'){
                            free(usuario);
                            acceso = 1;
                        }
                    }
                }
                else{
                    s->Enviar("\nERROR:501!! Datos incorrectos\nSi quieres salir pulsa 6, sino, pulsa otro boton:  ");
                    ve = (s->Recibir())[0];
                }
            }
        }
        else if (ve == '2'){
            //REGISTRAR USUARIO
            
            Usuario *usuario;
            usuario =  (Usuario*) malloc(sizeof(Usuario));
            
            s->Enviar("\nREGISTRO USUARIO\nIntroduzca su DNI:  ");
            strncpy((*usuario).DNI, s->Recibir(), 10);  
            excepcionDNI((*usuario).DNI, s);

            s->Enviar("Introduzca su nombre: ");
            strncpy((*usuario).nombre, s->Recibir(), 16);
            excepcionNombre((*usuario).nombre, s);

            s->Enviar("Introduzca su apellido: ");
            strncpy((*usuario).apellido, s->Recibir(), 16);
            excepcionApellido((*usuario).apellido, s);

            s->Enviar("Introduzca su contrasena: ");
            strncpy((*usuario).contrasena, s->Recibir(), 16);
            excepcionContrasena((*usuario).contrasena, s);

            registrarUsuario(usuario);
            
            s->Enviar("\nCODIGO:202\n");
            char mensaje[100];
            sprintf(mensaje, "El usuario con DNI %s se ha registrado.", (*usuario).DNI);
            logInicioSesion(mensaje);
            free(usuario);
            usuario = NULL;
            }
        else if (ve == '3'){

            //SALIR DEL PROGRAMA

        }
    }
}
