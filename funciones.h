#ifndef FUNCIONES_H
#define FUNCIONES_H

#include <iostream>
using namespace std;
#include "usuario.h"
#include "actividad.h"
#include "gestor_actividad.h"
#include "gestor_inscripcion.h"


#define RED_TEXT "\033[1;31m"
#define RESET_COLOR "\033[0m"

#define RESET   "\033[0m"
#define BLUE    "\033[34m"

#define ANSI_COLOR_GREEN "\033[32m"
#define ANSI_COLOR_RESET "\033[0m"

#define RESET_COLOR "\033[0m"
#define BRIGHT_YELLOW "\033[1;33m"

int menu()
{
    
    cout << RED_TEXT << "************************************" << endl;
    cout << "            MENÚ PRINCIPAL" << endl;
    cout << "************************************" << RESET_COLOR << endl;
    cout << "1) LOGIN" << endl;
    cout << "2) REGISTRARME" << endl;
    cout << "3) MOSTRAR ACTIVIDAD" << endl;
    cout << "0) SALIR" << endl;
    cout << RED_TEXT << "************************************" << RESET_COLOR << endl;
    cout << "Introduce el número de la opción deseada: ";
    int opcion;
    cin >> opcion;
    return opcion;
}

int menuOrganizador()
{
    cout << BLUE << "************************************" << endl;
    cout << "            MENÚ ORGANIZADOR" << endl;
    cout << "************************************" << RESET_COLOR << endl;
    cout << "1) CREAR ACTIVIDAD" << endl;
    cout << "2) MOSTRAR ACTIVIDADES" << endl;
    cout << "3) MODIFICIAR ACTIVIDADES" << endl;
    cout << "4) BORRAR ACTIVIDADES" << endl;
    cout << "0) SALIR" << endl;
    cout << BLUE << "************************************" << RESET_COLOR << endl;
    cout << "Introduce el número de la opción deseada: ";
    int opcion;
    cin >> opcion;
    return opcion;
}
int menuUsuario()
{
    cout <<ANSI_COLOR_GREEN<<"************************************" << endl;
    cout << "         MENÚ USUARIO" << endl;
    cout << "************************************" << RESET_COLOR<<endl;
    cout << "1) AÑADIRSE A LA ACTIVIDAD" << endl;
    cout << "2) DARSE DE BAJA DE LA ACTIVIDAD" << endl;
    cout << "0) SALIR" << endl;
    cout << ANSI_COLOR_GREEN << "************************************" << ANSI_COLOR_RESET << endl;
    cout << "Introduce el número de la opción deseada: ";
    int opcion;
    cin >> opcion;
    return opcion;
}
int menuDirector()
{
    cout << BRIGHT_YELLOW <<"************************************" << endl;
    cout << "     MENÚ DIRECTOR ACADÉMICO" << endl;
    cout << "************************************" << RESET_COLOR << endl;
    cout << "1) AÑADIRSE A LA ACTIVIDAD" << endl;
    cout << "2) BORRAR USUARIO DE LA ACTIVIDAD" << endl;
    cout << "3) MOSTRAR LISTA TOTAL DE ACTIVIDADES" << endl;
    cout << "4) MOSTRAR LISTA DE INSCRITOS" << endl;
    cout << "0) SALIR" << endl;
    cout << BRIGHT_YELLOW << "************************************" << RESET_COLOR << endl;
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