#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <sstream>
#include <stdexcept>
#include <fstream> 

//Generación de la Matriz Alineada con un Archivo.dot 
void generateDotFileMatrix(const std::vector<std::vector<int>>& matrix, const std::vector<std::pair<int, int>>& path, int imageCountM) {
    std::ofstream dotFile("MatrizAlineada" + std::to_string(imageCountM) + ".dot");
    if (!dotFile) {
        std::cerr << "No se pudo crear el archivo .dot" << std::endl;
        return;
    }

    dotFile << "graph grid" << std::endl;
    dotFile << "{" << std::endl;
    dotFile << "    fontname=\"Helvetica,Arial,sans-serif\"" << std::endl;
    dotFile << "    node [fontname=\"Helvetica,Arial,sans-serif\"]" << std::endl;
    dotFile << "    edge [fontname=\"Helvetica,Arial,sans-serif\"]" << std::endl;
    dotFile << "    layout=dot" << std::endl;
    dotFile << "    label=\"Matriz de Aineamiento Needleman-Wunsch\"" << std::endl;
    dotFile << "    labelloc = \"t\"" << std::endl;
    dotFile << "    node [shape=plaintext]" << std::endl;

    // Imprimir nodos con las celdas de la matriz
    for (int i = 0; i < matrix.size(); ++i) {
        for (int j = 0; j < matrix[i].size(); ++j) {
            dotFile << "    " << char('A' + i) << j << " [label=\"" << matrix[i][j] << "\"];" << std::endl;
        }}

    // Crear las aristas para conectar los nodos en el formato de la matriz (solo una vez)
    for (int i = 0; i < matrix.size(); ++i) {
        for (int j = 0; j < matrix[i].size(); ++j) {
            if (j + 1 < matrix[i].size()) {
                dotFile << "    " << char('A' + i) << j << " -- " << char('A' + i) << (j + 1) << " [len=1.00];" << std::endl;
            }
            if (i + 1 < matrix.size()) {
                dotFile << "    " << char('A' + i) << j << " -- " << char('A' + (i + 1)) << j << " [len=1.00];" << std::endl;
            }}}

    // Agregar restricciones de rango para cada fila
    for (int i = 0; i < matrix.size(); ++i) {
        dotFile << "    {rank=same;";
        for (int j = 0; j < matrix[i].size(); ++j) {
            dotFile << char('A' + i) << j;
            if (j < matrix[i].size() - 1) {
                dotFile << ";";
            }
        }
        dotFile << "};" << std::endl;
    }

    dotFile << "}" << std::endl;
    dotFile.close();  
}
//SUBMENÚ - Opción 4: Función para generar la imagen .png de la Matriz Alineada 
void generatePngImageMatrix(int imageCountM) {
    //Usamos el comando de sistema para ejecutar Graphviz y generar la imagen con un nombre único (Para poder crear varias imagenes sin que se solapen)
    std::string command = "dot -Tpng MatrizAlineada" + std::to_string(imageCountM) + ".dot -o MatrizAlineada" + std::to_string(imageCountM) + ".png";
    int result = system(command.c_str());

    if (result == 0) {
        std::cout << "\n-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-\n" << std::endl;
        std::cout << "  * * * Imagen generada exitosamente como 'MatrizAlineada" << imageCountM << ".png'. * * *" << std::endl;
        std::cout << "\n-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-\n" << std::endl;
    } else {
        std::cerr << "Error al generar la imagen con Graphviz." << std::endl;
    }}


//Generación de la Diagonal Trazada con un Archivo.dot 
void generateDotFileDiagonal(const std::vector<std::vector<int>>& matrix, const std::vector<std::pair<int, int>>& path, int imageCountD) {
    std::ofstream dotFile("MatrizDiagonalTrazada" + std::to_string(imageCountD) + ".dot");
    if (!dotFile) {
        std::cerr << "No se pudo crear el archivo .dot" << std::endl;
        return;
    }

    dotFile << "digraph G {" << std::endl;
    dotFile << "rankdir=LR;" << std::endl; 

    //Crear los nodos
    for (const auto& cell : path) {
        dotFile << "  node" << cell.first << "_" << cell.second << " [label=\"" 
                << matrix[cell.first][cell.second] << "\", shape=circle];" << std::endl;
    }

    //Crear las aristas
    for (size_t i = 1; i < path.size(); ++i) {
        dotFile << "  node" << path[i].first << "_" << path[i].second << " -> "
                << "node" << path[i - 1].first << "_" << path[i - 1].second << ";" << std::endl;
    }

    dotFile << "}" << std::endl;
    dotFile.close();
}

