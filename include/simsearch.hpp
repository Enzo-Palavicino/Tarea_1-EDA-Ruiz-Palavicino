#pragma once
#include "cluster.hpp"
#include "puntos.hpp"
#include "consultas.hpp"

class SimSearch{
    protected: // es mejor que sea protected para que no hayan problemas

        std::vector<punto> puntos; // vectores de todos los objetos
        std::vector<Consulta> consultas;
        Cluster* clusters; // esto es para que sea constante el cluster
        mutable size_t comparaciones_count; // contador de comparaciones

    public:

        SimSearch(std::vector<punto> puntos1, std::vector<Consulta> consultas1, Cluster * clusters1);
        std::vector<size_t> search_with_clusters(Consulta,int m);  
        std::vector<size_t> search_without(Consulta, int m);
        size_t get_comparaciones() const;
        void reset_comparaciones();       

        Cluster * pasar_cluster();
        std::vector<punto> pasar_puntos();
        Consulta pasar_consulta(int i);

};
