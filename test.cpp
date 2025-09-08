#include "consultas.hpp"
#include "cluster.hpp"
#include "puntos.hpp"
#include "matrix.hpp"
#include "simsearch.hpp"
#include "utils.hpp"
#include <iostream>
#include <vector>
#include <ctime>
#include <chrono>

int main(){

    int n = 1000;
    int k = 8; // numero de clusters
    int dim = 2;
    int m = 8;
    int numero_consultas = 100;

    std::string filename1 = "data_eda.npy";
    Matrix mat_data(filename1);
    
    std::vector<punto> puntos_totales;

    for (size_t i = 0; i < n; i++) {
        std::vector<float> coordenadas;
        const float *data_row = mat_data.getRow(i);
        coordenadas.push_back(data_row[0]);
        coordenadas.push_back(data_row[1]);
        puntos_totales.push_back(punto(coordenadas, 0, i));
    }
    
    std::string filename2 = "queries_eda.npy";
    Matrix mat_queries(filename2);
    
    std::vector<Consulta> consultas_totales;

    for (size_t i = 0; i < numero_consultas; i++) {
        std::vector<float> coordenadas;
        const float *query_row = mat_queries.getRow(i);
        coordenadas.push_back(query_row[0]);
        coordenadas.push_back(query_row[1]);
        consultas_totales.push_back(Consulta(i, coordenadas));
    }
    
    Cluster clusters_totales(mat_data, k);
    SimSearch simulador(puntos_totales, consultas_totales, &clusters_totales);

    auto start_without = std::chrono::high_resolution_clock::now();
    for(int i = 0; i < numero_consultas; i++){
        std::vector<size_t> a = simulador.search_without(simulador.pasar_consulta(i), m);
    }
    auto stop_without = std::chrono::high_resolution_clock::now();
    auto duration_without = std::chrono::duration_cast<std::chrono::microseconds>(stop_without - start_without);
    std::cout << "============================================================================================="<< std::endl;
    std::cout << "* Numero de Clusters: " << k << std::endl;
    std::cout << "* m: " << m << std::endl;

    std::cout << "------------------------------------------------------"<< std::endl;
    std::cout << "* Tiempo de busqueda sin clusters: " << duration_without.count() << " microsegundos" << std::endl;
    std::cout << "* Comparaciones sin clusters: " << simulador.get_comparaciones() << " comparaciones" << std::endl;

    clusters_totales.applyClustering();
    
    auto start_with = std::chrono::high_resolution_clock::now();
    for(int i = 0; i < numero_consultas; i++){
        std::vector<size_t> b = simulador.search_with_clusters(simulador.pasar_consulta(i), m);
    }
    auto stop_with = std::chrono::high_resolution_clock::now();
    auto duration_with = std::chrono::duration_cast<std::chrono::microseconds>(stop_with - start_with);

    std::cout << "------------------------------------------------------"<< std::endl;
    std::cout << "* Tiempo de busqueda con clusters: " << duration_with.count() << " microsegundos" << std::endl;
    std::cout << "* Comparaciones con clusters: " << simulador.get_comparaciones() << " comparaciones" << std::endl;
    
    return 0;
}
