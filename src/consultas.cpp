#include <vector>
#include<iostream>
#include<string>
#include<fstream>
#include<sstream>
#include "consultas.hpp"

Consulta::Consulta(int n,std::vector<float> p){
    posicion = p;
    nombre = n;
}


std::vector<float> Consulta::dar_posicion() const {
    return posicion;
}

std::vector<punto> Consulta::dar_puntos(){
    return puntos_mas_cercanos;

}

void Consulta::modificar_puntos(std::vector<punto> nuevos_puntos){
    puntos_mas_cercanos = nuevos_puntos;
}

void Consulta::mostrar_datos(){
    std::cout << "======================================" << "\n\n";
    std::cout <<"          Datos del punto " << nombre << "\n \n";
    std::cout <<" x: " << posicion[0] << " y: " << posicion[1] << std::endl;
    std::cout << "======================================" << "\n\n";
}