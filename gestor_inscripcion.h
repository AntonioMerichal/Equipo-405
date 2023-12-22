#ifndef INSCRIPCIONES_ACTIVIDAD_H
#define INSCRIPCIONES_ACTIVIDAD_H

#include <iostream>
#include <string>
#include <list>
#include "inscripciones.h"
#include "enum_estado_inscripcion.h"
#include <fstream>
#include <iomanip>
#include <stdexcept>
#include <cctype>
#include "usuario.h"
using namespace std;

class inscripciones_actividad
{
private:
    string nombreFichero_;
    list<Inscripcion> lista_inscritos_;

public:
    inscripciones_actividad() {}
    inscripciones_actividad(string nombreFichero)
    {
       nombreFichero_ = nombreFichero;
        ifstream fich(nombreFichero);
        if (fich.is_open())
        {
            string datoLeido;
            Inscripcion aux;
            while (getline(fich, datoLeido, ','))
            {
                aux.setUsuario(datoLeido);
                getline(fich, datoLeido, ',');
                
                    if (isdigit(datoLeido[0])) {
                        aux.setId(std::stoi(datoLeido));
                    } else {
                        cerr << "Error al convertir a entero: No es un número válido." << endl;
                        // Manejar la situación de error según sea necesario
                    }

                getline(fich, datoLeido, ',');

                aux.setFechaInscripcion(datoLeido);

                getline(fich, datoLeido, ',');
                
                aux.setFechaInicioCurso(datoLeido);
                getline(fich, datoLeido, '\n');
                
               if (datoLeido == "PREINSCRITO")
                {
                    aux.setEstado(estado_inscripcion::PREINSCRITO);
                }
                else if (datoLeido == "INSCRITO")
                {
                    aux.setEstado(estado_inscripcion::INSCRITO);
                }

                lista_inscritos_.push_back(aux);
            }
            fich.close();
        }
        else
        {
            cout << "Error al conectar con la base de datos " << nombreFichero << endl;
            exit(EXIT_FAILURE);
        } 
    }
    void modificarFechaInicioCurso(const std::string &usuario, int idCurso, const std::string &nuevaFechaInicio)
    {
        for (auto &inscripcion : lista_inscritos_)
        {
            if (inscripcion.getUsuario() == usuario && inscripcion.getId() == idCurso)
            {
                std::cout << "Modificando fecha de inicio del curso para el usuario " << usuario << " en el curso con ID " << idCurso << std::endl;

                // Verifica si la fecha de inicio del curso puede ser modificada (según tu lógica de negocio)
                // ...

                // Modifica la fecha de inicio del curso
                inscripcion.setFechaInicioCurso(nuevaFechaInicio);

                std::cout << "Fecha de inicio del curso modificada con éxito." << std::endl;
                return;
            }
        }

        std::cout << "No se encontró ninguna inscripción para el usuario " << usuario << " en el curso con ID " << idCurso << std::endl;
    }
    std::list<Inscripcion> getListaInscritos() const
    {
        return lista_inscritos_;
    }

    void setListaInscritos(const std::list<Inscripcion> &lista_inscritos)
    {
        lista_inscritos_ = lista_inscritos;
    }

    void nuevaInscripcion(const Inscripcion &inscripcion)
    {
        lista_inscritos_.push_back(inscripcion);
    }

    bool fechaInscripcionEnRango(int idInscripcion, const std::string &fechaInicio, const std::string &fechaFinal)
{
    for (const auto &inscripcion : lista_inscritos_)
    {
        if (inscripcion.getId() == idInscripcion)
        {
            std::string fechaInscripcion = inscripcion.getFechaInscripcion();
            return (fechaInscripcion >= fechaInicio && fechaInscripcion <= fechaFinal);
        }
    }

    // If no matching idInscripcion is found, return a default value.
    return false; // Or true, depending on your desired default behavior.
}
void mostrarInscripciones() const
    {
        std::cout << "Inscripciones en la actividad:\n";

        for (auto it = lista_inscritos_.begin(); it != lista_inscritos_.end(); ++it)
        {
            string rol;
                        switch (it->getEstado()) {
                            case estado_inscripcion::INSCRITO:
                                rol = "INSCRITO";
                                break;
                            case estado_inscripcion::PREINSCRITO:
                                rol = "PREINSCRITO";
                                break;
                        }
            std::cout << "Usuario: " << it->getUsuario()
                      << ", ID: " << it->getId()
                      << ", Fecha de Inscripción: " << it->getFechaInscripcion()
                      << ", Fecha de Inicio del Curso: " << it->getFechaInicioCurso()
                      << ", Estado: " << rol << std::endl;
        }
    }
~inscripciones_actividad() {
        std::cout << "Realizando backup de inscritos..." << std::endl;
        std::cout << "Nombre del fichero: " << nombreFichero_ << std::endl;
        ofstream fich(nombreFichero_);
        // Iterar sobre la lista de inscritos y escribir en el archivo
            
               for (auto it = lista_inscritos_.begin(); it != lista_inscritos_.end(); ++it) 
               {
                        string rol;
                        switch (it->getEstado()) {
                            case estado_inscripcion::INSCRITO:
                                rol = "INSCRITO";
                                break;
                            case estado_inscripcion::PREINSCRITO:
                                rol = "PREINSCRITO";
                                break;
                        }
                        // Obtengo la fecha actual // fecha matriculacion
                    std::time_t t = std::time(nullptr);
                    std::tm *tm_info = std::localtime(&t);
                    char buffer[80];
                    std::strftime(buffer, sizeof(buffer), "%Y-%m-%d", tm_info);
                    std::string fechaActual(buffer);

                    //obtener el usuario
                   
                fich << it->getUsuario() << "," << it->getId() << "," << fechaActual << ","
                << it->getFechaInicioCurso() << "," << rol << "\n";
               }
                
        
    fich.close();
}
       

    bool darDeBajaUsuario(const std::string &nombreUsuario, const int idCurso)
    {
        for (auto it = lista_inscritos_.begin(); it != lista_inscritos_.end(); ++it)
        {
            if (it->getUsuario() == nombreUsuario && it->getId() == idCurso)
            {
                if (it->getEstado() == estado_inscripcion::PREINSCRITO)
                {
                    lista_inscritos_.erase(it);
                    return true;
                }
                else if (it->getEstado() == estado_inscripcion::INSCRITO)
                {
                    // Obtengo la fecha de inicio del curso
                    string fechaInicioCurso = it->getFechaInicioCurso();
                    std::tm tmFechaInicio2 = {};
                    std::istringstream ssFechaInicio2(fechaInicioCurso);
                    ssFechaInicio2 >> std::get_time(&tmFechaInicio2, "%Y-%m-%d");

                    // Obtengo la fecha actual
                    std::time_t t = std::time(nullptr);
                    std::tm *tm_info = std::localtime(&t);
                    char buffer[80];
                    std::strftime(buffer, sizeof(buffer), "%Y-%m-%d", tm_info);
                    std::string fechaActual(buffer);

                    // Debe haber al menos 24 horas de diferencia
                    if (fechaActual < ssFechaInicio2.str())
                    {
                        lista_inscritos_.erase(it);
                        return true;
                    }
                }
            }
        }
        return false;
    }
};

#endif
