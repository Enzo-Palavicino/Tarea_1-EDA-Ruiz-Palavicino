import numpy as np
import matplotlib.pyplot as plt

def cargar_puntos(archivo):
    """Carga puntos desde un archivo de texto"""
    puntos = []
    with open(archivo, 'r') as f:
        for linea in f:
            try:
                x, y = map(float, linea.strip().split())
                puntos.append([x, y])
            except:
                continue
    return np.array(puntos)

def cargar_clusters(archivo):
    """Carga información de clusters"""
    clusters = []
    with open(archivo, 'r') as f:
        for linea in f:
            try:
                x, y, cluster_id = map(float, linea.strip().split())
                clusters.append([x, y, int(cluster_id)])
            except:
                continue
    return np.array(clusters)

def visualizar_busqueda_sin_clustering():
    """Visualización de búsqueda SIN clustering"""
    print("Cargando datos para visualización sin clustering...")
    
    # Cargar datos originales
    data = np.load('data_eda.npy')
    queries = np.load('queries_eda.npy')
    
    # Cargar resultados exportados desde C++
    consulta = cargar_puntos('consulta_actual.txt')
    vecinos_sin = cargar_puntos('vecinos_sin_clustering.txt')
    
    # Crear visualización
    plt.figure(figsize=(10, 8))
    
    # Todos los puntos del catálogo X (rojo)
    plt.scatter(data[:, 0], data[:, 1], color='red', alpha=0.5, s=15, label='Catálogo X (1000 puntos)')
    
    # Todas las consultas Q (azul claro)
    plt.scatter(queries[:, 0], queries[:, 1], color='blue', alpha=0.3, s=20, label='Consultas Q')
    
    # Consulta actual (azul oscuro)
    plt.scatter(consulta[:, 0], consulta[:, 1], color='darkblue', s=150, marker='*', 
                edgecolors='white', linewidth=2, label='Consulta actual', zorder=10)
    
    # Vecinos más cercanos (verde)
    plt.scatter(vecinos_sin[:, 0], vecinos_sin[:, 1], color='green', s=80, 
                edgecolors='black', linewidth=1.5, label='8 vecinos más cercanos', zorder=5)
    
    plt.title('Búsqueda SIN Clustering (Fuerza Bruta)\nComparación con todos los 1000 puntos', fontsize=14)
    plt.xlabel('Coordenada X', fontsize=12)
    plt.ylabel('Coordenada Y', fontsize=12)
    plt.legend()
    plt.grid(True, alpha=0.2)
    plt.axis('equal')
    
    plt.savefig('busqueda_sin_clustering.png', dpi=300, bbox_inches='tight')
    plt.show()

def visualizar_busqueda_con_clustering(k_value):
    """Visualización de búsqueda CON clustering"""
    print(f"Cargando datos para visualización con k={k_value} clusters...")
    
    # Cargar datos originales
    data = np.load('data_eda.npy')
    queries = np.load('queries_eda.npy')
    
    # Cargar resultados exportados desde C++
    consulta = cargar_puntos('consulta_actual.txt')
    vecinos_con = cargar_puntos('vecinos_con_clustering.txt')
    clusters_info = cargar_clusters('clusters.txt')
    
    # Crear visualización
    plt.figure(figsize=(12, 8))
    
    # Colores para los clusters
    colores = plt.cm.tab10(np.linspace(0, 1, len(clusters_info)))
    
    # Mostrar todos los puntos del catálogo, coloreados por proximidad a clusters
    for i, cluster in enumerate(clusters_info):
        distancias = np.linalg.norm(data - cluster[:2], axis=1)
        # Puntos más cercanos a este cluster (simulación de pertenencia)
        mascara = distancias < 0.15  # Umbral de proximidad
        plt.scatter(data[mascara, 0], data[mascara, 1], 
                   color=colores[i], alpha=0.4, s=10, 
                   label=f'Cluster {int(cluster[2])+1}' if i < 5 else "")
    
    # Mostrar centroides de clusters
    plt.scatter(clusters_info[:, 0], clusters_info[:, 1], color='black', s=120, 
                marker='X', label='Centroides', zorder=8)
    
    # Consulta actual
    plt.scatter(consulta[:, 0], consulta[:, 1], color='darkblue', s=200, marker='*', 
                edgecolors='white', linewidth=2, label='Consulta actual', zorder=10)
    
    # Vecinos encontrados
    plt.scatter(vecinos_con[:, 0], vecinos_con[:, 1], color='lime', s=100, 
                edgecolors='black', linewidth=2, label='8 vecinos encontrados', zorder=9)
    
    # Resaltar cluster más cercano
    distancias_consulta = np.linalg.norm(clusters_info[:, :2] - consulta[0], axis=1)
    cluster_cercano_idx = np.argmin(distancias_consulta)
    cluster_cercano = clusters_info[cluster_cercano_idx]
    
    plt.scatter(cluster_cercano[0], cluster_cercano[1], color='yellow', s=200, 
                edgecolors='red', linewidth=2, marker='o', 
                label=f'Cluster más cercano ({int(cluster_cercano[2])+1})', zorder=11)
    
    plt.title(f'Búsqueda CON Clustering (k={k_value} clusters)\nBúsqueda eficiente usando clusters', fontsize=14)
    plt.xlabel('Coordenada X', fontsize=12)
    plt.ylabel('Coordenada Y', fontsize=12)
    plt.legend()
    plt.grid(True, alpha=0.2)
    plt.axis('equal')
    
    plt.savefig(f'busqueda_con_clustering_k{k_value}.png', dpi=300, bbox_inches='tight')
    plt.show()

# Ejecutar visualizaciones
if __name__ == "__main__":
    print("="*60)
    print("VISUALIZACIÓN DE BÚSQUEDA POR VECINOS MÁS CERCANOS")
    print("="*60)
    
    # Visualizar búsqueda sin clustering
    visualizar_busqueda_sin_clustering()
    
    # Visualizar búsqueda con clustering para diferentes valores de k
    print("\n" + "="*60)
    visualizar_busqueda_con_clustering(8)   # k=8 clusters
    
    print("\n" + "="*60)
    visualizar_busqueda_con_clustering(32)  # k=32 clusters (óptimo según tus resultados)
    
    print("\nVisualizaciones completadas!")
    print("Archivos generados:")
    print("- busqueda_sin_clustering.png")
    print("- busqueda_con_clustering_k8.png") 
    print("- busqueda_con_clustering_k32.png")