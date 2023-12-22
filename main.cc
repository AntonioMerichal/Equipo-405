#include <iostream>
#include <string>
#include "gestor_usuarios.h"
#include "funciones.h"
#include "actividad.h"
#include "gestor_actividad.h"
#include <ctime>
#include <iomanip>
#include "gestor_inscripcion.h"
using namespace std;
#define ANSI_COLOR_GREEN "\033[32m"
#define ANSI_COLOR_RESET "\033[0m"

#define RESET_COLOR "\033[0m"
#define BRIGHT_YELLOW "\033[1;33m"
int main(int argc, char **argv)
{
    if (argc != 4)
    {
        cout << "Error al ejecutar el programa, debe introducir obligatoriamente el nombre de las bases de datos." << endl;
        cout << "Por ejemplo: <./a.out usuarios.txt actividades.txt inscripciones.txt>" << endl;
        exit(EXIT_FAILURE);
    }

    string nombreFicheroUsuarios(argv[1]);
    string nombreFicheroActividades(argv[2]);
    string nombreFicheroInscritos(argv[3]);
    int idCurso;

    GestorUsuario usuarios(nombreFicheroUsuarios);

    GestorActividad actividad(nombreFicheroActividades);

    inscripciones_actividad inscripcion(nombreFicheroInscritos);


    int opcion;
    Usuario nuevo;
    string usuario, pass;
    string rol_usuario_logueado = "";
    Actividad nueva;
    int id;
   std::string fechaInicio;
   std::string fechaFin;
    Inscripcion Inueva;
    // Obtener la fecha y hora actual
    std::time_t t = std::time(nullptr);
    
    // Convertir la fecha y hora actual a una estructura tm
    std::tm* tm_info = std::localtime(&t);

    // Crear un string con el formato deseado (%Y-%m-%d)
    char buffer[80];
    std::strftime(buffer, sizeof(buffer), "%Y-%m-%d", tm_info);

    // Imprimir la fecha actual con el formato especificado
    std::string fechaActual(buffer);
    std::cout << "Fecha actual: " << fechaActual << std::endl;

    do
    {
        opcion = menu();

        switch (opcion)
        {
        case 0:
            cout << "Saliendo..." << endl;
            break;

        case 1:
            cout << "Usuario: ";
            cin >> usuario;
            cout << "Contraseña: ";
            cin >> pass;
            if (usuarios.login(usuario, pass) == true)
            {
                cout << "Login realizado con éxito!" << endl;
                rol_usuario_logueado = usuarios.getRolUsuario(usuario);
                opcion = 0;
            }
            else
            {
                cout << "Error login!" << endl;
                cout << "\n" << endl;
            }
            break;

        case 2:
            pedirDatosUsuario(nuevo);
            if (usuarios.altaUsuario(nuevo) == true)
            {
                cout << "Te has registrado con éxito!!" << endl;
            }
            else
            {
                cout << "Error al registrarte, el nombre de usuario ya existe." << endl;
            }
            break;

        case 3:
            actividad.mostrarActividadesActuales(fechaActual);
            break;
        

        default:
            cout << "Opción incorrecta, introduce una opción válida!" << endl;
            break;
        }

    } while (opcion != 0);

    if (rol_usuario_logueado == "ORGANIZADOR")
    {
        do
        {
            opcion = menuOrganizador();

            switch (opcion)
            {
            case 0:
                cout << "Saliendo..." << endl;
                break;

            case 1:
                pedirDatosAct(nueva);
                if (actividad.altaActividad(nueva) == true)
                {
                    cout << "Has creado la actividad con exito!!" << endl;
                }
                break;

            case 2:
                cout <<"Introduce el rango de fechas:"<<endl;
                cout <<"Fecha inicio: ";
                cin >> fechaInicio;
                cout <<"Fecha fin: ";
                cin >> fechaFin;
                actividad.mostrarActividadesEntreFechas(fechaInicio,fechaFin);
                break;
            case 3:
                cout<<"Introduce que actividad quieres modificar"<<endl;
                cin>>id;
                actividad.modificarActividad(id);
                break;
            case 4:
                cout<<"Introduce que actividad quieres borrar"<<endl;
                cin>>id;
                actividad.borrarActividad(id);
                break;
            }

        } while (opcion != 0);
    }

    else if(rol_usuario_logueado == "USUARIO")
    {
        cout << "\n" ;
        cout << ANSI_COLOR_GREEN << "================= BIENVENIDO A IDEED : " << usuario << "================= " << ANSI_COLOR_RESET << endl;
        cout << "\n";
        cout << "ACTIVIDADES DISPONIBLES EN LA FECHA ACTUAL: " << endl;
        actividad.mostrarActividadesActuales(fechaActual);
        do
        {
             opcion = menuUsuario();

            switch (opcion)
            {
                case 1:
                cout << "Introduce el ID de la actividad a la que desea inscribirse: ";
                cin >> idCurso;
                inscripcion.nuevaInscripcion(Inscripcion(usuario,idCurso));
                fechaInicio = actividad.obtenerFechaInicio(idCurso);
                inscripcion.modificarFechaInicioCurso(usuario,idCurso,fechaInicio);
                cout << "te has inscrito" << endl;
                break;
            case 2:
            cout << "Te vas a dar de baja de la actividad. Introduce tu usuario y el id de la actividad" << endl;
            cin >> usuario;
            cin>> id;
               if (inscripcion.darDeBajaUsuario(usuario,id)==true)
               {
                    cout<< "Te has dado de baja con éxito de la actividad"<<endl;
               }
               else
               {
                    cout<< "Has introducido valores incorrectos" << endl;
               }
                break;
            }

        } while (opcion != 0);
    }
    else if(rol_usuario_logueado == "DIRECTOR_ACADEMICO")
    {
        cout << "\n" ;
        cout << BRIGHT_YELLOW << "================= BIENVENIDO A IDEED : " << usuario << "================= " << RESET_COLOR << endl;
        cout << "\n";
        do
        {
                    opcion = menuDirector();

                    switch (opcion)
                    {
                    case 0:
                        cout << "Saliendo..." << endl;
                        break;

                    case 1:
                        cout << "Introduce el ID de la actividad a la que desea inscribirse: ";
                        cin >> idCurso;
                        inscripcion.nuevaInscripcion(Inscripcion(usuario,idCurso));
                        fechaInicio = actividad.obtenerFechaInicio(idCurso);
                        inscripcion.modificarFechaInicioCurso(usuario,idCurso,fechaInicio);
                        cout << "te has inscrito" << endl;               
                        break;

                    case 2:
                        cout << "Vas a dar de baja al usuario que introduzcas. Introduce su usuario, seguido de 'enter' y a continuación el id de la actividad, seguido de 'enter'" << endl;
                            cin >> usuario;
                            cin>> id;
                        if (inscripcion.darDeBajaUsuario(usuario,id)==true)
                        {
                            cout<< "Te has dado de baja con éxito de la actividad"<<endl;
                        }
                        else
                        {
                            cout<< "Has introducido valores incorrectos" << endl;
                        }               
                        break;
                    case 3:
                        cout<<"La lista de actividades que se van a realizar es la siguiente: "<<endl;
                        actividad.mostrarActividades();                
                        break;
                    case 4:
                        cout<<"La lista de inscritos es la siguiente: "<<endl;
                        inscripcion.mostrarInscripciones();              
                        break;
                    }
            } while (opcion != 0);

    }

}