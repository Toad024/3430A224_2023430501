#include <fstream>
#include <iostream>
#include <limits>
#include <string>
#include <vector>

using namespace std;

struct Node {
  int info;
  Node *left;
  Node *right;
};

Node *createNode(int data) {
  Node *newNode = new Node;
  newNode -> info = data;
  newNode -> left = nullptr;
  newNode -> right = nullptr;
  return newNode;
}

class Tree {
private:
  Node *root;

  Node *insertNode(Node *node, int data) {
    if (!node) {
      return createNode(data);
    }

    if (data < node -> info) {
      node -> left = insertNode(node -> left, data);} 
      else if (data > node -> info) {
      node -> right = insertNode(node -> right, data);}
    else {
      cout << "This number is already a Node.";
      cout << endl;
    }
    return node;
  }

  Node *Minimum(Node *node) {
    while (node -> left != nullptr) {
      node = node -> left;
    }
    return node;
  }

  Node *deleteNode(Node *node, int data) {
    if (!node) {
      return node;
    }

    if (data < node -> info) {
      node -> left = deleteNode(node -> left, data);
    } else if (data > node -> info) {
      node -> right = deleteNode(node -> right, data);} 
      else {
      if (node -> left == nullptr) {
        Node * temp = node -> right;
        delete node;
        return temp;} 
        else if (node -> right == nullptr) {
        Node * temp = node -> left;
        delete node;
        return temp;
      }
      Node *temp = Minimum(node -> right);
      node -> info = temp -> info;
      node -> right = deleteNode(node -> right, temp -> info);
    }
    return node;
  }

  void printPreOrder(Node *node) const {
    if (!node) {
      return;
    }
    cout << node -> info << " ";
    printPreOrder(node -> left);
    printPreOrder(node -> right);
  }

  void printInOrder(Node *node) const {
    if (!node) {
      return;
    }
    printInOrder(node -> left);
    cout << node -> info << " ";
    printInOrder(node -> right);
  }

  void printPostOrder(Node *node) const {
    if (!node) {
      return;
    }
    printPostOrder(node -> left);
    printPostOrder(node -> right);
    cout << node -> info << " ";
  }

  void traverse(Node *node, ofstream &fp) {
    if (node != nullptr) {
      if (node -> left != nullptr) {
        fp << "\"" << node -> info << "\" -> \"" << node -> left -> info << "\";"
           << endl;} 
           else {
        string cadena = "null" + to_string(node -> info) + "l";
        fp << "\"" << cadena << "\"[shape=point];" << endl;
        fp << "\"" << node -> info << "\" -> \"" << cadena << "\";" << endl;}

      if (node -> right != nullptr) {
        fp << "\"" << node -> info << "\" -> \"" << node -> right -> info << "\";"
           << endl;} 
           else {
        string cadena = "null" + to_string(node -> info) + "r";
        fp << "\"" << cadena << "\"[shape=point];" << endl;
        fp << "\"" << node -> info << "\" -> \"" << cadena << "\";" << endl;}

      traverse(node -> left, fp);
      traverse(node -> right, fp);
    }}

public: //to make the functions public
  Tree() : root(nullptr) {}
  void insert(int data) {
     root = insertNode(root, data); }

  void remove(int data) { root = deleteNode(root, data); }

  void modify(int antiguo, int nuevo) {
    remove(antiguo);
    insert(nuevo);}

  void printPreOrder() const {
    printPreOrder(root);
    cout << endl;}

  void printInOrder() const {
    printInOrder(root);
    cout << endl;}

  void printPostOrder() const {
    printPostOrder(root);
    cout << endl;}

  void visualize() {
    ofstream fp("grafo.dot");
    if (!fp.is_open()) {
      cerr << "Error al abrir el archivo tree.dot" << endl;
      return;
    }
    fp << "digraph G {" << endl;
    fp << "node [style=filled fillcolor=yellow];" << endl;
    traverse(root, fp);
    fp << "}" << endl;
    fp.close();

    system("dot -Tpng -o grafo.png grafo.dot");
    system("eog grafo.png");
  }};

int main() {
  Tree tree;

std::vector<int> valores = {120, 87, 140, 43, 99, 130, 22, 65, 93, 135, 56};

for (int valor : valores) {
    tree.insert(valor);
}

  while (true) {
    int respuesta = 0;
    cout << "__________________________________________________________________" << endl;
    cout << "1. Add Node" << endl;
    cout << "2. Modify Node" << endl;
    cout << "3. Delete Node" << endl;
    cout << "4. Print PreOrder" << endl;
    cout << "5. Print InOrder" << endl;
    cout << "6. Print PostOrder" << endl;
    cout << "7. Generate image of the tree (.png)" << endl;
    cout << "8. Exit" << endl;
    cout << "__________________________________________________________________" << endl;

    if (!(cin >> respuesta)) {
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      cout << "Please insert a integer value." << endl;
      continue;
    }

    switch (respuesta) {

    case 1: { //ADD
      int n = 0;
      cout << "Insert the number to add: ";
      if (!(cin >> n)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Please insert a integer value." << endl;
        continue;
      }
      tree.insert(n);
      cout << "\n¡The Node" << " -" << n << "- was successfully added to the Tree!" << endl;
      break;}
    
    case 2: { //MODIFY
      int n = 0;
      cout << "Insert the number you want to modify: ";
      if (!(cin >> n)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Please insert a integer value." << endl;
        continue;
      }
      int m = 0;
      cout << "Insert their new value: ";
      if (!(cin >> m)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Please insert a integer value." << endl;
        continue;
      }
      tree.modify(n, m);
      cout << "\n The Node: \n'" ;
      cout << n << "'" << endl;
      cout << " Has been successfully changed to: \n'"; 
      cout << m << "'" << endl ;
      break;}

    case 3: { //DELETE
      int n = 0;
      cout << "Insert the number you want to delete: ";
      if (!(cin >> n)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Please insert a integer value." << endl;
        continue;
      }
      tree.remove(n);
      cout << "\nThe Node -" << n << "- has been successfully deleted" << endl;
      break;}
    
    case 4: { //PREORDER
      cout << "-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_" << endl;
      cout << " PreOrder View: ";
      tree.printPreOrder();
      cout << "-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_" << endl;
      break;}

    case 5: { //INORDER
      cout << "-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_" << endl;
      cout << " InOrder View: ";
      tree.printInOrder();
      cout << "-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_" << endl;
      break;}

    case 6: { //POSTORDER
      cout << "-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_" << endl;
      cout << " PostOrder View: ";
      tree.printPostOrder();
      cout << "-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_" << endl;
      break;}

    case 7: { //PNG
      tree.visualize();
      break;}

    case 8: { //EXIT
      return 0;}
    default:
      cout << "Please insert a integer value" << endl;
    }}
  return 0;}