/*Escriba un programa en C++ que permita almacenar la información de pacientes en
una estructura. Cada paciente debe contener como datos el nombre, edad, peso y
1altura. Dentro de la función main debe exponer tres ejemplos de “pacientes”
entregando la información de cada uno de ellos por la salida estándar.*/

#include <iostream>
#include <string>

using namespace std;

struct Patient {
    string name;
    int age;
    double weight;
    double height;
};

int main() {
    Patient Patient1 = {"Watoncito Gordito", 20, 110.9, 1.70};
    Patient Patient2 = {"Diego Riquelme", 49, 76.7, 1.75};
    Patient Patient3 = {"Shushetoide Máximo", 21, 88.8, 1.74};
    Patient Patient4 = {"Mamadisimo Bastardisimo", 22, 90, 1.80};
/*############################################################*/
    cout << "Info. Patient 1: " << endl;
    cout << "name: " << Patient1.name << endl;
    cout << "age: " << Patient1.age << " years" << endl;
    cout << "weight: " << Patient1.weight << " kg" << endl;
    cout << "height: " << Patient1.height << " m" << endl << endl;
/*############################################################*/
    cout << "Info. Patient 2: " << endl;
    cout << "name: " << Patient2.name << endl;
    cout << "age: " << Patient2.age << " years" << endl;
    cout << "weight: " << Patient2.weight << " kg" << endl;
    cout << "height: " << Patient2.height << " m" << endl << endl;
/*############################################################*/
    cout << "Info. Patient 3: " << endl;
    cout << "name: " << Patient3.name << endl;
    cout << "age: " << Patient3.age << " years" << endl;
    cout << "weight: " << Patient3.weight << " kg" << endl;
    cout << "height: " << Patient3.height << " m" << endl << endl;
/*############################################################*/
    cout << "Info. Patient 4: " << endl;
    cout << "name: " << Patient3.name << endl;
    cout << "age: " << Patient3.age << " years" << endl;
    cout << "weight: " << Patient3.weight << " kg" << endl;
    cout << "height: " << Patient3.height << " m" << endl << endl;
    return 0;

}