#ifndef GESTOR_ACTIVIDADES_H
#define GESTOR_ACTIVIDADES_H

#include <string>
#include <iostream>
#include "actividad.h"
#include <list>
#include <fstream>
#include <ctime>
#include <sstream>
#include <iomanip>

class GestorActividad
{
private:
    string nombreFichero_;
    list<Actividad> lista_actividad_;

public:
    GestorActividad(string nombreFichero)
    {
        nombreFichero_ = nombreFichero;
        ifstream fich(nombreFichero);
        if (fich.is_open())
        {
            string datoLeido;
            Actividad aux;
            while (getline(fich, datoLeido, ','))
            {
                aux.setId(stoi(datoLeido));
                getline(fich, datoLeido, ',');
                aux.setNombreActividad(datoLeido);
                getline(fich, datoLeido, ',');
                aux.setDescripcion(datoLeido);
                getline(fich, datoLeido, ',');
                aux.setFechaInicio(datoLeido);
                getline(fich, datoLeido, '\n');
                aux.setFechaFinal(datoLeido);
                altaActividad(aux);
            }
            fich.close();
        }
        else
        {
            cout << "Error al conectar con la base de datos " << nombreFichero << endl;
            exit(EXIT_FAILURE);
        }
    }
            std::string obtenerFechaInicio(int id)
                {
                    for (const auto &actividad : lista_actividad_)
                    {
                        if (actividad.getId() == id)
                        {
                            return actividad.getFechaInicio();
                        }
                    }

                    // Si no se encuentra la actividad con el ID proporcionado, puedes lanzar una excepción o devolver una cadena vacía según tus necesidades.
                    std::cerr << "No se encontró ninguna actividad con el ID proporcionado." << std::endl;
                    // Puedes lanzar una excepción aquí o devolver una cadena vacía según tus necesidades
                    // throw std::runtime_error("No se encontró ninguna actividad con el ID proporcionado.");
                    return "";
                }
    std::list<Actividad> getListaActividades() const
    {
        return lista_actividad_;
    }
    ~GestorActividad()
    {
        cout << "Realizando backup de actividades..." << endl;
        ofstream fich(nombreFichero_);
        if (fich.is_open() == false)
        {
            cout << "Error de conexión con la base de datos." << endl;
            exit(EXIT_FAILURE);
        }
        for (Actividad a : lista_actividad_)
        {
            fich << a.getId() << "," << a.getNombreActividad() << "," << a.getDescripcion() << "," << a.getFechaInicio() << "," << a.getFechaFinal() << endl;
        }
        fich.close();
    }
    void mostrarActividades()
        {

        for (const auto &actividad : lista_actividad_)
        {
            // Convertir las cadenas a estructuras tm para cada fecha y poder compararlas
                std::cout << "ID: " << actividad.getId() << ", NOMBRE: " << actividad.getNombreActividad()
                          << ", DESCRIPCION: " << actividad.getDescripcion()
                          << ", FECHA INICIO: " << actividad.getFechaInicio()
                          << ", FECHA FINAL: " << actividad.getFechaFinal() << std::endl;
            }
        }
        
    bool existeActividad(int id)
    {
        for (auto it = lista_actividad_.begin(); it != lista_actividad_.end(); it++)
        {
            if (it->getId() == id)
            {
                return true;
            }
        }
        return false;
    }

    bool altaActividad(Actividad actividadNueva)
    {
        if (existeActividad(actividadNueva.getId()) == true)
        {
            return false;
        }
        lista_actividad_.push_back(actividadNueva);
        return true;
    }

