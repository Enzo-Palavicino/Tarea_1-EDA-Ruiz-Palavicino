#pragma once

#include <vector>
#include<iostream>
#include<string>
#include<fstream>
#include<sstream>
#include<vector>
#include "puntos.hpp"

class Consulta{
    protected:
        int nombre;
        std::vector<float> posicion; // [0] ==> x, [1] ==> y
        std::vector<punto> puntos_mas_cercanos; // estos se definen por el parametro m

    public:
        Consulta(int, std::vector<float>);
        std::vector<float> dar_posicion();
        std::vector<punto> dar_puntos();
        void modificar_puntos(std::vector<punto> );
        void mostrar_datos();
};