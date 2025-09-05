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

SimSearch::SimSearch(std::vector<punto> puntos1, std::vector<Consulta> consultas1, Cluster*  clusters1){
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

std::vector<std::vector<float>> SimSearch::search_without(Consulta con, int m){

    // calculador de distancias
    // primero hay que calcular la distancia de la consulta a 0 al m-esimo punto
    float coor_c[2] = {(con.dar_posicion())[0], (con.dar_posicion())[1]};

    for(size_t i = 0; i < puntos.size(); i ++){

        float coor_p[2] = {(pasar_puntos()[i].mostrar_posicion())[0], (pasar_puntos()[i].mostrar_posicion())[1]};
        float distancia = vec_compute_distance(coor_c, coor_p, 2);
        puntos[i].editar_distancia(distancia);

    }
    //---------------------------------------------

    // ordenador quicksort
    std::vector<punto> punto_aux = puntos;

    quick_sort(punto_aux, 0, punto_aux.size()-1);

    con.modificar_puntos(punto_aux); // esto es para hacer más facil la comparacion del error

    std::vector<std::vector<float>> punto_dis;

    for(int i = 0; i < m; i ++){
        std::vector<float> aux = {(punto_aux[i].mostrar_posicion())[0], (punto_aux[i].mostrar_posicion())[1]};
        punto_dis.push_back(aux);

    }
    return punto_dis;
} 

std::vector<std::vector<size_t>> SimSearch::search_with_clusters(Consulta con ,int m){

    

}