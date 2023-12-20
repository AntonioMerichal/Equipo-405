#ifndef FUNCIONES_H
#define FUNCIONES_H

#include <iostream>
using namespace std;
#include "usuario.h"
#include "actividad.h"

#define RED_TEXT "\033[1;31m"
#define RESET_COLOR "\033[0m"

#define RESET   "\033[0m"
#define BLUE    "\033[34m"

int menu()
{
    
    cout << RED_TEXT << "***********************************" << endl;
    cout << "            MENÚ PRINCIPAL" << endl;
    cout << "***********************************" << RESET_COLOR << endl;
    cout << "1) Login" << endl;
    cout << "2) Registrarme" << endl;
    cout << "3) Mostrar actividades" << endl;
    cout << "0) SALIR" << endl;
    cout << RED_TEXT << "***********************************" << RESET_COLOR << endl;
    cout << "Introduce el número de la opción deseada: ";
    int opcion;
    cin >> opcion;
    return opcion;
}

int menuOrganizador()
{
    cout << BLUE << "***********************************" << endl;
    cout << "            MENÚ ORGANIZADOR" << endl;
    cout << "***********************************" << RESET_COLOR << endl;
    cout << "1) Crear actividad" << endl;
    cout << "2) Mostrar actividad" << endl;
    cout << "3) Modificar actividades" << endl;
    cout << "4) Borrar actividades" << endl;
    cout << "0) SALIR" << endl;
    cout << BLUE << "***********************************" << RESET_COLOR << endl;
    cout << "Introduce el número de la opción deseada: ";
    int opcion;
    cin >> opcion;
    return opcion;
}
int menuUsuario()
{
    cout << "***********************************" << endl;
    cout << "         MENÚ USUARIO" << endl;
    cout << "***********************************" << endl;
    cout << "1) Elije actividad" << endl;
    cout << "2) Añadirse a la actividad" << endl;
    cout << "3) Modificar actividades" << endl;
    cout << "4) Borrar actividades" << endl;
    cout << "0) SALIR" << endl;
    cout << "***********************************" << endl;
    cout << "Introduce el número de la opción deseada: ";
    int opcion;
    cin >> opcion;
    return opcion;
}
int menuDirector()
{
    cout << "***********************************" << endl;
    cout << "     MENÚ DIRECTOR ACADÉMICO" << endl;
    cout << "***********************************" << endl;
    cout << "1) Borrar usuario actividad" << endl;
    cout << "2) Añadirse a la actividad" << endl;
    cout << "3) Borrarse de la actividad" << endl;
    cout << "0) SALIR" << endl;
    cout << "***********************************" << endl;
    cout << "Introduce el número de la opción deseada: ";
    int opcion;
    cin >> opcion;
    return opcion;
}



void pedirDatosUsuario(Usuario &nuevo)
{
    string usuario, nombre, pass;
    cout << "Introduce tu nombre de usuario: ";
    cin >> usuario;
    cout << "Introduce tu nombre completo: ";
    getchar();
    getline(cin,nombre);
    cout << "Introduce la contraseña: ";
    cin >> pass;
    nuevo.setUsuario(usuario);
    nuevo.setNombre(nombre);
    nuevo.setPass(pass);
    nuevo.setRol(rol_enum::USUARIO);
    nuevo.setEstado(estado_usuario_enum::VISITANTE);
}

void pedirDatosAct(Actividad &nueva)
{
    string nombre_act, descripcion,fechaInicio, fechaFinal;
    int id;
    cout << "Introduce id de actividad: ";
    cin >> id; 
    cout << "Introduce nombre de actividad: ";
    cin >> nombre_act;
    cout << "Introduce tu descripcion: ";
    getchar();
    getline(cin,descripcion);
    cout << "Introduce la fecha de inicio: ";
    cin >> fechaInicio;
    cout << "Introduce la fecha de final: ";
    cin >> fechaFinal;
    nueva.setId(id);
    nueva.setNombreActividad(nombre_act);
    nueva.setDescripcion(descripcion);
    nueva.setFechaInicio(fechaInicio);
    nueva.setFechaFinal(fechaFinal);
}


#endif