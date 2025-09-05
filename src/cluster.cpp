#include "cluster.hpp"
#include "utils.hpp"
#include <cstring>
#include <algorithm>

Cluster::Cluster(const Matrix &mat, size_t k):
mat_data(mat), mat_centroids(k, mat.getDim()), k_clusters(k), inds(nullptr) {
    inds = new std::vector<size_t>[k_clusters];
    puntos = new std::vector<punto>[k_clusters];
    for (size_t i = 0; i <  k_clusters; i++ ){                
        inds[i].clear();     
        puntos[i].clear();   
    }
}

//**choose the best cluster for each point */
void Cluster::compute_clusters(){
    float min_dist = 0;
    size_t best_cluster = -1;
    const float *vec_x = nullptr;
    const float *vec_u = nullptr;
    float d = 0;
    //set the inds to zero, cleaning groups
    for (size_t j = 0; j < k_clusters; j++){
        inds[j].clear();  // se encargan de limipiar los puntos
        puntos[j].clear();       
    }    
    for (size_t i = 0; i < mat_data.getN(); i++){        
        min_dist = 1000000;
        best_cluster = -1;
        vec_x = mat_data.getRow(i); 
        std::vector<float> a;
        a.push_back(vec_x[0]); // se guarda el x
        a.push_back(vec_x[1]); // se guarda el y
        // search for the best cluster for vec_x
        for (size_t j = 0; j < k_clusters; j++){            
            vec_u = mat_centroids.getRow(j);            
            d = vec_compute_distance(vec_x, vec_u, mat_data.getDim());                        
            if (d < min_dist){
                best_cluster = j;
                min_dist = d;
            }
        }        
        puntos[best_cluster].push_back(punto(a, best_cluster, i)); // posicion, numero de cluster y nombre
        inds[best_cluster].push_back(i);    
        
        //std::cout << " numero: " <<  i << ",";
        //std::cout << " numero de cluster: " <<  best_cluster << ","<< std::endl;
        // hay que editar aqui para añadir los puntos   
    }
}

//**recompute the centroid for each cluster */
void Cluster::update_centroids(){
    const float *vec_x = nullptr;
    for (size_t j = 0; j < k_clusters; j++){        
        if (inds[j].size() > 0){
            float* u = new float[mat_data.getDim()];
            set_array(u, mat_data.getDim(), 0);
            for (size_t x : inds[j]){
                //std::cout<<" < " << x << std::endl;
                vec_x = mat_data.getRow(x);            
                vec_add(u, vec_x, mat_data.getDim());
            }                   
            vec_divide(u, inds[j].size(), mat_data.getDim());
            mat_centroids.setRow(j, u);               
            delete[] u;
        }
    }
}


void Cluster::applyClustering(){
    // random   
    mat_centroids.setAllRandom();
    float dif_clusters  = 1000;
    float epsilon = 0.001 ;
    int centroid_size = mat_centroids.getN() * mat_centroids.getDim();
    float *centroids_1 = new float[centroid_size];    
    size_t iter = 0;
    while((dif_clusters > epsilon) && (iter < 10)){        
        std::copy(mat_centroids.getData(), mat_centroids.getData() +  centroid_size, centroids_1);
        //mat_centroids.show();        
        compute_clusters();        
        update_centroids();
        //mat_centroids.show();
        dif_clusters = vec_compute_avg_dif(centroids_1, mat_centroids.getData(), centroid_size);              
        iter = iter + 1;
    }    
    delete[] centroids_1;    
}

const float* Cluster::getCentroid(size_t i){
    return mat_centroids.getRow(i);
}

std::vector<size_t> Cluster::getInds(size_t i){
    return inds[i];
}

void Cluster::print_clusters() const{
    mat_centroids.show();
}

Cluster::~Cluster(){
    if (inds!= nullptr){
        delete[] inds;       
        delete[] puntos;    
    }
}

void Cluster::imprimir_puntos(size_t numero, const Matrix& mat){
    // esta funcion imprime los puntos que tiene un cluster
    std::vector<size_t> idx = getInds(numero); // guarda el cluster numero
    std::cout << "Datos de los puntos en el cluster "<< numero <<":" << std::endl;
    for (size_t i = 0; i < idx.size(); i++) {
        /*size_t punto_index = idx[i];     
        const float* punto_data = mat.getRow(punto_index);
        std::cout << "Punto " << punto_index << ": ";
        print_array(punto_data, mat.getDim());*/
        puntos[numero][i].imprimir_posicion();
        //std::cout << " " <<  puntos[numero][i].mostrar_nombre() << ",";
    }
}

std::vector<punto> Cluster::get_punto(int i){
    return puntos[i];  // retorna los puntos de los arreglos del cluster
}

int Cluster::cantidad_puntos(int i){
    return inds[i].size();
}