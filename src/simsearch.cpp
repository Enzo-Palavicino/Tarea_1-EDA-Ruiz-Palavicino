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

SimSearch::SimSearch(std::vector<punto> puntos1, std::vector<Consulta> consultas1, Cluster* clusters1){
    puntos = puntos1;
    consultas = consultas1;
    clusters = clusters1;

}

Cluster * SimSearch::pasar_cluster(){
    return clusters; // pasa el puntero original, es decir el cluster original, asi que hay que tener cuidado

}

std::vector<punto>  SimSearch::pasar_puntos(){
    return puntos;

}

Consulta  SimSearch::pasar_consulta(int i){
    return consultas[i];

}

size_t SimSearch::get_comparaciones() const { 
    return comparaciones_count; 
}

void SimSearch::reset_comparaciones() { 
    comparaciones_count = 0; 
}

std::vector<size_t> SimSearch::search_without(Consulta con, int m){
    reset_comparaciones();
    float coor_c[2] = {(con.dar_posicion())[0], (con.dar_posicion())[1]};

    for(size_t i = 0; i < puntos.size(); i ++){
        float coor_p[2] = {(puntos[i].mostrar_posicion())[0], (puntos[i].mostrar_posicion())[1]};
        float distancia = vec_compute_distance(coor_c, coor_p, 2);
        puntos[i].editar_distancia(distancia);
        comparaciones_count++;
    }

    std::vector<size_t> indices_ordenados = argsort(puntos);

    std::vector<size_t> resultado;
    for(int i = 0; i < m; i++){
        resultado.push_back(puntos[indices_ordenados[i]].mostrar_nombre());
    }
    return resultado;
} 

std::vector<size_t> SimSearch::search_with_clusters(Consulta con ,int m){
    reset_comparaciones();
    float min_distancia_cluster = -1;
    size_t cluster_mas_cercano = 0;

    for (size_t i = 0; i < clusters->getK(); i++) {
        const float* centroide = clusters->getCentroid(i);
        float distancia_a_cluster = vec_compute_distance(con.dar_posicion().data(), centroide, 2);
        
        if (min_distancia_cluster == -1 || distancia_a_cluster < min_distancia_cluster) {
            min_distancia_cluster = distancia_a_cluster;
            cluster_mas_cercano = i;
        }
    }

    std::vector<size_t> indices_en_cluster = clusters->getInds(cluster_mas_cercano);
    std::vector<punto> puntos_del_cluster;
    for(size_t indice : indices_en_cluster){
        puntos_del_cluster.push_back(puntos[indice]);
    }

    float coor_c[2] = {(con.dar_posicion())[0], (con.dar_posicion())[1]};
    for(size_t i = 0; i < puntos_del_cluster.size(); i ++){
        float coor_p[2] = {(puntos_del_cluster[i].mostrar_posicion())[0], (puntos_del_cluster[i].mostrar_posicion())[1]};
        float distancia = vec_compute_distance(coor_c, coor_p, 2);
        puntos_del_cluster[i].editar_distancia(distancia);
        comparaciones_count++;
    }

    std::vector<size_t> indices_ordenados = argsort(puntos_del_cluster);

    std::vector<size_t> resultado;
    for(int i = 0; i < m && i < indices_ordenados.size(); i++){
        resultado.push_back(puntos_del_cluster[indices_ordenados[i]].mostrar_nombre());
    }

    // Manejar el caso si el cluster es más pequeño que m
    if(resultado.size() < m){
        // Lógica para buscar en clústeres vecinos.
        // Esto es un desafío adicional que puedes implementar después.
        // Por ahora, solo devolvemos lo que encontramos.
    }
    
    return resultado;
}
