#pragma once

#include <vector>
#include<iostream>
#include<string>
#include<fstream>
#include<sstream>
#include<vector>


class punto{
    protected:

        std::vector<float> posicion; // [0] --> x, [1] --> y
        int n_cluster;
        int nombre;
        float dis_cent; // la voy a ocupar como la distancia con la consulta

    public:

        punto(std::vector<float> posicion, int n_cluster, int nombre);
        int mostrar_nombre();
        std::vector<float> mostrar_posicion();
        void imprimir_posicion();
        float mostrar_distancia() const;
        int cluster_actual();
        void editar_distancia(float n_dis);
        void mostrar_datos();

};