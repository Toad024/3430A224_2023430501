/*Escriba un programa en C++ que permita almacenar la información de pacientes en
una estructura para trabajar con una lista dinámica. Aquí no se puede utilizar la librería
list y debe realizar la actualización de la estructura, la inclusión de las funciones para
agregar, imprimir y eliminar. Dentro de la función main debe incorporar los ejemplos de
pacientes y dejar en evidencia todas las funciones desarrolladas.*/

#include <iostream>
#include <string>

using namespace std;

struct Patient {
  string name;
  int age;
  double weight;
  double height;

  Patient *next; 
};

void deletePatient(Patient *&head, const string &name) {
  Patient *current = head;
  Patient *previous = nullptr;

  while (current != nullptr && current->name != name) {
    previous = current;
    current = current->next;
  }

  if (current != nullptr) {
    if (previous == nullptr) {
      head = current->next;
    } else {
      previous -> next = current -> next;
    }
    delete current;
  }}

void addPatient(Patient *&head, const string &name, int age, double height, double weight) {
  Patient *newPatient = new Patient();
  newPatient -> name = name;
  newPatient -> age = age;
  newPatient -> height = height;
  newPatient -> weight = weight;
  newPatient -> next = head;
  head = newPatient;
}

void printPatient(const Patient *head) {
  const Patient * current = head;
  while (current != nullptr) {
    cout << current->name << "\n" "Age: " << current->age << " years old." "\n" 
    "Weight: "<< current->weight << " kilos." "\n" 
    "Height: " << current->height << " meters tall." "\n" << endl;
    current = current->next;
  }}

int main() {
  Patient *head = nullptr;

  addPatient(head, "Watoncito", 20, 110.9, 1.70);
  addPatient(head, "Diego", 49, 76.7, 1.82);
  addPatient(head, "Mamadisimo", 22, 90, 1.80);

  printPatient(head);
  deletePatient(head, "Diego");
  deletePatient(head, "Mamadisimo");

  cout << "(after delete)" << endl;
  cout << "\n";
  printPatient(head);

  while (head != nullptr) {
    Patient *temp = head;
    head = head->next;
    delete temp;
  }
  return 0;
}