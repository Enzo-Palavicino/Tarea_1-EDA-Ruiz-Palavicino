#include "utils.hpp"
#include "matrix.hpp"
#include "puntos.hpp"
#include <cmath>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

float vec_compute_distance(const float* u, const float* v, size_t dim){ // quite el const porque molestaba mucho en el codigo de calcular las distancias
    float d = 0;
    float s = 0;
    float diff = 0;
    for (size_t i = 0;  i < dim; i++){
        diff = (u[i] - v[i]);
        s += diff * diff;
    }
    d = std::sqrt(s);
    return d;
}

void vec_add(float* s, const float* u,  size_t dim){
    for (size_t i = 0;  i < dim; i++){
        s[i] = u[i] + s[i];
    }
}

void vec_divide(float* u, float scalar, size_t dim){
    for (size_t i = 0;  i < dim; i++){
        u[i] = u[i] / scalar;
    }
}

void set_array(float *array, size_t dim, float val){
    for (size_t i = 0;  i < dim; i++){
        array[i] = val;
    }
}

float vec_compute_avg_dif(const float *u, const float* v,  size_t dim){

    float dif = 0;
    for (size_t i = 0;  i < dim; i++){        
        dif = dif + std::abs(u[i] - v[i]);
        //std::cout << u[i] << " - " << v[i] << "  " << std::abs(u[i] - v[i]) << std::endl;
    }   
    //std::cout << dif <<std::endl;
    return dif / dim;
}

void print_array(const float *array, size_t d){
    for (size_t i = 0; i< d; i ++){
        std::cout << array[i] << " ";
    }
    std::cout<< std::endl;
}

void crear_puntos( const float * mat, std::vector<punto> * puntos, int t){
    size_t dim = t;
    //std::cout << "tamaño de datos:  " << dim << std::endl;
    for(size_t i = 0; i < dim; i ++){
        std::vector<float> coordenadas;
        coordenadas.push_back(mat[i]);
        coordenadas.push_back(mat[i+1]);
        //std::cout << " numero: " <<  i << ",";
        //std::cout << "x: " << coordenadas[0] << " y: " << coordenadas[1] << std::endl;
        (puntos)->push_back(punto(coordenadas,  0, i));
    }
}

void crear_consultas(const float * mat, std::vector<Consulta> * consultas, int  t){
       size_t dim = t;
    //std::cout << "tamaño de datos:  " << dim << std::endl;
    for(size_t i = 0; i < dim; i ++){
        std::vector<float> coordenadas;
        coordenadas.push_back(mat[i]);
        coordenadas.push_back(mat[i+1]);
        //std::cout << " numero: " <<  i << ",";
        //std::cout << "x: " << coordenadas[0] << " y: " << coordenadas[1] << std::endl;
        (consultas)->push_back(Consulta(i, coordenadas));
    } 
}

int dividir_punto(std::vector<punto> & puntos, int i, int j){
    
    int p = i + rand() % (j - i + 1); // randomiza la posicion del pivote
    std::swap(puntos[p], puntos[j]);

    while(i < j){

        while (i < p && (puntos)[i].mostrar_distancia() <= (puntos)[p].mostrar_distancia()) {
            
            i++; // va moviendo el pivote i, que son los numeros menores a el pivote p
                
        }
        
        while (j > p && (puntos)[j].mostrar_distancia() >= (puntos)[p].mostrar_distancia()) {

            j--; // es lo mismo que el pivote i, pero con los numeros mayores a p
        }
        
        if (i < j) { // pongo este if para asegurar que se cumpla la condicion del while
            std::swap(puntos[i], puntos[j]);
            if (i == p) p = j;
            else if (j == p) p = i;
        }
    }
    return p;
}

void quick_sort(std::vector<punto>& puntos, int i, int j) {
    if (i < j) {
        int k = dividir_punto(puntos, i, j);
        quick_sort(puntos, i, k - 1);
        quick_sort(puntos, k + 1, j);
    }
}
// funcion que calcule todas las distancias de los puntos de un arreglo

// algoritmo de ver el maximo de los puntos

// seria bueno ocupar 2 algoritmos distintos para comparar la velocidad de estos

// algoritmo merge sort de los puntos en base a la distancia

// algoritmo quick sort de los puntos en base a la distancia

// funcion que imprima las posiciones de los puntos de un arreglo


