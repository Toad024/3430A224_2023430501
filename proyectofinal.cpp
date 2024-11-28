#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <sstream>
#include <stdexcept>
#include <fstream> 

// Función para imprimir la matriz sin asteriscos (solo los valores)
void printMatrix(const std::vector<std::vector<int>>& matrix) {
    for (const auto& row : matrix) {
        for (int val : row) {
            std::cout << val << "\t";
        }
        std::cout << std::endl;
    }
}

// Función para imprimir la matriz con trazado (destacando el camino óptimo)
void printMatrixWithPath(const std::vector<std::vector<int>>& matrix, const std::vector<std::pair<int, int>>& path) {
    for (int i = 0; i < matrix.size(); ++i) {
        for (int j = 0; j < matrix[i].size(); ++j) {
            if (std::find(path.begin(), path.end(), std::make_pair(i, j)) != path.end()) {
                std::cout << "*" << matrix[i][j] << "*\t";
            } else {
                std::cout << matrix[i][j] << "\t";
            }
        }
        std::cout << std::endl;
    }
}

// Función para realizar el trazado del camino óptimo
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
        }
    }

    path.emplace_back(0, 0);
    std::reverse(path.begin(), path.end());
    return path;
}

// Función para reconstruir el alineamiento óptimo
void reconstructAlignment(const std::vector<std::vector<int>>& matrix, const std::string& seqA, const std::string& seqB, int gapPenalty) {
    std::string alignedA, alignedB;
    int i = seqB.length();
    int j = seqA.length();

    // Reconstruir el alineamiento óptimo
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
        }
    }

    // Imprimir el alineamiento de forma ordenada
    std::cout << "\nAlineamiento óptimo:\n" << std::endl;
    const int lineWidth = 80; // Cambia este valor según el ancho deseado
    size_t length = alignedA.length();

    for (size_t start = 0; start < length; start += lineWidth) {
        std::string segmentA = alignedA.substr(start, lineWidth);
        std::string segmentB = alignedB.substr(start, lineWidth);

        std::cout << "Secuencia A: " << segmentA << std::endl;
        std::cout << "Secuencia B: " << segmentB << std::endl;
        std::cout << std::endl;
    }
}



// Submenú 2: Alineamiento óptimo
void alignmentSubmenu(const std::vector<std::vector<int>>& matrix, const std::string& seqA, const std::string& seqB) {
    int subOption;
    do {
        std::cout << "\nSubmenú de alineamiento óptimo:" << std::endl;
        std::cout << "1. Hacer alineamiento óptimo" << std::endl;
        std::cout << "2. Salir al menú principal" << std::endl;
        std::cout << "Selecciona una opción (1-2): ";
        std::cin >> subOption;

        switch (subOption) {
            case 1:
                reconstructAlignment(matrix, seqA, seqB, -1);
                break;
            case 2:
                std::cout << "Volviendo al menú principal..." << std::endl;
                break;
            default:
                std::cout << "Opción no válida. Intenta de nuevo." << std::endl;
        }
    } while (subOption != 2);
}

// Submenú 1: Destacar trazado diagonal y alineamiento óptimo
void traceMatrixSubmenu(const std::vector<std::vector<int>>& matrix, const std::string& seqA, const std::string& seqB) {
    int subOption;
    do {
        std::cout << "\nSubmenú de trazado diagonal y alineamiento óptimo:" << std::endl;
        std::cout << "1. Mostrar alineamiento óptimo" << std::endl;
        std::cout << "2. Destacar trazado diagonal" << std::endl;
        std::cout << "3. Salir al menú principal" << std::endl;
        std::cout << "Selecciona una opción (1-3): ";
        std::cin >> subOption;

        switch (subOption) {
            case 1: {
                int gapPenalty = -1; // Ajustar el valor del gap si es necesario
                reconstructAlignment(matrix, seqA, seqB, gapPenalty);
                break;
            }
            case 2: {
                auto path = tracePath(matrix, seqA, seqB);
                std::cout << "\nMatriz con trazado destacado:" << std::endl;
                printMatrixWithPath(matrix, path);
                break;
            }
            case 3:
                std::cout << "Volviendo al menú principal..." << std::endl;
                break;
            default:
                std::cout << "Opción no válida. Intenta de nuevo." << std::endl;
        }
    } while (subOption != 3);
}



