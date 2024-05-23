#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include"cabecera.h"
#include"sqlite3.h"



void funcion(){

    if (!existeBD()) {
        crearBD();
        crearTipoHabitaciones();
        crearHabitaciones();
    }
    char ve;
    while (ve != '3'){
        fflush(stdin);

        printf("\nBIENVENIDO A HOTEL 33");
        printf("\n1. Iniciar Sesion");
        printf("\n2. Registrar Usuario");
        printf("\n3. Salir del programa\n");
        printf("Introduzca la opcion deseada: ");
        ve = getchar();
        fflush(stdin);
        excepcionNumeros(&ve);

        if (ve == '1'){
            while (ve != '6'){

                //INICIAR SESION

                printf("\n INICIO SESION\n");

                Usuario *usuario = malloc(sizeof(Usuario));

                printf("Introduzca su DNI: ");
                scanf("%s", (*usuario).DNI);
                excepcionDNI((*usuario).DNI);
                fflush(stdin); 

    
                printf("Introduzca su contrasena: ");
                scanf("%s",(*usuario).contrasena);
                excepcionContrasena((*usuario).contrasena);
                fflush(stdin);


                int acceso = loggear(usuario);  

                if (acceso == 0){
                    char mensaje[100];
                    sprintf(mensaje, "El usuario con DNI %s ha iniciado sesión.", usuario->DNI);
                    logInicioSesion(mensaje);

                    while (acceso == 0){
                        printf("\n1. Realizar reserva");
                        printf("\n2. Anular reserva");
                        printf("\n3. Historial de reservas por cliente (DNI)");
                        printf("\n4. Consultar datos habitaciones");
                        printf("\n5. Consultar datos usuario");
                        printf("\n6. Cerrar sesion");
                        printf("\nIntroduzca la opcion deseada:");

                        ve = getchar();
                        fflush(stdin); 
                        excepcionNumeros(&ve);


                        if (ve == '1'){
                            Reserva *r = malloc(sizeof(Reserva));
                            printf("¿Tiene registrado sus datos? (Si es asi pulsa S): ");
                            char registro = getchar();
                            fflush(stdin); 

                            if ((registro == 'S') || (registro =='s')){
                                printf("\nIndique su DNI: ");
                                scanf("%s", (*r).DNI);  
                                int valor = comprobarCliente((*r).DNI);
                                while (valor != 0){
                                    printf("El DNI no esta en la base de datos introduzcala de nuevo: ");
                                    scanf("%s", (*r).DNI);  

                                    valor = comprobarCliente((*r).DNI);
                                }                    

                            }
                            else{
                                Cliente *c = malloc(sizeof(Cliente));
                                if (c == NULL) {
                                    printf("Error: No se pudo asignar memoria para el cliente.\n");
                                    exit(1);
                                    }

                                printf("\nIndique su DNI: ");
                                scanf("%s", (*c).DNI);  
                                excepcionDNI((*c).DNI);

                                printf("\nIndique su nombre: ");
                                scanf("%s", (*c).nombre);  
                                excepcionNombre((*c).nombre);
                            
                                printf("\nIndique su apellido: ");
                                scanf("%s", (*c).apellido);  
                                excepcionApellido((*c).apellido);

                                printf("\nIndique su telefono: ");
                                scanf("%s", (*c).telefono);  
                                fflush(stdin);
                                excepcionNumeroTelefono((*c).telefono);

                                printf("\nIndique su numero de tarjeta: ");
                                scanf("%s", (*c).num_tarjeta);  
                                fflush(stdin);
                                excepcionNumeroTarjeta((*c).num_tarjeta);

                                printf("\nIndique su anyo de nacimiento: ");
                                scanf("%i", &(*c).fecha_nac.anyo);
                                fflush(stdin);
                                excepcionAnyoNacimiento(&(*c).fecha_nac.anyo);

                                printf("\nIndique su mes de nacimiento: ");
                                scanf("%i", &(*c).fecha_nac.mes);  
                                fflush(stdin);
                                excepcionMesReserva(&(*c).fecha_nac.mes);

                                printf("\nIndique su dia de nacimiento: ");
                                scanf("%i", &(*c).fecha_nac.dia);  
                                fflush(stdin);
                                excepcionDiaReserva(&(*c).fecha_nac.mes, &(*c).fecha_nac.dia);                                

                                registrarCliente(c);

                            }
                            int correcto = 0;
                            while(correcto != 1){
                                printf("\nAno inicio: ");
                                scanf("%i", &(*r).fecha_ini.anyo);
                                fflush(stdin);
                                excepcionAnyoReserva(&(*r).fecha_ini.anyo);

                                printf("\nMes inicio: ");  
                                scanf("%i", &(*r).fecha_ini.mes);
                                fflush(stdin);
                                excepcionMesReserva(&(*r).fecha_ini.mes);

                                printf("\nDia inicio:");
                                scanf("%i", &(*r).fecha_ini.dia);  
                                fflush(stdin);
                                excepcionDiaReserva(&(*r).fecha_ini.mes, &(*r).fecha_ini.dia);

                                printf("\nAno fin:");
                                scanf("%i", &(*r).fecha_fin.anyo);  
                                fflush(stdin);
                                excepcionAnyoReserva(&(*r).fecha_fin.anyo);

                                printf("\nMes fin:");
                                scanf("%i", &(*r).fecha_fin.mes);
                                fflush(stdin);
                                excepcionMesReserva(&(*r).fecha_fin.mes);  

                                printf("\nDia fin:");
                                scanf("%i", &(*r).fecha_fin.dia);
                                fflush(stdin);
                                excepcionDiaReserva(&(*r).fecha_fin.mes, &(*r).fecha_fin.dia);

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

                            printf("\nNumero de Personas: ");
                            scanf("%i", &(*r).numPersona);
                            fflush(stdin);
                            excepcionNumeroPersonas(&(*r).numPersona);



                            mostrarHabitaciones();
                            printf("\nQue tipo de habitacion quieres: ");
                            int *lista;
                            lista = disponibilidadHabitaciones((*r).fecha_ini,(*r).fecha_fin);
                            printf("\nElige una habitacion disponible: ");
                            int valor = 0;
                            scanf("%i",&(*r).id_habitacion);
                            fflush(stdin);

                            while (lista[(*r).id_habitacion] == 0){
                                printf("\nElige una habitacion disponible: ");
                                scanf("%i",&(*r).id_habitacion);

                            }
                            fflush(stdin);

                            realizarReserva(r);
                            char mensaje[100];
                            sprintf(mensaje, "Se ha relizado la reserva %i.", (*r).id_reserva_hotel);
                            logInicioSesion(mensaje);
                            free(r);
                            r = NULL;

                            


                        }
                        else if (ve == '2'){
                            fflush(stdin);

                            Cliente *c = malloc(sizeof(Cliente));
                            printf("\nIndique el DNI: ");
                            scanf("%s",(*c).DNI);
                            fflush(stdin);
                            excepcionDNI((*c).DNI);
                            anularReserva((*c).DNI);
                            fflush(stdin);
                            char mensaje[100];
                            sprintf(mensaje, "Se han anulado todas las reservas de %s.", (*c).DNI);
                            logInicioSesion(mensaje);


                        }
                        else if (ve == '3'){
                            Cliente *c = malloc(sizeof(Cliente));
                            printf("\nIndique el DNI: ");
                            scanf("%s",(*c).DNI);
                            fflush(stdin);
                            excepcionDNI((*c).DNI);
                            mostrarReservasCliente((*c).DNI);

                        }
                        else if (ve == '4'){
                            mostrarHabitaciones();
                        }
                        else if (ve == '5'){
                            Usuario *u = malloc(sizeof(Usuario));
                            printf("\nIndique el DNI del usuario que quieres informarte: ");
                            scanf("%s", (*u).DNI);  
                            excepcionDNI((*u).DNI);
                            informacionUsuario((*u).DNI);
                        }
                        else if (ve =='6'){
                            free(usuario);
                            acceso = 1;
                        }
                    }
                }
                else{
                    printf("\nDatos incorrectos");
                    printf("\nSi quieres salir pulsa 6, sino, pulsa otro boton: ")  ;
                    ve = getchar();
                }
            }
        }
        else if (ve == '2'){
            //REGISTRAR USUARIO
            printf("\nREGISTRO USUARIO\n");
            Usuario *usuario;
            usuario = (Usuario*) malloc(sizeof(Usuario));

            printf("Introduzca su DNI: ");
            scanf("%s", (*usuario).DNI);        
            fflush(stdin); 
            excepcionDNI((*usuario).DNI);

            printf("Introduzca su nombre: ");
            scanf("%s", (*usuario).nombre);
            fflush(stdin);
            excepcionNombre((*usuario).nombre);

            printf("Introduzca su apellido: ");
            scanf("%s", (*usuario).apellido);
            fflush(stdin); 
            excepcionApellido((*usuario).apellido);

            printf("Introduzca su contrasena: ");
            scanf("%s", (*usuario).contrasena);
            fflush(stdin); 
            excepcionContrasena((*usuario).contrasena);

            registrarUsuario(usuario);
            
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
