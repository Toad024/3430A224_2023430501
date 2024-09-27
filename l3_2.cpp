#include <iostream>
#include <stack>
#include <string>
#include <vector>

using namespace std;

struct Container {
    int number;
    string company;

    Container(int num, string emp) : number(num), company(emp) {}
};

void mostrarPilas(const vector<stack<Container>>& stacks) {

    for (int i = 0; i < stacks.size(); i++) {
        cout << "Stack " << i + 1 << ": ";
        stack<Container> temp = stacks[i];

        while (!temp.empty()) {
            Container c = temp.top();
            cout << "[" << c.number << "/" << c.company << "] ";
            temp.pop();
        }
        cout << endl;
    }}

// Función para encontrar una stack con espacio disponible
int findFreeStack(const vector<stack<Container>>& stacks, int currentStack) {
    for (int i = 0; i < stacks.size(); i++) {
        if (i != currentStack && stacks[i].size() < 4) { // Se verifica que la stack no esté llena
            return i;
        }
    }
    return -1; // Si no hay espacio
}

void moveContainer(int number, const string& company, vector<stack<Container>>& stacks) {
    bool encontrado = false;
    for (int i = 0; i < stacks.size(); i++) {
        stack<Container> temp;
        while (!stacks[i].empty()) {
            Container c = stacks[i].top();
            if (c.number == number && c.company == company) {
                cout << "Taking off container [" << c.number << "/" << c.company << "] from the stack " << i + 1 << endl;
                stacks[i].pop();
                encontrado = true;
                break;
            } else {
                int nuevaPila = findFreeStack(stacks, i);
                if (nuevaPila == -1) {
                    cout << "Error: there's no enough space for te container [" << c.number << "/" << c.company << "]" << endl;
                    return;
                } else {
                    cout << "Moving container [" << c.number << "/" << c.company << "] from stack " << i + 1 << " to stack " << nuevaPila + 1 << endl;
                    stacks[nuevaPila].push(c);
                    stacks[i].pop();
                }}}

        if (encontrado)
            break;
    }

    if (!encontrado) {
        cout << "Container [" << number << "/" << company << "] not found." << endl;
    }}


int main() {
    int n, m;
    cout << "Insert how many containers you want to set: \n";
    cin >> n;
    cout << "Insert how many stocks you want to set: \n"; 
    cin >> m;

    vector<stack<Container>> stacks(m);

    for (int i = 0; i < n; i++) {
        int number;
        string company;
        int pilaIndex;
        cout << "Insert the number of the container: \n";
        cin >> number;
        cout <<"Insert the name of the company: \n";
        cin >> company;
        cout << "From stack 1 to " << m << ", where do you want to leave the container: \n";
        cin >> pilaIndex;
        pilaIndex--;
        stacks[pilaIndex].push(Container(number, company));
    }

    cout << "\n";
    cout << "Initial state: \n";
    mostrarPilas(stacks);

    int number;
    string company;
    cout << "Which container do you want to take \n";
    cout << "Insert their number: \n";
    cin >> number; 
    cout << "Insert the name of their company: \n";
    cin >> company;

    moveContainer(number, company, stacks);

    cout << "Final state: \n";
    mostrarPilas(stacks);

    return 0;
}
