#include <fstream>
#include <iostream>
#include <limits>
#include <string>
#include <vector>

using namespace std;

struct Node {
    int info;
    int FE; // Factor de equilibrio
    Node* left;
    Node* right;
};

// Función para crear un nuevo nodo
Node* createNode(int data) {
    Node* newNode = new Node;
    newNode->info = data;
    newNode->FE = 0; // Inicializa el FE en 0
    newNode->left = nullptr;
    newNode->right = nullptr;
    return newNode;
}

class Tree {
private:
    Node* root;

    Node* insertNode(Node* node, int data) {
        if (!node) {
            return createNode(data);
        }

        if (data < node->info) {
            node->left = insertNode(node->left, data);
        } else if (data > node->info) {
            node->right = insertNode(node->right, data);
        } else {
            cout << "Este número ya es un nodo." << endl;
            return node;
        }

        // Actualizar FE
        updateFE(node);
        return node;
    }

    void updateFE(Node* node) {
        int leftHeight = height(node->left);
        int rightHeight = height(node->right);
        node->FE = rightHeight - leftHeight;
    }

    int height(Node* node) {
        if (!node) return 0;
        return 1 + max(height(node->left), height(node->right));
    }

    Node* deleteNode(Node* node, int data) {
        if (!node) return node;

        if (data < node->info) {
            node->left = deleteNode(node->left, data);
        } else if (data > node->info) {
            node->right = deleteNode(node->right, data);
        } else {
            if (!node->left) {
                Node* temp = node->right;
                delete node;
                return temp;
            } else if (!node->right) {
                Node* temp = node->left;
                delete node;
                return temp;
            }

            Node* temp = minimum(node->right);
            node->info = temp->info;
            node->right = deleteNode(node->right, temp->info);
        }

        updateFE(node);
        return node;
    }

    Node* minimum(Node* node) {
        while (node->left) {
            node = node->left;
        }
        return node;
    }

    void printInOrder(Node* node) const {
        if (!node) return;
        printInOrder(node->left);
        cout << node->info << " ";
        printInOrder(node->right);
    }

    void visualize(Node* node, ofstream& fp) {
        if (node) {
            if (node->left) {
                fp << "\"" << node->info << "\" -> \"" << node->left->info << "\";" << endl;
                visualize(node->left, fp);
            } else {
                fp << "\"" << node->info << "\" -> \"null" << node->info << "l\"[style=dashed];" << endl;
            }

            if (node->right) {
                fp << "\"" << node->info << "\" -> \"" << node->right->info << "\";" << endl;
                visualize(node->right, fp);
            } else {
                fp << "\"" << node->info << "\" -> \"null" << node->info << "r\"[style=dashed];" << endl;
            }
            fp << "\"" << node->info << "\" [label=\"" << node->info << "\\nFE: " << node->FE << "\"];" << endl;
        }
    }

public:
    Tree() : root(nullptr) {}

    void insert(int data) {
        root = insertNode(root, data);
    }

    void remove(int data) {
        root = deleteNode(root, data);
    }

    void modify(int oldVal, int newVal) {
        remove(oldVal);
        insert(newVal);
    }

    void printInOrder() const {
        printInOrder(root);
        cout << endl;
    }

    void visualize() {
        ofstream fp("grafo.txt");
        if (!fp.is_open()) {
            cerr << "Error al abrir el archivo grafo.txt" << endl;
            return;
        }
        fp << "digraph G {" << endl;
        visualize(root, fp);
        fp << "}" << endl;
        fp.close();

        system("dot -Tpng -o grafo.png grafo.txt");
        system("eog grafo.png");
    }
};

int main() {
    Tree tree;
    std::vector<int> valores = {120, 87, 140, 43, 99, 130, 22, 65, 93, 135, 56};

    for (int valor : valores) {
        tree.insert(valor);
    }

    while (true) {
        int respuesta = 0;
        cout << "__________________________________________________________________" << endl;
        cout << "1. Agregar Nodo" << endl;
        cout << "2. Modificar Nodo" << endl;
        cout << "3. Eliminar Nodo" << endl;
        cout << "4. Imprimir InOrder" << endl;
        cout << "5. Generar imagen del árbol (.png)" << endl;
        cout << "6. Salir" << endl;
        cout << "__________________________________________________________________" << endl;

        if (!(cin >> respuesta)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Por favor, inserte un valor entero." << endl;
            continue;
        }

        switch (respuesta) {
            case 1: { // Agregar
                int n = 0;
                cout << "Inserte el número a agregar: ";
                if (!(cin >> n)) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Por favor, inserte un valor entero." << endl;
                    continue;
                }
                tree.insert(n);
                cout << "\n¡El Nodo -" << n << "- se ha agregado exitosamente al Árbol!" << endl;
                break;
            }
            case 2: { // Modificar
                int n = 0;
                cout << "Inserte el número que desea modificar: ";
                if (!(cin >> n)) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Por favor, inserte un valor entero." << endl;
                    continue;
                }
                int m = 0;
                cout << "Inserte su nuevo valor: ";
                if (!(cin >> m)) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Por favor, inserte un valor entero." << endl;
                    continue;
                }
                tree.modify(n, m);
                cout << "\n El Nodo: \n'" << n << "' ha sido cambiado exitosamente a: \n'" << m << "'" << endl;
                break;
            }
            case 3: { // Eliminar
                int n = 0;
                cout << "Inserte el número que desea eliminar: ";
                if (!(cin >> n)) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Por favor, inserte un valor entero." << endl;
                    continue;
                }
                tree.remove(n);
                cout << "\nEl Nodo -" << n << "- ha sido eliminado exitosamente." << endl;
                break;
            }
            case 4: { // Imprimir InOrder
                cout << "-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_" << endl;
                cout << " Vista InOrder: ";
                tree.printInOrder();
                cout << "-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_" << endl;
                break;
            }
            case 5: { // Generar imagen
                tree.visualize();
                break;
            }
            case 6: { // Salir
                return 0;
            }
            default:
                cout << "Por favor, inserte un valor entero." << endl;
        }
    }
    return 0;
}