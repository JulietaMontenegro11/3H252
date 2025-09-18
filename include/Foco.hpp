#pragma once
#include <EstadoFoco.hpp>

class Foco
{
private:
    EstadoFoco estadoActual;
public:
    Foco() {}
    ~Foco() {}
    void Encender () { }
    void Apagar () {}
    EstadoFoco MostrarEstado(){}
};

