#ifndef ACTIVIDAD_H
#define ACTIVIDAD_H

#include <iostream>
#include <string>
using namespace std;

class Actividad
{
    private:
        int id_;
        string nombre_act_;
        string descripcion_;
        string fechaInicio_;
        string fechaFinal_;
    public:
        Actividad(){}
        Actividad (int id, string nombre_act, string descripcion, 
        string fechaInicio,
        string fechaFinal)
        {
            id_=id;
            nombre_act_=nombre_act;
            descripcion_=descripcion;
            fechaInicio_=fechaInicio;
            fechaFinal_=fechaFinal;
        }
int getId() const
    {
        return id_;
    }
    void setId(int id)
    {
        id_ = id;
    }

string getNombreActividad() const
    {
        return nombre_act_;
    }

    void setNombreActividad(const std::string &nombre_act)
    {
        nombre_act_ = nombre_act;
    }

string getDescripcion() const
    {
        return descripcion_;
    }

    void setDescripcion(const std::string &descripcion)
    {
        descripcion_ = descripcion;
    }
    string getFechaInicio() const
    {
        return fechaInicio_;
    }

    // Setter para la fecha
    void setFechaInicio(const std::string& fechaInicio)
    {
        fechaInicio_ = fechaInicio;
    }
    string getFechaFinal() const
    {
        return fechaFinal_;
    }

    // Setter para la fecha
    void setFechaFinal(const std::string& fechaFinal)
    {
        fechaFinal_ = fechaFinal;
    }

    string getDatosAct() const
    {
        return "Id: " + to_string(id_) + " Nombre: " + nombre_act_;
    }
};
#endif