// Función principal para gestionar alineamientos
void alignSequences(std::string seqA, std::string seqB) {
    const int MAX_SIZE = 1000;

    // Truncar las secuencias si exceden el tamaño máximo permitido
    if (seqA.length() > MAX_SIZE) {
        seqA = seqA.substr(0, MAX_SIZE);
        std::cout << "Advertencia: La secuencia A fue truncada a " << MAX_SIZE << " caracteres." << std::endl;
    }
    if (seqB.length() > MAX_SIZE) {
        seqB = seqB.substr(0, MAX_SIZE);
        std::cout << "Advertencia: La secuencia B fue truncada a " << MAX_SIZE << " caracteres." << std::endl;
    }

    int lenA = seqA.length();
    int lenB = seqB.length();

    // Crear la matriz con las dimensiones dadas
    std::vector<std::vector<int>> matrix(lenB + 1, std::vector<int>(lenA + 1, 0));

    // Inicializar la primera fila y columna
    for (int i = 0; i <= lenA; ++i) matrix[0][i] = -i;
    for (int j = 0; j <= lenB; ++j) matrix[j][0] = -j;

    // Llenar la matriz con el algoritmo de Needleman-Wunsch
    for (int i = 1; i <= lenB; ++i) {
        for (int j = 1; j <= lenA; ++j) {
            int matchScore = (seqA[j - 1] == seqB[i - 1]) ? 1 : -1;
            int diagonal = matrix[i - 1][j - 1] + matchScore;
            int up = matrix[i - 1][j] - 1;
            int left = matrix[i][j - 1] - 1;
            matrix[i][j] = std::max({diagonal, up, left});
        }
    }

    // Imprimir la matriz solo si es necesario
    std::cout << "Matriz de alineamiento calculada:" << std::endl;
    printMatrix(matrix);

    // Submenú para trazado y alineamiento
    traceMatrixSubmenu(matrix, seqA, seqB);
}



// Función para leer una secuencia desde un archivo
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
            firstLine = false; // Ignorar la primera línea
            continue;   
        }
        content += line; // Agregar el resto del contenido
    }

    file.close();

    // Eliminar saltos de línea y caracteres de retorno de carro
    content.erase(std::remove(content.begin(), content.end(), '\n'), content.end());
    content.erase(std::remove(content.begin(), content.end(), '\r'), content.end());

    return content;
}


// Opción 3: Abrir secuencias desde archivos
void openSequences() {
    std::string fileA, fileB;
    std::string seqA, seqB;

    try {
        std::cout << "Ingresa la ruta del archivo para la Secuencia A: ";
        std::cin >> fileA;
        seqA = readSequenceFromFile(fileA);

        std::cout << "Ingresa la ruta del archivo para la Secuencia B: ";
        std::cin >> fileB;
        seqB = readSequenceFromFile(fileB);

        // Aquí las secuencias están cargadas pero no se imprimen.
        alignSequences(seqA, seqB);

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        std::cout << "Volviendo al menú principal..." << std::endl;
    }
}

// Menú principal
int main() {
    int option;

    do {
        std::cout << "\nMenú de opciones:\n";
        std::cout << "1. Secuencias de ejemplo\n";
        std::cout << "2. Escribir secuencias\n";
        std::cout << "3. Abrir secuencias\n";
        std::cout << "4. Explicar algoritmo\n";
        std::cout << "5. About\n";
        std::cout << "6. Salir\n";
        std::cout << "Selecciona una opción (1-6): ";
        std::cin >> option;

        switch (option) {
            case 1:
                alignSequences("GACATAC", "TATGACA");
                break;
            case 2: {
                std::string seqA, seqB;
                std::cout << "Escribe la secuencia A: ";
                std::cin >> seqA;
                std::cout << "Escribe la secuencia B: ";
                std::cin >> seqB;
                alignSequences(seqA, seqB);
                break;
            }
            case 3:
                openSequences();
                break;
            case 4:
                std::cout << "\nEl algoritmo de Needleman-Wunsch es un enfoque de programación dinámica utilizado para realizar un alineamiento global de dos secuencias,\n" << 
                "(por ejemplo, secuencias de ADN, ARN o proteínas)" << ".\nEste algoritmo optimiza el proceso de encontrar el mejor alineamiento posible entre las dos secuencias," << 
                "\nconsiderando penalizaciones por desajustes y gaps (espacios)." << std::endl;
                break;
            case 5:
                std::cout << "\n Programa desarrollado por Emilio Fernando Vásquez Millar.\n" << 
                "Este programa permite al usuario realizar alineamientos globales de secuencias biológicas, visualizando las matrices de puntuación y el trazado del camino óptimo. \n" <<
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
