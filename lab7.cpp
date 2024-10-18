#include <iostream>
#include <climits>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <unistd.h>
using namespace std;

#define INF INT_MAX

// Declaración anticipada de printMenu
void printMenu();

class Graph {       //Se crea un grafo de N nodos, determinados por el usuario.
    int N;
    vector<vector<int>> graph;

public:
    Graph(int N) : N(N), graph(N, vector<int>(N, 0)) {}

    void addEdge(int from, int to, int weight) { //se añade la arista correspindiente
        if (from >= 0 && from < N && to >= 0 && to < N) { //verificación de nodos para correcto funcionamiento
            graph[from][to] = weight;
            graph[to][from] = weight;  // El grafo es no dirigido, por lo que se hace la conexión hacia ambos lados :)
            cout << "Conexión añadida exitosamente.\n";
        } else {
            cout << "Nodos inválidos. Deben estar entre 0 y " << N-1 << ".\n"; 
        }
    }

    int minKey(const vector<int>& key, const vector<bool>& mstSet) { //FUnción que encuentra el vértice con el peso mínimo
        int min = INF, min_index;
        for (int v = 0; v < N; v++) {
            if (!mstSet[v] && key[v] < min) {
                min = key[v];
                min_index = v;
            }
        }
        return min_index;
    }

    void primMST() {  //función para visualizar resultados
        vector<int> parent(N);
        vector<int> key(N, INF);
        vector<bool> mstSet(N, false);

        key[0] = 0;
        parent[0] = -1;

        vector<pair<int, int>> L;

        for (int count = 0; count < N - 1; count++) {
            int u = minKey(key, mstSet);
            mstSet[u] = true;

            for (int v = 0; v < N; v++) {
                if (graph[u][v] && !mstSet[v] && graph[u][v] < key[v]) {
                    parent[v] = u;
                    key[v] = graph[u][v];
                }
            }
        }

        for (int i = 1; i < N; i++) {
            L.push_back({parent[i], i});
        }

        printMST(parent);
        generateDotFileAndImage("original_graph", false);
        generateDotFileAndImage("minimum_cost_graph", true, L);
        printSetL(L);
    }

    void printMST(const vector<int>& parent) { //print del arbol de expansión mímima
        cout << "\nÁrbol de expansión mínima:\n";
        cout << "Arista \tPeso\n";
        for (int i = 1; i < N; i++) {
            cout << (char)('a' + parent[i]) << " - " << (char)('a' + i) << "\t" << graph[i][parent[i]] << "\n";
        }
    }

    void generateDotFileAndImage(const string& filename, bool isMinimumCost, const vector<pair<int, int>>& L = {}) {
        string dotFilename = filename + ".dot"; //función para generar las imagenes de los grafos (base y expansión mínima)
        ofstream dotFile(dotFilename);
        dotFile << "graph G {\n";
        dotFile << "graph [rankdir=LR]\n";
        dotFile << "node [style=filled fillcolor=\"#00ff005f\"]\n";

        for (int i = 0; i < N; i++) {
            for (int j = i + 1; j < N; j++) {
                if (graph[i][j] != 0) {
                    if (!isMinimumCost || (isMinimumCost && 
                        (find(L.begin(), L.end(), make_pair(i, j)) != L.end() || 
                         find(L.begin(), L.end(), make_pair(j, i)) != L.end()))) {
                        dotFile << (char)('a' + i) << " -- " << (char)('a' + j) << " [label=" << graph[i][j] << "];\n";
                    }
                }
            }
        }

        dotFile << "}\n";
        dotFile.close();
        cout << "Archivo DOT generado: " << dotFilename << endl;

        // Generar imagen usando Graphviz
        string command = "dot -Tpng " + dotFilename + " -o " + filename + ".png";
        int result = system(command.c_str());
        if (result == 0) {
            cout << "Imagen generada: " << filename << ".png" << endl;
        } else {
            cout << "Error al generar la imagen. Asegúrese de tener Graphviz instalado." << endl;
        }
    }

    void printSetL(const vector<pair<int, int>>& L) { //contiene los vertices del arbol en expresion mínima en 'L'
        cout << "\nContenido del conjunto L:\n";
        for (const auto& edge : L) {
            cout << (char)('a' + edge.first) << " - " << (char)('a' + edge.second) << "\n";
        }
    }

    void showImage(const string& filename) { //para abrir la imagen mediante EOG
        string command = "eog " + filename + ".png";
        int result = system(command.c_str());
        if (result != 0) {
            cout << "Error al abrir la imagen. Asegúrese de tener EOG (Eye of GNOME) instalado." << endl;
        }
    }
};

void printMenu() { //print del menú principal
    cout << "\n--- Menú ---\n";
    cout << "1) Agregar nodos y sus conexiones. \n";
    cout << "2) Ejecutar algoritmo de Prim. \n";
    cout << "3) Mostrar grafo original. \n";
    cout << "4) Mostrar árbol de expansión mínima. \n";
    cout << "5) Salir.  \n";
    cout << "Ingrese su opción: ";
}

int main() { //manejo de la interacción con usuario
    if (system("which dot > /dev/null 2>&1") != 0) {
        cout << "Error: Graphviz no está instalado. Por favor, instálelo con 'sudo apt-get install graphviz'." << endl;
        return 1;
    }

    if (system("which eog > /dev/null 2>&1") != 0) {
        cout << "Advertencia: EOG (Eye of GNOME) no está instalado. Por favor, instálelo con 'sudo apt-get install eog'." << endl;
        return 1; //verificaciónes correspondientes para ver si están instalados los componentes necesarios para ejecutar correctamente el código.
    }

    int N;
    cout << "Ingrese el número de nodos (N > 2): "; 
    cin >> N;

    if (N <= 2) {
        cout << "El número de nodos debe ser mayor que 2.\n";
        return 1;
    }

    Graph g(N);
    int option;

    do {
        printMenu();
        cin >> option;

        switch(option) { //opciones y acciones del menú
            case 1: {
                int from, to, weight;
                cout << "Ingrese nodo origen (de 0 a " << N-1 << "): ";
                cin >> from;
                cout << "Ingrese nodo destino (de 0 a " << N-1 << "): ";
                cin >> to;
                cout << "Ingrese peso de la conexión: ";
                cin >> weight;
                g.addEdge(from, to, weight);
                break;
            }
            case 2:
                g.primMST();
                break;
            case 3:
                g.showImage("original_graph");
                break;
            case 4:
                g.showImage("minimum_cost_graph");
                break;
            case 5:
                cout << "Saliendo del programa...\n";
                break;
            default:
                cout << "Opción inválida. Por favor, intente de nuevo.\n";
        }
    } while (option != 5);

    return 0;
}