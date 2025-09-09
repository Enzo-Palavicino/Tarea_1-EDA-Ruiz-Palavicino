#include "utils.hpp"
#include "matrix.hpp"
#include "cluster.hpp"
#include "puntos.hpp"
#include "consultas.hpp"
#include "simsearch.hpp"
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <algorithm>
#include <cmath>
#include <limits>

SimSearch::SimSearch(std::vector<punto> puntos1, std::vector<Consulta> consultas1, Cluster* clusters1){
    puntos = puntos1;
    consultas = consultas1;
    clusters = clusters1;
    comparaciones_count = 0;
    time_without_sort = 0;
    time_with_sort = 0;
}

Cluster* SimSearch::pasar_cluster(){
    return clusters;
}

std::vector<punto> SimSearch::pasar_puntos(){
    return puntos;
}

Consulta SimSearch::pasar_consulta(int i){
    return consultas[i];
}

size_t SimSearch::get_comparaciones() const { 
    return comparaciones_count; 
}

void SimSearch::reset_comparaciones() { 
    comparaciones_count = 0; 
}

long long SimSearch::get_time_without_sort() const {
    return time_without_sort;
}

long long SimSearch::get_time_with_sort() const {
    return time_with_sort;
}

float SimSearch::calcular_error(const std::vector<size_t>& resultado_sin_cluster, 
                              const std::vector<size_t>& resultado_con_cluster,
                              Consulta con) {
    if (resultado_sin_cluster.size() != resultado_con_cluster.size()) {
        return -1.0f;
    }
    
    float total_error = 0.0f;
    float coor_c[2] = {con.dar_posicion()[0], con.dar_posicion()[1]};
    
    for (size_t i = 0; i < resultado_sin_cluster.size(); i++) {
        float coor_p1[2] = {puntos[resultado_sin_cluster[i]].mostrar_posicion()[0], 
                           puntos[resultado_sin_cluster[i]].mostrar_posicion()[1]};
        float coor_p2[2] = {puntos[resultado_con_cluster[i]].mostrar_posicion()[0], 
                           puntos[resultado_con_cluster[i]].mostrar_posicion()[1]};
        
        float dist_sin = vec_compute_distance(coor_c, coor_p1, 2);
        float dist_con = vec_compute_distance(coor_c, coor_p2, 2);
        total_error += std::abs(dist_sin - dist_con);
    }
    
    return total_error / resultado_sin_cluster.size();
}

std::vector<size_t> SimSearch::search_without(Consulta con, int m){
    reset_comparaciones();
    std::vector<punto> puntos_copia = puntos;

    auto start_search = std::chrono::high_resolution_clock::now();

    float coor_c[2] = {con.dar_posicion()[0], con.dar_posicion()[1]};
    for(size_t i = 0; i < puntos_copia.size(); i++){
        float coor_p[2] = {puntos_copia[i].mostrar_posicion()[0], puntos_copia[i].mostrar_posicion()[1]};
        float distancia = vec_compute_distance(coor_c, coor_p, 2);
        puntos_copia[i].editar_distancia(distancia);
        comparaciones_count++;
    }

    auto stop_search = std::chrono::high_resolution_clock::now();
    time_without_sort = std::chrono::duration_cast<std::chrono::microseconds>(stop_search - start_search).count();
    
    auto start_sort = std::chrono::high_resolution_clock::now();
    std::vector<size_t> indices_ordenados = argsort(puntos_copia);
    auto stop_sort = std::chrono::high_resolution_clock::now();

    long long sort_time = std::chrono::duration_cast<std::chrono::microseconds>(stop_sort - start_sort).count();
    time_with_sort = time_without_sort + sort_time;

    std::vector<size_t> resultado;
    for(int i = 0; i < m && i < indices_ordenados.size(); i++){
        resultado.push_back(indices_ordenados[i]);
    }
    
    return resultado;
} 

std::vector<size_t> SimSearch::search_with_clusters(Consulta con, int m, float& error){
    reset_comparaciones();
    std::vector<size_t> resultado_sin_cluster = search_without(con, m);
    reset_comparaciones();
    auto start_search = std::chrono::high_resolution_clock::now();

    std::vector<std::pair<punto, size_t>> puntos_con_indices;

    std::vector<float> distancias_a_clusters;
    for (size_t i = 0; i < clusters->getK(); i++) {
        const float* centroide = clusters->getCentroid(i);
        float distancia = vec_compute_distance(con.dar_posicion().data(), centroide, 2);
        distancias_a_clusters.push_back(distancia);
        comparaciones_count++;
    }
    std::vector<size_t> clusters_ordenados = argsort(distancias_a_clusters);
    size_t cluster_idx = 0;
    while (puntos_con_indices.size() < m * 2 && cluster_idx < clusters_ordenados.size()) {
        size_t cluster_actual = clusters_ordenados[cluster_idx];
        std::vector<size_t> indices_en_cluster = clusters->getInds(cluster_actual);
        float coor_c[2] = {con.dar_posicion()[0], con.dar_posicion()[1]};
        for(size_t indice_original : indices_en_cluster){
            punto p = puntos[indice_original];
            float coor_p[2] = {p.mostrar_posicion()[0], p.mostrar_posicion()[1]};
            float distancia = vec_compute_distance(coor_c, coor_p, 2);
            p.editar_distancia(distancia);
            puntos_con_indices.push_back({p, indice_original});
            comparaciones_count++;
        }
        cluster_idx++;
    }
    auto stop_search = std::chrono::high_resolution_clock::now();
    time_without_sort = std::chrono::duration_cast<std::chrono::microseconds>(stop_search - start_search).count();
    auto start_sort = std::chrono::high_resolution_clock::now();
    std::vector<punto> solo_puntos;
    for (const auto& pair : puntos_con_indices) {
        solo_puntos.push_back(pair.first);
    }
    std::vector<size_t> indices_ordenados = argsort(solo_puntos);
    auto stop_sort = std::chrono::high_resolution_clock::now();
    long long sort_time = std::chrono::duration_cast<std::chrono::microseconds>(stop_sort - start_sort).count();
    time_with_sort = time_without_sort + sort_time;
    std::vector<size_t> resultado;
    for(int i = 0; i < m && i < indices_ordenados.size(); i++){
        resultado.push_back(puntos_con_indices[indices_ordenados[i]].second);
    }
    error = calcular_error(resultado_sin_cluster, resultado, con);
    return resultado;
}
