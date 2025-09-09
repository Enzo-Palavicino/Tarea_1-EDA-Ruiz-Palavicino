#pragma once
#include "cluster.hpp"
#include "puntos.hpp"
#include "consultas.hpp"
#include <vector>

class SimSearch{
    protected:
        std::vector<punto> puntos;
        std::vector<Consulta> consultas;
        Cluster* clusters;
        
        // Variables para almacenar los resultados de la última búsqueda
        mutable size_t comparaciones_count; 
        mutable long long time_without_sort;
        mutable long long time_with_sort;

    public:
        SimSearch(std::vector<punto> puntos1, std::vector<Consulta> consultas1, Cluster * clusters1);
        std::vector<size_t> search_with_clusters(Consulta con, int m, float& error);  
        std::vector<size_t> search_without(Consulta con, int m);
        
        size_t get_comparaciones() const;
        void reset_comparaciones();       
        long long get_time_without_sort() const;
        long long get_time_with_sort() const;

        Cluster* pasar_cluster();
        std::vector<punto> pasar_puntos();
        Consulta pasar_consulta(int i);
        
        // Función auxiliar para calcular error
        float calcular_error(const std::vector<size_t>& resultado_sin_cluster, 
                           const std::vector<size_t>& resultado_con_cluster,
                           Consulta con);
};

//punto seguro