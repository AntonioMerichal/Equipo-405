#ifndef GESTOR_USUARIOS_H
#define GESTOR_USUARIOS_H

#include "usuario.h"
#include <list>
#include <fstream>
#include <iostream>
using namespace std;

class GestorUsuario
{
private:
    string nombreFichero_;
    
    list<Usuario> lista_usuarios_;

public:
    GestorUsuario(string nombreFichero)
    {
        nombreFichero_ = nombreFichero;
        ifstream fich(nombreFichero);
        if (fich.is_open())
        {
            string datoLeido;
            Usuario aux;
            while (getline(fich, datoLeido, ','))
            {
                aux.setUsuario(datoLeido);
                getline(fich, datoLeido, ',');
                aux.setPass(datoLeido);
                getline(fich, datoLeido, ',');
                aux.setNombre(datoLeido);
                getline(fich, datoLeido, '\n');
                if (datoLeido == "USUARIO")
                {
                    aux.setRol(rol_enum::USUARIO);
                }
                else if (datoLeido == "DIRECTOR_ACADEMICO")
                {
                    aux.setRol(rol_enum::DIRECTOR_ACADEMICO);
                }
                else if (datoLeido == "ORGANIZADOR")
                {
                    aux.setRol(rol_enum::ORGANIZADOR);
                }
                aux.setEstado(estado_usuario_enum::VISITANTE);

                altaUsuario(aux);
            }
            fich.close();
        }
        else
        {
            cout << "Error al conectar con la base de datos " << nombreFichero << endl;
            exit(EXIT_FAILURE);
        }
    }

    ~GestorUsuario()
    {
        cout << "Realizando backup de usuarios..." << endl;
        ofstream fich(nombreFichero_);
        if (fich.is_open())
        {
            for (auto it = lista_usuarios_.begin(); it != lista_usuarios_.end(); it++)
            {
                fich << it->getUsuario() << "," << it->getPass() 
                    << "," << it->getNombre() << "," << it->getRolCadena() << endl;
            }
            fich.close();
        }
    }

    bool login(string usuario, string pass)
    {
        for (auto it = lista_usuarios_.begin(); it != lista_usuarios_.end(); it++)
        {
            if (it->getUsuario() == usuario and it->comprobarPass(pass))
            {
                it->setEstado(estado_usuario_enum::LOGUEADO);
                return true;
            }
        }
        return false;
    }

    string getRolUsuario(string usuario)
    {
        for (auto it = lista_usuarios_.begin(); it != lista_usuarios_.end(); it++)
        {
            if (it->getUsuario() == usuario)
            {
                return it->getRolCadena();
            }
        }
        return "";
    }

    bool existeUsuario(string usuario)
    {
        for (auto it = lista_usuarios_.begin(); it != lista_usuarios_.end(); it++)
        {
            if (it->getUsuario() == usuario)
            {
                return true;
            }
        }
        return false;
    }

    bool altaUsuario(Usuario usuarioNuevo)
    {
        if (existeUsuario(usuarioNuevo.getUsuario()) == true)
        {
            return false;
        }
        lista_usuarios_.push_back(usuarioNuevo);
        return true;
    }

    string getInfoUsuarios(rol_enum rol)
    {
        string cadena = "";
        for (auto it = lista_usuarios_.begin(); it != lista_usuarios_.end(); it++)
        {
            if (it->getRol() == rol)
            {
                cadena += it->getDatos() + "\n";
            }
        }
        return cadena;
    }
};

#endif