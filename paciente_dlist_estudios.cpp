/*Escriba un programa en C++ que permita obtener algunos datos del espacio muestral
de pacientes que se maneja y se encuentra almacenado en la lista. Es de interés
poder conocer el promedio de edad y el promedio de peso del grupo presente
además del IMC de cada uno de los pacientes. Dentro de la función main debe
incorporar los ejemplos de pacientes y dejar en evidencia todas las funciones
desarrolladas.*/

#include <iostream>
#include <string>
using namespace std;

struct Patient {
  string name;
  int age;
  double weight;
  double height;

  Patient * next;
};

void deletePatient(Patient *&head, const string &name) {
  Patient * current = head;
  Patient * previous = nullptr;

  while (current != nullptr && current -> name != name) {
    previous = current;
    current = current -> next;
  }

  if (current != nullptr) {
    if (previous == nullptr) {
      head = current -> next;
    } else {
      previous -> next = current->next;
    }
    delete current;
  }}

void addPatient(Patient *&head, const string &name, int age, double weight , double height) {
  Patient * newPatient = new Patient();
  newPatient -> name = name; newPatient -> age = age;
  newPatient -> weight = weight;
  newPatient -> height = height;
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

double calculateAverageAge(const Patient *head) {
  const Patient * current = head;
  int ageSum = 0, patientsNumber = 0;

  while (current != nullptr) {
    ageSum = ageSum + current->age;
    patientsNumber += 1;
    current = current -> next;
  }

  int ageAverage = ageSum / patientsNumber;
  cout << "The average age of the patients is: " << ageAverage << endl;
  return ageAverage;
}

double calculateAverageWeight(const Patient *head) {
  const Patient * current = head;
  double weightSum = 0, patientsNumber = 0;

  while (current != nullptr) {
    weightSum = weightSum + current -> weight;
    patientsNumber += 1;
    current = current -> next;
  }

  double weightAverage = weightSum / patientsNumber;
  cout << "The average weight of the patients is: " << weightAverage << endl;
  return weightAverage;
}

double calculateAverageHeight (const Patient *head) {
  const Patient * current = head;
  double heightSum = 0, patientsNumber = 0;

  while (current != nullptr) {
    heightSum = heightSum + current -> height;
    patientsNumber += 1;
    current = current -> next;
  }

  double heightAverage = heightSum / patientsNumber;
  cout << "The average height of the patients is: " << heightAverage << endl;
  return heightAverage;
}

void calculateIMC(const Patient *head) {
  const Patient * current = head;
  double weight = 0, height = 0, imc = 0;

  while (current != nullptr) {
    weight = current -> weight;
    height = current -> height;
    imc = weight / (height * height);   

    cout << current -> name << "'s IMC is: " << imc << endl;
    current = current -> next;
  }}

int main() {
  Patient *head = nullptr;

  addPatient(head, "Devilman", 537, 208.9, 2.75);
  addPatient(head, "Akira", 18, 75.9, 1.75);
  addPatient(head, "Satan", 4543, 100.6, 2.73);
  addPatient(head, "Ryo", 18 , 66.6, 1.73);
  addPatient(head, "Miki", 18, 60.3, 1.58);
  addPatient(head, "Kaim", 20032, 6.500 , 5.24);
  addPatient(head, "Jenny", 4006, 99.9, 1.90);

  printPatient(head);
  cout << "\n";
  calculateAverageAge(head);
  calculateAverageWeight(head);
  calculateAverageHeight(head);
  cout << "\n";
  calculateIMC(head);

  while (head != nullptr) {
    Patient *temp = head;
    head = head->next;
    delete temp;
  }
  return 0;
}