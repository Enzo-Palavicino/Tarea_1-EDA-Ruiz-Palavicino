# Tarea_1-EDA-Ruiz-Palavicino

¡IMPORTANTE!
##El Codigo esta en la rama Master##
##Es necesario hacer que los contenidos se ajusten al terminal para ver de mejor manera los graficos ya que pueden variar como se muestren las tablas en el terminal segun el tamaño de la resolucion##

##Configuración del Entorno de Desarrollo##
- Para ejecutar el programa de búsqueda por clustering, el usuario primero debe clonar el repositorio desde GitHub utilizando el comando git clone https://github.com/Enzo-Palavicino/Tarea_1-EDA-Ruiz-Palavicino.git. Una vez clonado, es recomendable abrir la carpeta del proyecto en Visual Studio Code para tener acceso a los archivos necesarios.

##Compilación del Programa C++##
- El usuario debe asegurarse de tener instalado un compilador de C++ como g++ o clang. En la terminal integrada de VSCode, navega hasta la carpeta del proyecto y ejecuta el comando de compilación. Dado que el proyecto utiliza múltiples archivos, se recomienda compilar todos los archivos .cpp juntos asi en el terminal bash:

g++ -std=c++11 -o programa_principal main.cpp simsearch.cpp utils.cpp cluster.cpp puntos.cpp consultas.cpp matrix.cpp

- Este comando compila todos los archivos fuente y genera un ejecutable llamado programa_principal.

##Preparación de los Datos##
- Antes de ejecutar el programa, el usuario debe verificar que los archivos de datos data_eda.npy y queries_eda.npy estén presentes en el directorio principal del proyecto. Estos archivos contienen los puntos del catálogo y las consultas respectivamente, que son esenciales para el funcionamiento del algoritmo.

##Ejecución del Programa Principal##
- Una vez compilado, el usuario puede ejecutar el programa con el comando para  terminal bash:

./Tarea_1-EDA-Ruiz-Palavicino (Aqui se puede cambiar segun la carpeta en donde el usuario piensa ejecutar el programa)

- El programa comenzará a procesar los datos, aplicando el algoritmo de clustering con diferentes valores de k (8, 16, 32, 64, 128) y realizando búsquedas para diferentes valores de m (8, 16, 32, 64, 128). Durante la ejecución, mostrará en terminal el progreso de los cálculos y generará los archivos TXT necesarios para la visualización.

##Generación de Gráficos##
- Después de que el programa termine de ejecutarse, el usuario puede generar las visualizaciones ejecutando el script de Python, desde el terminal bash:

python graficos.py

- Este script leerá los archivos .txt generados y creará dos gráficos: uno mostrando la búsqueda sin clustering y otro mostrando la búsqueda con clustering, ambos seran generados y mostrados al usuario.

##Verificación de Resultados##
- Finalmente, el usuario puede verificar que todos los archivos se hayan generado correctamente: los gráficos PNG en la carpeta principal y las tablas de resultados mostradas en la terminal durante la ejecución del programa C++. Los resultados incluyen métricas como el número de comparaciones, tiempos de ejecución y errores promedio para cada configuración de parámetros.