//SUBMENÚ - Opción 3: Función para generar la imagen .png del Trazado Diagonal de la Matriz
void generatePngImageDiagonal(int imageCountD) {
    //Usamos el comando de sistema para ejecutar Graphviz y generar la imagen con un nombre único (Para poder crear varias imagenes sin que se solapen)
    std::string command = "dot -Tpng MatrizDiagonalTrazada" + std::to_string(imageCountD) + ".dot -o MatrizDiagonalTrazada" + std::to_string(imageCountD) + ".png";
    int result = system(command.c_str());

    if (result == 0) {
        std::cout << "\n-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-\n" << std::endl;
        std::cout << "  * * * Imagen generada exitosamente como 'MatrizDiagonalTrazada" << imageCountD << ".png'. * * *" << std::endl;
        std::cout << "\n-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-\n" << std::endl;
    } else {
        std::cerr << "Error al generar la imagen con Graphviz." << std::endl;
    }}

//Función para imprimir la matriz (se realiza de manera automática a toda secuencia introducida, ya sea la de ejemplo, insertada o escrita).
void printMatrix(const std::vector<std::vector<int>>& matrix) {
    for (const auto& row : matrix) {
        for (int val : row) {
            std::cout << val << "\t";
        }
        std::cout << std::endl;
    }}

//SUBMENÚ - Opción 2: Función para imprimir la matriz con trazado diagonal destacado.
void printMatrixWithPath(const std::vector<std::vector<int>>& matrix, const std::vector<std::pair<int, int>>& path) {
    for (int i = 0; i < matrix.size(); ++i) {
        for (int j = 0; j < matrix[i].size(); ++j) {
            if (std::find(path.begin(), path.end(), std::make_pair(i, j)) != path.end()) {
                std::cout << "*" << matrix[i][j] << "*\t";
            } else {
                std::cout << matrix[i][j] << "\t";
            }}
        std::cout << std::endl;
    }}

//Función para realizar el trazado del camino óptimo
std::vector<std::pair<int, int>> tracePath(const std::vector<std::vector<int>>& matrix, const std::string& seqA, const std::string& seqB) {
    int i = seqB.length();
    int j = seqA.length();
    std::vector<std::pair<int, int>> path;

    while (i > 0 || j > 0) {
        path.emplace_back(i, j);
        if (i > 0 && j > 0 && matrix[i][j] == matrix[i-1][j-1] + ((seqA[j-1] == seqB[i-1]) ? 1 : -1)) {
            --i;
            --j;
        } else if (i > 0 && matrix[i][j] == matrix[i-1][j] - 1) {
            --i;
        } else {
            --j;
        }}

    path.emplace_back(0, 0);
    std::reverse(path.begin(), path.end());
    return path;
}

//SUBMENÚ - Opción 1: Función para reconstruir el alineamiento óptimo.
void reconstructAlignment(const std::vector<std::vector<int>>& matrix, const std::string& seqA, const std::string& seqB, int gapPenalty) {
    std::string alignedA, alignedB;
    int i = seqB.length();
    int j = seqA.length();

    //Reconstruir el alineamiento óptimo
    while (i > 0 || j > 0) {
        if (i > 0 && j > 0 && matrix[i][j] == matrix[i-1][j-1] + ((seqA[j-1] == seqB[i-1]) ? 1 : -1)) {
            alignedA = seqA[j-1] + alignedA;
            alignedB = seqB[i-1] + alignedB;
            --i;
            --j;
        } else if (i > 0 && matrix[i][j] == matrix[i-1][j] + gapPenalty) {
            alignedA = "-" + alignedA;
            alignedB = seqB[i-1] + alignedB;
            --i;
        } else {
            alignedA = seqA[j-1] + alignedA;
            alignedB = "-" + alignedB;
            --j;
        }}

    //Imprimir el alineamiento óptimo de manera ordenada
    std::cout << "\n_________________________________________________\n";
    std::cout << "\n                Alineamiento óptimo:" << std::endl;
    std::cout << "_________________________________________________\n";
    const int lineWidth = 80; // Este parámetro es del largo de las comparaciónes de las bases nitrogenadsa.
    size_t length = alignedA.length();

    for (size_t start = 0; start < length; start += lineWidth) {
        std::string segmentA = alignedA.substr(start, lineWidth);
        std::string segmentB = alignedB.substr(start, lineWidth);

        std::cout << "\n Secuencia A: " << segmentA;
        std::cout << "\n Secuencia B: " << segmentB;
    }}

