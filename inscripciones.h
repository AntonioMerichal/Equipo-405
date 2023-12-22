#ifndef INSCRIPCIONES_H
#define INSCRIPCIONES_H

#include <iostream>
#include <string>
#include "actividad.h"
#include "usuario.h"
#include "enum_estado_inscripcion.h"
#include <ctime>
#include <iomanip>
#include <sstream>
#pragma once

using namespace std;

class Inscripcion
{
private:
    string usuario_;
    int id_;
    string fechaInscripcion_;
    string fechaInicioCurso_;
    estado_inscripcion estado_;
    

public:
    Inscripcion() {}
    Inscripcion(string usuario, int id)
    {
        usuario_ = usuario;
        id_ = id;
        estado_ = estado_inscripcion::PREINSCRITO;

        std::time_t t = std::time(nullptr);
        std::tm *tm_info = std::localtime(&t);
        char buffer[80];
        std::strftime(buffer, sizeof(buffer), "%Y-%m-%d", tm_info);
        std::string fechaInscripcion_(buffer);
    }
    string getUsuario() const
    {
        return usuario_;
    }

    int getId() const
    {
        return id_;
    }

    string getFechaInscripcion() const
    {
        return fechaInscripcion_;
    }
    string getFechaInicioCurso() const
    {
        return fechaInicioCurso_;
    }
   
    estado_inscripcion getEstado() const
    {
        return estado_;
    }

    // Métodos setter
    void setUsuario(const string &usuario)
    {
        usuario_ = usuario;
    }

    void setId(const int &id)
    {
        id_ = id;
    }

    void setFechaInscripcion(const string &fechaInscripcion)
    {
        fechaInscripcion_ = fechaInscripcion;
    }

    void setFechaInicioCurso(const string &fechaInicioCurso)
    {
        fechaInicioCurso_ = fechaInicioCurso;
    }

    // string getEstadoRol() const
    // {
    //     switch (estado_)
    //     {
    //     case estado_inscripcion::INSCRITO:
    //         return "INSCRITO";
    //         break;
    //     case estado_inscripcion::PREINSCRITO:
    //         return "PREINSCRITO";
        
    //     }
    // }
    void setEstado(const estado_inscripcion &estado)
    {
        estado_ = estado;
    }
};

#endif