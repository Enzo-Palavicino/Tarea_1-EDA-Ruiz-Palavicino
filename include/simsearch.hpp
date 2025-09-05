#pragma once
#include "cluster.hpp"
#include "puntos.hpp"
#include "consultas.hpp"

class SimSearch{
    protected: // es mejor que sea protected para que no hayan problemas

        std::vector<punto> puntos; // vectores de todos los objetos
        std::vector<Consulta> consultas;
        Cluster*  clusters; // esto es para que sea constante el cluster

    public:

        SimSearch(std::vector<punto> puntos1, std::vector<Consulta> consultas1, Cluster * clusters1);
        std::vector<std::vector<size_t>> search_with_clusters(Consulta,int m);  // estas funciones las cambie para
        std::vector<std::vector<float>> search_without(Consulta, int m);        // que solo interactue con objetos

        Cluster * pasar_cluster();
        std::vector<punto> pasar_puntos();
        Consulta pasar_consulta(int i);

};

