#include <vector>
#include<iostream>
#include<string>
#include<fstream>
#include<sstream>
#include "puntos.hpp"


punto::punto(std::vector<float> posiciones, int n1_cluster, int nombres){
    posicion = posiciones;
    n_cluster = n1_cluster;
    nombre = nombres;
    dis_cent = -1;
}

int punto::mostrar_nombre(){
    return nombre;
}

std::vector<float> punto::mostrar_posicion(){
    return posicion;
}

float punto::mostrar_distancia(){
    return dis_cent;
}

int punto::cluster_actual(){
    return n_cluster;
}

void punto::editar_distancia(float n_dis){
    dis_cent = n_dis;
}

void punto::mostrar_datos(){
    std::cout << "======================================" << "\n\n";
    std::cout <<"          Datos del punto " << nombre << "\n \n";
    std::cout <<" x: " << posicion[0] << " y: " << posicion[1] << std::endl;
    std::cout <<" pertenece al cluster: " << n_cluster << std::endl;
    std::cout <<" distancia a la consulta: " << dis_cent << std::endl;
    std::cout << "======================================" << "\n\n";
}

void punto::imprimir_posicion(){
    std::cout << " [ " << posicion[0] << " , " << posicion[1] << " ] ,";
}

