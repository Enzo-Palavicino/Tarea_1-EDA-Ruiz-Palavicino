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
#include <iomanip>
#include <fstream>

void exportar_resultados(const std::vector<size_t>& indices, 
                        const std::vector<punto>& puntos, 
                        const std::string& filename) {
    std::ofstream file(filename);
    for (size_t idx : indices) {
        const auto& pos = puntos[idx].mostrar_posicion();
        file << pos[0] << " " << pos[1] << "\n";
    }
    file.close();
}

void exportar_puntos_con_clusters(Cluster* clusters, 
                                 const std::vector<punto>& puntos, 
                                 const std::string& filename) {
    std::ofstream file(filename);
    for (size_t i = 0; i < clusters->getK(); i++) {
        std::vector<size_t> indices = clusters->getInds(i);
        for (size_t idx : indices) {
            const auto& pos = puntos[idx].mostrar_posicion();
            file << pos[0] << " " << pos[1] << " " << i << "\n";
        }
    }
    file.close();
}

void exportar_centroides(Cluster* clusters, const std::string& filename) {
    std::ofstream file(filename);
    for (size_t i = 0; i < clusters->getK(); i++) {
        const float* centroide = clusters->getCentroid(i);
        file << centroide[0] << " " << centroide[1] << "\n";
    }
    file.close();
}

void exportar_consulta(const Consulta& consulta, const std::string& filename) {
    std::ofstream file(filename);
    const auto& pos = consulta.dar_posicion();
    file << pos[0] << " " << pos[1] << "\n";
    file.close();
}

void imprimir_tabla_por_m(int m, const std::vector<int>& k_values, 
                         const std::vector<std::vector<int>>& comparaciones_promedio,
                         const std::vector<std::vector<long long>>& tiempo_sin_ordenar,
                         const std::vector<std::vector<long long>>& tiempo_con_ordenar,
                         const std::vector<std::vector<float>>& errores_promedio) {
    
    std::cout << "\n\n================================================================" << std::endl;
    std::cout << "TABLA PARA m = " << m << std::endl;
    std::cout << "================================================================" << std::endl;
    std::cout << std::setw(10) << "k-clusters" 
              << std::setw(20) << "#comparaciones" 
              << std::setw(25) << "tiempo sin ordenar"
              << std::setw(25) << "tiempo con ordenar"
              << std::setw(15) << "error" << std::endl;
    std::cout << "----------------------------------------------------------------" << std::endl;

    std::cout << std::setw(10) << "0" 
              << std::setw(20) << comparaciones_promedio[0][0] 
              << std::setw(25) << tiempo_sin_ordenar[0][0] 
              << std::setw(25) << tiempo_con_ordenar[0][0]
              << std::setw(15) << "0.0" << std::endl;

    for (size_t i = 0; i < k_values.size(); i++) {
        std::cout << std::setw(10) << k_values[i] 
                  << std::setw(20) << comparaciones_promedio[1][i] 
                  << std::setw(25) << tiempo_sin_ordenar[1][i] 
                  << std::setw(25) << tiempo_con_ordenar[1][i]
                  << std::setw(15) << std::fixed << std::setprecision(6) << errores_promedio[1][i] << std::endl;
    }
}

int main() {
    int n = 1000;
    int dim = 2;
    std::vector<int> m_values = {8, 16, 32, 64, 128};
    std::vector<int> k_values = {8, 16, 32, 64, 128};
    int numero_consultas = 100;
    
    int consulta_visualizacion = 0; 

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

    for (int m : m_values) {
        std::vector<std::vector<int>> comparaciones_por_k(2);
        std::vector<std::vector<long long>> tiempo_sin_ordenar_por_k(2);
        std::vector<std::vector<long long>> tiempo_con_ordenar_por_k(2);
        std::vector<std::vector<float>> errores_por_k(2);
        

        {
            Cluster clusters_dummy(mat_data, 8);
            SimSearch simulador(puntos_totales, consultas_totales, &clusters_dummy);
            
            int comparaciones_total = 0;
            long long tiempo_sin_total = 0;
            long long tiempo_con_total = 0;
            
            for (int i = 0; i < numero_consultas; i++) {
                auto resultado = simulador.search_without(simulador.pasar_consulta(i), m);
                comparaciones_total += simulador.get_comparaciones();
                tiempo_sin_total += simulador.get_time_without_sort();
                tiempo_con_total += simulador.get_time_with_sort();

                if (i == consulta_visualizacion) {
                    exportar_consulta(simulador.pasar_consulta(i), "consulta_actual.txt");
                    exportar_resultados(resultado, puntos_totales, "vecinos_sin_clustering.txt");
                }
            }
            
            comparaciones_por_k[0].push_back(comparaciones_total / numero_consultas);
            tiempo_sin_ordenar_por_k[0].push_back(tiempo_sin_total / numero_consultas);
            tiempo_con_ordenar_por_k[0].push_back(tiempo_con_total / numero_consultas);
            errores_por_k[0].push_back(0.0f);
        }

        for (int k : k_values) {
            std::cout << "Procesando m = " << m << ", k = " << k << "..." << std::endl;
            
            Cluster clusters_totales(mat_data, k);
            clusters_totales.applyClustering();
            SimSearch simulador(puntos_totales, consultas_totales, &clusters_totales);

            int comparaciones_total = 0;
            long long tiempo_sin_total = 0;
            long long tiempo_con_total = 0;
            float error_total = 0.0f;

            exportar_puntos_con_clusters(&clusters_totales, puntos_totales, "puntos_con_clusters.txt");
            exportar_centroides(&clusters_totales, "clusters.txt");

            for (int i = 0; i < numero_consultas; i++) {
                float error_consulta = 0.0f;
                auto resultado = simulador.search_with_clusters(simulador.pasar_consulta(i), m, error_consulta);
                comparaciones_total += simulador.get_comparaciones();
                tiempo_sin_total += simulador.get_time_without_sort();
                tiempo_con_total += simulador.get_time_with_sort();
                error_total += error_consulta;

                if (i == consulta_visualizacion) {
                    exportar_resultados(resultado, puntos_totales, "vecinos_con_clustering.txt");
                }
            }
            
            comparaciones_por_k[1].push_back(comparaciones_total / numero_consultas);
            tiempo_sin_ordenar_por_k[1].push_back(tiempo_sin_total / numero_consultas);
            tiempo_con_ordenar_por_k[1].push_back(tiempo_con_total / numero_consultas);
            errores_por_k[1].push_back(error_total / numero_consultas);
        }

        imprimir_tabla_por_m(m, k_values, comparaciones_por_k, 
                           tiempo_sin_ordenar_por_k, tiempo_con_ordenar_por_k, 
                           errores_por_k);
    }
    return 0;
}