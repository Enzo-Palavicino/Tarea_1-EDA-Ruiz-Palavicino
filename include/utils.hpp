#pragma once

#include <cmath>
#include "matrix.hpp"
#include "puntos.hpp"
#include "consultas.hpp"
#include <vector>

float vec_compute_distance(const float* u, const float* v, size_t dim);

void vec_add(float *s, const float* u,  size_t dim);

void vec_divide(float *u, float scalar, size_t dim);

void set_array(float *array, size_t dim, float val = 0);

float vec_compute_avg_dif(const float *u, const float* v,  size_t dim);

void print_array(const float *array, size_t d);

void crear_puntos(const float * datos, std::vector<punto> * puntos, int  t);

void crear_consultas(const float * datos, std::vector<Consulta> * consultas, int  t);

// quick sorts
// sin clusters

int dividir_punto(std::vector<punto> & puntos, int i, int j); // esta funcion se saco del libro del profe pg. 31

void quick_sort(std::vector<punto> & puntos, int i, int j);

// con clusters

// Funcion que ordena los indices de un vector de puntos en base a sus distancias.
std::vector<size_t> argsort(const std::vector<punto>& puntos);

// Nueva función: argsort para vectores de floats
std::vector<size_t> argsort(const std::vector<float>& values);

//punto seguro