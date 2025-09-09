import numpy as np
import matplotlib.pyplot as plt

def cargar_puntos(archivo):
    """Carga puntos desde un archivo de texto"""
    puntos = []
    with open(archivo, 'r') as f:
        for linea in f:
            x, y = map(float, linea.strip().split())
            puntos.append([x, y])
    return np.array(puntos)

# Cargar todos los datos
print("Cargando datos...")
todos_puntos = cargar_puntos('todos_puntos.txt')
todas_consultas = cargar_puntos('todas_consultas.txt')
consulta = cargar_puntos('consulta.txt')
vecinos_sin = cargar_puntos('resultado_sin_clustering.txt')
vecinos_con = cargar_puntos('resultado_con_clustering.txt')

print(f"Datos cargados:")
print(f"- Total puntos: {len(todos_puntos)}")
print(f"- Total consultas: {len(todas_consultas)}")
print(f"- Vecinos encontrados (sin clustering): {len(vecinos_sin)}")
print(f"- Vecinos encontrados (con clustering): {len(vecinos_con)}")

# Crear la visualización
plt.figure(figsize=(15, 6))

# Subplot 1: Sin clustering
plt.subplot(1, 2, 1)
plt.scatter(todos_puntos[:, 0], todos_puntos[:, 1], color='red', alpha=0.3, s=10, label='Catálogo X')
plt.scatter(todas_consultas[:, 0], todas_consultas[:, 1], color='blue', alpha=0.3, s=20, label='Consultas Q')
plt.scatter(consulta[:, 0], consulta[:, 1], color='green', s=100, marker='*', label='Consulta actual')
plt.scatter(vecinos_sin[:, 0], vecinos_sin[:, 1], color='purple', s=80, edgecolors='black', label='m vecinos más cercanos')

plt.title('Búsqueda SIN Clustering\n(m=8 vecinos más cercanos)')
plt.xlabel('Coordenada X')
plt.ylabel('Coordenada Y')
plt.legend()
plt.grid(True, alpha=0.3)

# Subplot 2: Con clustering
plt.subplot(1, 2, 2)
plt.scatter(todos_puntos[:, 0], todos_puntos[:, 1], color='red', alpha=0.3, s=10, label='Catálogo X')
plt.scatter(todas_consultas[:, 0], todas_consultas[:, 1], color='blue', alpha=0.3, s=20, label='Consultas Q')
plt.scatter(consulta[:, 0], consulta[:, 1], color='green', s=100, marker='*', label='Consulta actual')
plt.scatter(vecinos_con[:, 0], vecinos_con[:, 1], color='orange', s=80, edgecolors='black', label='m vecinos más cercanos')

plt.title('Búsqueda CON Clustering\n(m=8 vecinos más cercanos, k=8 clusters)')
plt.xlabel('Coordenada X')
plt.ylabel('Coordenada Y')
plt.legend()
plt.grid(True, alpha=0.3)

plt.tight_layout()
plt.savefig('visualizacion_vecinos.png', dpi=300, bbox_inches='tight')
plt.show()

# Visualización adicional: Comparación lado a lado
plt.figure(figsize=(12, 8))

plt.scatter(todos_puntos[:, 0], todos_puntos[:, 1], color='lightgray', alpha=0.2, s=5, label='Catálogo X')
plt.scatter(consulta[:, 0], consulta[:, 1], color='black', s=200, marker='*', label='Consulta', zorder=10)
plt.scatter(vecinos_sin[:, 0], vecinos_sin[:, 1], color='blue', s=100, edgecolors='white', label='Sin clustering', alpha=0.8)
plt.scatter(vecinos_con[:, 0], vecinos_con[:, 1], color='red', s=100, edgecolors='white', label='Con clustering', alpha=0.8)

# Conectar puntos con líneas para mostrar diferencias
for i, (vec_sin, vec_con) in enumerate(zip(vecinos_sin, vecinos_con)):
    if i < len(vecinos_con):  # Asegurar que tenemos ambos puntos
        plt.plot([vec_sin[0], vec_con[0]], [vec_sin[1], vec_con[1]], 
                'k--', alpha=0.3, linewidth=1)

plt.title('Comparación: Vecinos más cercanos con y sin Clustering\n(m=8, k=8)')
plt.xlabel('Coordenada X')
plt.ylabel('Coordenada Y')
plt.legend()
plt.grid(True, alpha=0.3)
plt.savefig('comparacion_vecinos.png', dpi=300, bbox_inches='tight')
plt.show()

print("Visualizaciones guardadas como:")
print("- visualizacion_vecinos.png")
print("- comparacion_vecinos.png")