    void mostrarActividadesEntreFechas(const std::string &fechaInicio, const std::string &fechaFin)
    {
        std::tm tmFechaInicio1 = {};
        std::tm tmFechaFinal1 = {};
        std::istringstream ssFechaInicio1(fechaInicio);
        std::istringstream ssFechaFinal1(fechaFin);
        ssFechaInicio1 >> get_time(&tmFechaInicio1, "%Y-%m-%d");
        ssFechaFinal1 >> get_time(&tmFechaFinal1, "%Y-%m-%d");

        for (const auto &actividad : lista_actividad_)
        {
            // Convertir las cadenas a estructuras tm para cada fecha y poder compararlas
            std::tm tmFechaInicio2 = {};
            std::tm tmFechaFinal2 = {};
            std::istringstream ssFechaInicio2(actividad.getFechaInicio());
            std::istringstream ssFechaFinal2(actividad.getFechaFinal());
            ssFechaInicio2 >> get_time(&tmFechaInicio2, "%Y-%m-%d");
            ssFechaFinal2 >> get_time(&tmFechaFinal2, "%Y-%m-%d");

            if (mktime(&tmFechaInicio2) >= mktime(&tmFechaInicio1) &&
                mktime(&tmFechaFinal2) <= mktime(&tmFechaFinal1))
            {
                std::cout << "ID: " << actividad.getId() << ", Nombre: " << actividad.getNombreActividad()
                          << ", Descripción: " << actividad.getDescripcion()
                          << ", Fecha Inicio: " << actividad.getFechaInicio()
                          << ", Fecha Final: " << actividad.getFechaFinal() << std::endl;
            }
        }
    }

    void mostrarActividadesActuales(const std::string &fechaInicio)
    {
        std::tm tmFechaInicio1 = {};
        std::istringstream ssFechaInicio1(fechaInicio);
        ssFechaInicio1 >> get_time(&tmFechaInicio1, "%Y-%m-%d");

        for (const auto &actividad : lista_actividad_)
        {
            // Convertir las cadenas a estructuras tm para cada fecha y poder compararlas
            std::tm tmFechaInicio2 = {};
            std::istringstream ssFechaInicio2(actividad.getFechaInicio());
            ssFechaInicio2 >> get_time(&tmFechaInicio2, "%Y-%m-%d");

            if (mktime(&tmFechaInicio2) >= mktime(&tmFechaInicio1))
            {
                std::cout << "ID: " << actividad.getId() << ", Nombre: " << actividad.getNombreActividad()
                          << ", Descripción: " << actividad.getDescripcion()
                          << ", Fecha Inicio: " << actividad.getFechaInicio()
                          << ", Fecha Final: " << actividad.getFechaFinal() << std::endl;
            }
        }
    }

    Actividad elegirActividad()
    {
        int idElegido;
        std::cout << "Ingrese el ID de la actividad que desea seleccionar: ";
        std::cin >> idElegido;

        for (const auto &actividad : lista_actividad_)
        {
            if (actividad.getId() == idElegido)
            {
                std::cout << "Actividad seleccionada: " << actividad.getNombreActividad() << std::endl;
                return actividad;
            }
        }

        std::cout << "No se encontró ninguna actividad con el ID ingresado." << std::endl;
        // Puedes lanzar una excepción aquí o devolver una actividad "nula" según tus necesidades
        // return Actividad(-1, "", "", "","","");
        return Actividad();
    }
    void modificarActividad(int id)
    {
        for (auto &actividad : lista_actividad_)
        {
            if (actividad.getId() == id)
            {
                std::cout << "Modificando actividad con ID " << id << std::endl;

                // Solicitar al usuario los nuevos datos
                std::string nuevoNombre;
                std::string nuevaDescripcion;
                std::string nuevaFechaInicio;
                std::string nuevaFechaFinal;

                std::cout << "Ingrese el nuevo nombre: ";
                std::cin >> nuevoNombre;
                actividad.setNombreActividad(nuevoNombre);

                std::cout << "Ingrese la nueva descripción: ";
                std::cin.ignore(); // Limpiar el buffer del teclado antes de getline
                std::getline(std::cin, nuevaDescripcion);
                actividad.setDescripcion(nuevaDescripcion);

                std::cout << "Ingrese la nueva fecha: ";
                std::cin >> nuevaFechaInicio;
                actividad.setFechaInicio(nuevaFechaInicio);

                std::cout << "Ingrese la nueva fecha: ";
                std::cin >> nuevaFechaFinal;
                actividad.setFechaFinal(nuevaFechaFinal);

                std::cout << "Actividad modificada con éxito." << std::endl;
                return;
            }
        }

        std::cout << "No se encontró ninguna actividad con el ID ingresado." << std::endl;
    }

    void borrarActividad(int id)
    {
        for (auto it = lista_actividad_.begin(); it != lista_actividad_.end(); it++)
        {
            if (it->getId() == id)
            {

                lista_actividad_.erase(it);
                std::cout << "Actividad con ID " << id << " borrada con éxito." << std::endl;
                return;
            }
        }

        std::cout << "No se encontró ninguna actividad con el ID ingresado." << std::endl;
    }
};

#endif
