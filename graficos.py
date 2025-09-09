import numpy as np
import matplotlib.pyplot as plt
import matplotlib.colors as mcolors

def leer_puntos_archivo(archivo):
    """Lee un archivo de puntos y devuelve un array numpy"""
    puntos = []
    with open(archivo, 'r') as f:
        for linea in f:
            coords = linea.strip().split()
            if len(coords) >= 2:
                x = float(coords[0])
                y = float(coords[1])
                puntos.append([x, y])
    return np.array(puntos)

def leer_puntos_con_clusters(archivo):
    """Lee archivo con puntos y su cluster asignado"""
    puntos = []
    clusters = []
    with open(archivo, 'r') as f:
        for linea in f:
            datos = linea.strip().split()
            if len(datos) >= 3:
                x = float(datos[0])
                y = float(datos[1])
                cluster = int(datos[2])
                puntos.append([x, y])
                clusters.append(cluster)
    return np.array(puntos), np.array(clusters)

def leer_centroides(archivo):
    """Lee archivo de centroides"""
    centroides = []
    with open(archivo, 'r') as f:
        for linea in f:
            coords = linea.strip().split()
            if len(coords) >= 2:
                x = float(coords[0])
                y = float(coords[1])
                centroides.append([x, y])
    return np.array(centroides)

def leer_consulta(archivo):
    """Lee el punto de consulta"""
    with open(archivo, 'r') as f:
        linea = f.readline().strip()
        coords = linea.split()
        if len(coords) >= 2:
            x = float(coords[0])
            y = float(coords[1])
            return np.array([x, y])
    return None

def grafico_sin_clustering():
    """Genera gráfico para búsqueda SIN clustering - Estilo minimalista"""
    print("Generando gráfico SIN clustering...")
    try:
        catalogo = np.load('data_eda.npy')
        consulta = leer_consulta('consulta_actual.txt')
        vecinos = leer_puntos_archivo('vecinos_sin_clustering.txt')
    except FileNotFoundError as e:
        print(f"Error: Archivo no encontrado - {e}")
        return

    plt.figure(figsize=(10, 8), facecolor='white')

    plt.scatter(catalogo[:, 0], catalogo[:, 1], 
                c='lightgray', alpha=0.7, s=20, label='Catálogo')

    plt.scatter(vecinos[:, 0], vecinos[:, 1], 
                c='navy', s=80, label='Vecinos más cercanos', 
                edgecolors='white', linewidth=1, alpha=0.9)

    plt.scatter(consulta[0], consulta[1], 
                c='red', marker='*', s=300, 
                label='Consulta', edgecolors='black', linewidth=1.5)
    
    plt.title('Búsqueda SIN Clustering', fontsize=14, fontweight='bold', pad=20)
    plt.xlabel('Coordenada X', fontsize=11)
    plt.ylabel('Coordenada Y', fontsize=11)
    plt.grid(True, alpha=0.2, linestyle='--')
    plt.legend(loc='upper right', frameon=True, fancybox=True, shadow=True)
    
    plt.gca().set_facecolor('white')
    plt.gca().spines['top'].set_visible(False)
    plt.gca().spines['right'].set_visible(False)
    plt.gca().spines['left'].set_alpha(0.3)
    plt.gca().spines['bottom'].set_alpha(0.3)
    
    plt.axis('equal')
    plt.tight_layout()
    plt.savefig('busqueda_sin_clustering.png', dpi=300, bbox_inches='tight', 
                facecolor='white', edgecolor='none')
    plt.show()
    print("Gráfico SIN clustering guardado como 'busqueda_sin_clustering.png'")

def grafico_con_clustering(k=32):
    """Genera gráfico para búsqueda CON clustering - Estilo similar a la referencia"""
    print(f"Generando gráfico CON clustering (k={k})...")
    
    try:
        puntos, clusters = leer_puntos_con_clusters('puntos_con_clusters.txt')
        centroides = leer_centroides('clusters.txt')
        consulta = leer_consulta('consulta_actual.txt')
        vecinos = leer_puntos_archivo('vecinos_con_clustering.txt')
    except FileNotFoundError as e:
        print(f"Error: Archivo no encontrado - {e}")
        return
    
    distancias = np.linalg.norm(centroides - consulta, axis=1)
    cluster_cercano_idx = np.argmin(distancias)
    centroide_cercano = centroides[cluster_cercano_idx]
    
    plt.figure(figsize=(10, 8), facecolor='white')
    
    colores = ['#FF6B6B', '#4ECDC4', '#45B7D1', '#96CEB4', '#FECA57', 
               '#FF9FF3', '#54A0FF', '#5F27CD', '#00D2D3', '#FF9F43',
               '#A3CB38', '#ED4C67', '#B53471', '#EE5A24', '#009432',
               '#0652DD', '#9980FA', '#833471', '#F79F1F', '#EA2027']

    for cluster_id in np.unique(clusters):
        mask = clusters == cluster_id
        color_idx = cluster_id % len(colores)
        plt.scatter(puntos[mask, 0], puntos[mask, 1], 
                    c=colores[color_idx], alpha=0.6, s=20)

    plt.scatter(centroides[:, 0], centroides[:, 1], 
                c='black', marker='X', s=80, label='Centroides', 
                edgecolors='white', linewidth=1.5)

    plt.scatter(centroide_cercano[0], centroide_cercano[1], 
                c='yellow', marker='o', s=200, 
                label='Cluster más cercano', edgecolors='black', linewidth=2, alpha=0.8)

    plt.scatter(vecinos[:, 0], vecinos[:, 1], 
                c='blue', s=60, label='Vecinos', 
                edgecolors='white', linewidth=1.2, alpha=0.9)
    
    plt.scatter(consulta[0], consulta[1], 
                c='red', marker='*', s=250, 
                label='Consulta', edgecolors='black', linewidth=1.5)

    plt.title(f'Búsqueda CON Clustering (k={k})', fontsize=14, fontweight='bold', pad=20)
    plt.xlabel('Coordenada X', fontsize=11)
    plt.ylabel('Coordenada Y', fontsize=11)
    plt.grid(True, alpha=0.2, linestyle='--')
    plt.legend(loc='upper right', frameon=True, fancybox=True, shadow=True)

    plt.gca().set_facecolor('white')
    plt.gca().spines['top'].set_visible(False)
    plt.gca().spines['right'].set_visible(False)
    plt.gca().spines['left'].set_alpha(0.3)
    plt.gca().spines['bottom'].set_alpha(0.3)
    
    plt.figtext(0.15, 0.02, f"Clusters: {len(np.unique(clusters))} | Vecinos: {len(vecinos)}", 
                fontsize=10, ha='center', 
                bbox=dict(boxstyle="round,pad=0.3", facecolor="white", alpha=0.8))
    
    plt.axis('equal')
    plt.tight_layout()
    
    plt.savefig(f'busqueda_con_clustering_k{k}.png', dpi=300, bbox_inches='tight', 
                facecolor='white', edgecolor='none')
    plt.show()
    print(f"Gráfico CON clustering guardado como 'busqueda_con_clustering_k{k}.png'")

def main():
    
    grafico_sin_clustering()
    print()
    grafico_con_clustering(k=32)  # valor de k aqui
    


if __name__ == "__main__":
    main()