#pragma once
#include "matrix.hpp"
#include "puntos.hpp"
#include <vector>

class Cluster{
    private:
        const Matrix &mat_data; //it's a set of vectors n x dim
        Matrix mat_centroids; // it'ss a set of centroids, clusters k x dim
        size_t k_clusters; //it's a number of clusters
        std::vector<size_t> * inds; // it is an array of vectors
        std::vector<punto> * puntos; // contiene los puntos a objetos

    public: 
        Cluster(const Matrix &mat, size_t k = 8);        
        void compute_clusters();
        void update_centroids();
        void applyClustering();
        const float *getCentroid(size_t i);
        std::vector<size_t> getInds(size_t i);
        void print_clusters() const;
        virtual ~Cluster();
        void imprimir_puntos(size_t numero, const Matrix& mat);
        std::vector<punto> get_punto(int i);
        int cantidad_puntos(int i);
};