bool imageCreated = false;

//SUBMENÚ 
//SUBMENÚ
void subMenu(const std::vector<std::vector<int>>& matrix, const std::string& seqA, const std::string& seqB) {
    int subOption;
    static int imageCountD = 1;  //Contador estático para generar nombres únicos de imágenes
    static int imageCountM = 1;
    static int imageCountA = 1;
    do {
        std::cout << "\n______________________________________________________________________\n";
        std::cout << "\n¿Qué acción desea realizar a continuación?: \n" << std::endl;
        std::cout << "1) Mostrar alineamiento óptimo" << std::endl;
        std::cout << "2) Destacar trazado diagonal" << std::endl;
        std::cout << "3) Generar imagen .png de la matriz trazada" << std::endl;
        std::cout << "4) Generar archivo .dot con la matriz" << std::endl; // Nueva opción para generar archivo .dot
        std::cout << "5) Volver al menú principal" << std::endl;
        std::cout << "Seleccione una opción (1-5): ";
        std::cin >> subOption;

        switch (subOption) {
            case 1: {
                int gapPenalty = -1; //Ajustar el valor del gap si es necesario
                reconstructAlignment(matrix, seqA, seqB, gapPenalty);
                break;
            }
            case 2: {
                auto path = tracePath(matrix, seqA, seqB);
                std::cout << "\n______________________________________________________________________\n";
                std::cout << "                Matriz con Trazado Diagonal Destacado:";
                std::cout << "\n______________________________________________________________________\n";
                printMatrixWithPath(matrix, path);
                break;
            }
            case 3: {
                // Generar el path de alineamiento
                auto path = tracePath(matrix, seqA, seqB);
                // Crear el archivo .dot
                std::cout << "\nGenerando archivo .dot ..." << std::endl;
                generateDotFileDiagonal(matrix, path, imageCountD);
                generatePngImageDiagonal(imageCountD);
                // Incrementar el contador de imágenes
                imageCountD++;
                break;
            }
            case 4: { // Nueva opción para generar archivo .dot
                // Crear archivo .dot con la matriz
                std::cout << "\nGenerando archivo .dot ..." << std::endl;
                generateDotFileMatrix(matrix, tracePath(matrix, seqA, seqB), imageCountM);
                generatePngImageMatrix(imageCountM);
                imageCountM++;
                break;

            case 5:
                std::cout << "\n^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n" << std::endl;
                std::cout << "         Volviendo al menú principal..." << std::endl;
                std::cout << "\n^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n" << std::endl;
                break;

            }
            default:
                std::cout << "Opción no válida. Intenta de nuevo." << std::endl;
        }
    } while (subOption != 5);
}

//Función principal para gestionar alineamientos
void alignSequences(std::string seqA, std::string seqB) {
    const int MAX_SIZE = 1000; //Máximo de carácteres a ser tomados por el programa.

    // Truncar las secuencias si exceden el tamaño máximo permitido
    if (seqA.length() > MAX_SIZE) {
        seqA = seqA.substr(0, MAX_SIZE);
        std::cout << "Advertencia: La secuencia A fue truncada a " << MAX_SIZE << " caracteres." << std::endl; //Por si la secuencia A pasan los 1000 carácteres
    }
    if (seqB.length() > MAX_SIZE) {
        seqB = seqB.substr(0, MAX_SIZE);
        std::cout << "Advertencia: La secuencia B fue truncada a " << MAX_SIZE << " caracteres." << std::endl; //Por si la secuencia B pasan los 1000 carácteres
    }

    int lenA = seqA.length();
    int lenB = seqB.length();

    //Crear la matriz con las dimensiones dadas
    std::vector<std::vector<int>> matrix(lenB + 1, std::vector<int>(lenA + 1, 0));

    //Inicializar la primera fila y columna
    for (int i = 0; i <= lenA; ++i) matrix[0][i] = -i;
    for (int j = 0; j <= lenB; ++j) matrix[j][0] = -j;

    //Llenar la matriz con el algoritmo de Needleman-Wunsch
    for (int i = 1; i <= lenB; ++i) {
        for (int j = 1; j <= lenA; ++j) {
            int matchScore = (seqA[j - 1] == seqB[i - 1]) ? 1 : -1;
            int diagonal = matrix[i - 1][j - 1] + matchScore;
            int up = matrix[i - 1][j] - 1;
            int left = matrix[i][j - 1] - 1;
            matrix[i][j] = std::max({diagonal, up, left});
        }}                       
    std::cout << "\n______________________________________________________________________\n";
    std::cout << "                   Matriz de Alineamiento Calculada:";
    std::cout << "\n______________________________________________________________________\n";

    printMatrix(matrix); //Printeo de las matrices (de manera automática)
    subMenu(matrix, seqA, seqB);
}

