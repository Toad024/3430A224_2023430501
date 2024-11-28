#Proyecto Final - Alineamiento de Secuencias
##Autor
Este programa fue desarrollado por Emilio Fernando Vásquez Millar.
___
##Descripción del Programa
Este programa implementa el algoritmo de alineamiento global de secuencias Needleman-Wunsch utilizando programación dinámica, para comparar secuencias de ADN. 
El objetivo es encontrar el mejor alineamiento entre dos secuencias, teniendo en cuenta las penalizaciones por desajustes y espacios (gaps).

El programa permite al usuario ingresar dos secuencias, ya sea a partir de un ejemplo preestablecido, escribiéndolas manualmente o cargándolas desde archivos, ya sea .txt o .fna.
Luego realiza el alineamiento. El proceso incluye la visualización de una matriz de puntuación, el trazado diagonal del camino óptimo, y el alineamiento final con las secuencias de entrada.
___

##Funcionalidades
#####Visualización de la Matriz de Puntuación: 
Muestra la matriz con los valores de alineamiento calculados.

#####Trazado Diagonal del Camino Óptimo: 
Resalta el camino óptimo a través de la matriz mediante asteriscos.

#####Alineamiento Final: 
Muestra el alineamiento de las secuencias con líneas de secuencia ajustadas a un ancho determinado para su mejor visualización.

#####Cargar Secuencias desde Archivos: 
Permite leer secuencias desde archivos de texto.
Menú de Opciones

#####Secuencias de Ejemplo: 
Usa secuencias predeterminadas para el alineamiento.
Escribir Secuencias: Permite al usuario escribir sus propias secuencias.

#####Abrir Secuencias: 
Permite abrir secuencias desde archivos de texto.

#####Explicar Algoritmo: 
Muestra una breve explicación del algoritmo de Needleman-Wunsch.

#####About: 
Información sobre el programa y el autor.

#####Salir: 
Cierra el programa.

#####Requisitos
Este programa requiere un compilador de C++ que soporte las características estándar del lenguaje (C++11 o superior).
___

##Uso
###Menú Principal
Al ejecutar el programa, se presentará un menú donde el usuario puede elegir entre las siguientes opciones:

1. Secuencias de ejemplo: Se utilizarán secuencias predefinidas para realizar el alineamiento.
2. Escribir secuencias: El usuario puede ingresar sus propias secuencias.
3. Abrir secuencias: El usuario puede cargar secuencias desde archivos de texto.
4. Explicar algoritmo: Muestra una breve descripción del algoritmo de Needleman-Wunsch.
5. About: Información sobre el programa y su creador.
6. Salir: Sale del programa.

###Cargar Secuencias desde Archivos
####Si usted elige la opción 3 para importar archivos existen varios puntos a tener en cuenta para el correcto uso del programa.
##### - Los genes importados deben de contar únicamente con una secuencia dentro de su contenido.
#####- Al estar diseñado para recepcionar archivos de tipo .fna, la primera linea de estos (por lo general el nombre del gen), será ignorada para la correcta comparación y posterior alineamiento de sus aminoácidos.
#####- El programa está diseñado para secuencias relativamente cortas, por lo que exite un límite de 1000 carácteres por secuencia, es decir se pueden crear matrices de 1000x1000, osea la comparación de 2000 aminoácidos máximo (entre los 2 archivos seleccionados). 
#####- Si el contenido excede este parámetro, se tomarán los primeros 1000 carácteres que se encuentren de cada archivo (sin contar la primera linea).

Para el uso de la opción 3 se pedirá al usuario las rutas de dos archivos de texto que contienen las secuencias a alinear.
Por ejemplo, si el archivo se encuentra en la misma carpeta en la que se está ejecutando el código, entonces al pedirle la ruta, debemos poner simplemente el nombre del archivo a elegir.


####Submenú
SI se escoge la opción 1, 2 o 3, de manera automática se ejecutará el algoritmo de needleman wunsch y se creará la matriz de alineamiento con su contenido respectivo, para posteriormente revelarse un submenú en el cual habran 3 nuevas opciones.
1.- Mostrar Alineamiento Final
2.- Destacar Trazado Diagonal Optimo
3.- Volver al menú principal.

Estas opciones nos permite realizar el alineamiento final que nos muestra cómo quedan los aminoácidos una vez alineados. Y el print nuevamente de la matriz alineada, pero esta vez con su diagonal optima destacada por asteriscos, para una comoda visualizacíon (respectivamente).
___

##Implementación del Algoritmo
###1. Inicialización de la Matriz y Penalizaciones
La matriz de puntuación se construye de manera que su primera fila y columna están inicializadas con penalizaciones correspondientes a los "gaps" o espacios en las secuencias. Estos valores se asignan como sigue:

La primera fila es inicializada con valores decrecientes a partir de 0, con una penalización de -1 por cada posición que se avance en la secuencia A.
La primera columna sigue el mismo proceso, penalizando con un valor de -1 por cada espacio en la secuencia B.
Penalizaciones:
Coincidencia: Cuando dos caracteres son idénticos, se asigna una puntuación positiva (en este caso, 1).
Desajuste: Cuando los caracteres no coinciden, se asigna una puntuación negativa (en este caso, -1).
Gap (Espacio): Cada vez que se introduce un gap en una secuencia (por ejemplo, al alinear un carácter de la secuencia A con un espacio en la secuencia B), se aplica una penalización de -1 en las posiciones correspondientes de la matriz.
### 2. Cálculo de la Matriz de Alineamiento

Para llenar la matriz, en cada celda (i, j), se toman tres posibles valores:

#####Diagonal: 
Corresponde a la puntuación de la celda diagonal superior izquierda (i-1, j-1) más la puntuación de la coincidencia/desajuste entre los caracteres de las secuencias A y B en las posiciones i-1 y j-1, respectivamente.

#####Arriba: 
Corresponde a la puntuación de la celda de arriba (i-1, j) más la penalización por gap.

#####Izquierda: 
Corresponde a la puntuación de la celda a la izquierda (i, j-1) más la penalización por gap.

De estos tres valores, se selecciona el mayor. Este es el valor que se coloca en la celda actual. Este proceso asegura que se elige la mejor opción para alinear los caracteres de las dos secuencias, considerando las penalizaciones y las ganancias por coincidencia.

#####Decisión de Espacio:
El algoritmo de Needleman-Wunsch usa programación dinámica para tomar decisiones en cuanto al camino que se debe seguir, asegurando que el alineamiento sea el óptimo. Si el valor máximo proviene de la diagonal, significa que se ha encontrado una coincidencia o desajuste; si proviene de la celda superior o izquierda, significa que se ha insertado un gap.

###3. Reconstrucción del Alineamiento y Trazado de la Diagonal
Una vez que la matriz está llena, se reconstruye el alineamiento óptimo comenzando desde la celda en la esquina inferior derecha y rastreando hacia atrás hasta la esquina superior izquierda. Esto nos da el camino óptimo de alineamiento, que se destaca en la matriz. En este proceso, los espacios de gap se indican con guiones (-), mientras que las coincidencias y desajustes se representan con los caracteres de las secuencias correspondientes.

#####Resaltado de la Diagonal:
El trazado diagonal se refiere al camino de celdas que se eligen para reconstruir el alineamiento óptimo. Cada vez que se elige la celda diagonal, se marca con un asterisco (*) al imprimir la matriz, lo que facilita visualizar el camino tomado en la matriz de puntuación.
___
