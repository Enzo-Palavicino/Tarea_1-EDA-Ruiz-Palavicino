#pragma once
#include "cluster.hpp"
#include "puntos.hpp"
#include "consultas.hpp"

class SimSearch{
    protected:
        std::vector<punto> puntos;
        std::vector<Consulta> consultas;
        Cluster* clusters;
        
        // Variables para almacenar los resultados
        mutable size_t comparaciones_count; 
        mutable long long time_without_sort;
        mutable long long time_with_sort;

    public:
        SimSearch(std::vector<punto> puntos1, std::vector<Consulta> consultas1, Cluster * clusters1);
        std::vector<size_t> search_with_clusters(Consulta, int m);  
        std::vector<size_t> search_without(Consulta, int m);
        
        size_t get_comparaciones() const;
        void reset_comparaciones();       
        long long get_time_without_sort() const;
        long long get_time_with_sort() const;

        Cluster * pasar_cluster();
        std::vector<punto> pasar_puntos();
        Consulta pasar_consulta(int i);
};
//punto seguro