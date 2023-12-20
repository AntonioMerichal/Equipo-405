#ifndef USUARIO_H
#define USUARIO_H

#include <string>
#include "rol_enum.h"
#include "estado_usuario_enum.h"

using namespace std;

class Usuario
{
private:
    string usuario_;
    string pass_;
    string nombre_;
    rol_enum rol_;
    estado_usuario_enum estado_;

public:
    Usuario() {}

    Usuario(string u, string pass, string n, rol_enum rol)
    {
        usuario_ = u;
        pass_ = pass;
        nombre_ = n;
        rol_ = rol;
        estado_ = estado_usuario_enum::VISITANTE;
    }

    std::string getUsuario() const
    {
        return usuario_;
    }

    std::string getNombre() const
    {
        return nombre_;
    }

    rol_enum getRol() const
    {
        return rol_;
    }

    estado_usuario_enum getEstado() const
    {
        return estado_;
    }

    string getRolCadena() const
    {
        switch (rol_)
        {
        case rol_enum::USUARIO:
            return "USUARIO";
            break;

        case rol_enum::DIRECTOR_ACADEMICO:
            return "DIRECTOR_ACADEMICO";
            break;

        default:
            return "ORGANIZADOR";
        }
    }

    void setUsuario(const std::string &u)
    {
        usuario_ = u;
    }

    void setNombre(const std::string &n)
    {
        nombre_ = n;
    }

    void setRol(rol_enum rol)
    {
        rol_ = rol;
    }

    void setEstado(estado_usuario_enum estado)
    {
        estado_ = estado;
    }

    string getDatos() const
    {
        return "Usuario: " + usuario_ + ", Nombre: " + nombre_;
    }

    bool comprobarPass(string pass)
    {
        return pass == pass_;
    }

    void setPass(string pass)
    {
        pass_ = pass;
    }

    string getPass()const
    {
        return pass_;
    }
};

#endif