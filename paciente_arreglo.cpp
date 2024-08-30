/*Escriba un programa en C++ que permita almacenar la información de los pacientes
(estructura) en un arreglo. Dentro de la función main debe incorporar los ejemplos de
“pacientes” utilizados anteriormente, almacenarlos en el arreglo y entregar la
información de cada uno de ellos por la salida estándar.*/

#include <iostream>
using namespace std;

struct Patient {
  string name;
  int age;
  double weight;
  double height;

};

int main() {

  Patient patients[4];

  patients[0].name = "Watoncito Gordito";
  patients[0].age = 20;
  patients[0].weight = 110.9;
  patients[0].height = 1.70;

  patients[1].name = "Diego Riquelme";
  patients[1].age = 49;
  patients[1].weight = 76.7;
  patients[1].height = 1.82;

  patients[2].name = "Shushetoide Máximo";
  patients[2].age = 21;
  patients[2].weight = 88.8;
  patients[2].height = 1.74;

  patients[3].name = "Mamadisimo Bastardisimo";
  patients[3].age = 22;
  patients[3].weight = 90;
  patients[3].height = 1.80;  


  for (int e = 0; e < 5; ++e) {
    cout << "Name: " << patients[e].name << "\n";
    
    cout << "Age: " << patients[e].age << "\n";

    cout << "Weight: " << patients[e].weight << "Kilograms \n";

    cout << "Height: " << patients[e].height << "Meters \n";

    cout << "\n";
  }}
