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
#include <chrono> // Biblioteca para medir tiempos


 void print_vector(const std::vector<size_t> &v){
    for (size_t i = 0; i < v.size() ; i++){
        std::cout<<v[i]<<",";
    }
    std::cout<<std::endl;
 }

int main(int args, char* vargs[]){
    
    srand(static_cast<unsigned int>(time(NULL)));
    // Matrix mat(2,2);
    // float x[] = {1,2};
    // mat.show();
    // vec_add(x, x, 2);
    // vec_divide(x, 3, 2);
    // mat.setRow(0, x);
    // mat.show();
    // return 0;
    //Rutas Gonzalo
    //std::string str_data("/home/pbn/Desktop/EDA/tarea 1/tarea 1/codigo base/data_eda.npy");
    //std::string str_consulta("/home/pbn/Desktop/EDA/tarea 1/tarea 1/codigo base/queries_eda.npy");
    //Rutas Enzo
    std::string str_data("data_eda.npy");
    std::string str_consulta("queries_eda.npy");
    Matrix mat(str_data); // crea los puntos normales
    Matrix mat1(str_consulta); // crea las consultas

    std::vector<punto>  puntos;
    std::vector<Consulta> consultas;

    crear_consultas(mat1.getData(), &consultas, mat1.getN());

    int cantidad_clusters = 16;
    //const float *row = mat.getRow(999);
    //mat.show(); // este imprime la matriz
    

    // hace los puntos sin clusters
    crear_puntos(mat.getData(), &puntos, mat.getN());


    /*for(size_t i = 0; i < 1000; i++){ // puse size_t para que no diera error porque no tiene 
                                            // asignado el tipo de dato hasta que se usa
        puntos[i].imprimir_posicion();
    }*/

    /**/
    // hace los clusters
    //print_array(row, mat.getDim());
    Cluster cluster(mat, cantidad_clusters); // crea la cantidad de clusters
    cluster.applyClustering();    
    std::cout << "--- print clusters" << std::endl;
    cluster.print_clusters();
    //std::vector<size_t> inds_0= cluster.getInds(0);
    //std::vector<size_t> inds_1= cluster.getInds(1);
    //print_vector(inds_0);

    /*for(int i = 0; i < cantidad_clusters; i++){ // puntos por cluster
        std::cout << " En el cluster n° " << i << ", hay " << (cluster.getInds(i)).size() << " puntos " << std::endl;
    }*/
    int m = 100;
    SimSearch simulador(puntos, consultas, &cluster);

    /*
    std::chrono::high_resolution_clock::time_point inicio = std::chrono::high_resolution_clock::now();
    //std::vector<std::vector<std::vector<float>>> ordenado_consulta;
    for(size_t i = 0; i < consultas.size(); i ++){
        std::vector<std::vector<float>> a = simulador.search_without(simulador.pasar_consulta(0), m);  // las ordenaciones sin clusters se guardan en consultas
    }
    std::chrono::high_resolution_clock::time_point fin = std::chrono::high_resolution_clock::now();
    std::chrono::microseconds duracion = std::chrono::duration_cast<std::chrono::microseconds>(fin - inicio);

    std::cout << "El tiempo de ordenado demoro " << duracion.count() << " [uSeg] microsegundos  " << std::endl;
    */
    

    
    //cluster.imprimir_puntos(2, mat);
    
 
    return 0;
}