//Función para tomar y leer una secuencia desde un archivo
std::string readSequenceFromFile(const std::string& filePath) {
    std::ifstream file(filePath);
    if (!file.is_open()) {
        throw std::runtime_error("No se pudo abrir el archivo: " + filePath);
    }

    std::string content, line;
    bool firstLine = true;

    // Leer línea por línea
    while (std::getline(file, line)) {
        if (firstLine) {
            firstLine = false; //Ignorar la primera línea
            continue;   
        }
        content += line; //Agregar el resto del contenido
    }

    file.close();

    // Eliminar saltos de línea y caracteres de retorno
    content.erase(std::remove(content.begin(), content.end(), '\n'), content.end());
    content.erase(std::remove(content.begin(), content.end(), '\r'), content.end());

    return content;
}


//Función para abrir secuencias desde archivos
void openSequences() {
    std::string fileA, fileB;
    std::string seqA, seqB;

    try {
        //Ingreso de la secuenia A
        std::cout << "\n_______________________________________________\n";
        std::cout << "Ingresa la ruta del archivo para la Secuencia A: ";
        std::cout << "\n_______________________________________________\n";
        std::cin >> fileA;
        seqA = readSequenceFromFile(fileA);
        //Ingreso de la secuencia B
        std::cout << "\n_______________________________________________\n";
        std::cout << "Ingresa la ruta del archivo para la Secuencia B: ";
        std::cin >> fileB;
        seqB = readSequenceFromFile(fileB);

        // Aquí las secuencias están cargadas pero no se imprimen.
        alignSequences(seqA, seqB);

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        std::cout << "Volviendo al menú principal..." << std::endl;
    }}

//Menú principal
int main() {
    int option;

    do {
        std::cout << "_______________________________________________\n";
        std::cout << "\n                 Menú Principal:\n";
        std::cout << "_______________________________________________\n";
        std::cout << "1) Secuencias de ejemplo\n";
        std::cout << "2) Escribir secuencias\n";
        std::cout << "3) Abrir secuencias\n";
        std::cout << "4) Explicar algoritmo\n";
        std::cout << "5) About\n";
        std::cout << "6) Salir\n";
        std::cout << "Seleccione una opción (1-6): ";
        std::cout << "\n_______________________________________________\n";
        std::cin >> option;
        std::cout << "\n-_-_-_-_-_-_-_-_-_-_-_-_\n";

        switch (option) {
            case 1:
                alignSequences("GACATAC", "TATGACA");
                break;
            case 2: {
                std::string seqA, seqB;
                std::cout << "\n_______________________________________________\n";
                std::cout << "            Escribe la secuencia A: ";
                std::cout << "\n_______________________________________________\n";
                std::cin >> seqA;
                std::cout << "            Escribe la secuencia B: ";
                std::cout << "\n_______________________________________________\n";
                std::cin >> seqB;
                std::cout << "\n_______________________________________________\n";
                alignSequences(seqA, seqB);
                break;
            }
            case 3:
                openSequences();
                break;
            case 4:
                std::cout << "\nEl algoritmo de Needleman-Wunsch es un enfoque de programación dinámica utilizado para realizar un alineamiento global de dos secuencias,\n" << 
                "(por ejemplo, secuencias de ADN, ARN o proteínas)" << ".\nEste algoritmo optimiza el proceso de encontrar el mejor alineamiento posible entre las dos secuencias," << 
                "\nconsiderando puntajes, penalizaciones por desajustes y gaps (espacios)." << std::endl;
                break;
            case 5:
                std::cout << "\n    Programa desarrollado por Emilio Fernando Vásquez Millar.\n" << 
                "Este programa permite al usuario realizar alineamientos globales de secuencias biológicas de manera reducida y simplificada, visualizando las matrices de puntuación y el trazado del camino óptimo. \n" <<
                "Facilita la comparación de secuencias de ADN, ARN o proteínas, y es útil para estudios de similitud genética y evolución." << std::endl;
                break;
            case 6:
                std::cout << "Saliendo del programa." << std::endl;
                break;
            default:
                std::cout << "Opción no válida. Intenta de nuevo." << std::endl;
        }
    } while (option != 6);

    return 0;
}
