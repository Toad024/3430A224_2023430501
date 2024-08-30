/*Escriba un programa en C++ que permita trabajar con la gestión de pacientes a través
de opciones interactivas. Es de interés poder incorporar un menú que permita a un
usuario navegar por las opciones que existen y utilizar todas las funcionalidades
(funciones desarrolladas). Además se debe sumar la posibilidad de realizar la carga
de información desde un file de texto plano o CSV.*/

#include <fstream>
#include <iostream>
#include <sstream>
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
      previous -> next = current -> next;
    }
    delete current;
  }
}

void addPatient(Patient *&head, const string &name, int age,
                     double height, double weight) {
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
    cout << current -> name << "\n" "Age: " << current -> age << " years old." "\n" 
    "Weight: "<< current -> weight << " kilos." "\n" 
    "Height: " << current -> height << " meters tall." "\n" << endl;
    current = current -> next;
  }}

double calculateAverageAge(const Patient *head) {
  const Patient *current = head;
  int sumaEdad = 0, patientsNumber = 0;

  while (current != nullptr) {
    sumaEdad = sumaEdad + current -> age;
    patientsNumber += 1;
    current = current -> next;
  }

  int ageAverage = sumaEdad / patientsNumber;
  cout << "The average age of the patients is: " << ageAverage << endl;
  return ageAverage;
}

double calculateAverageWeight(const Patient *head) {
  const Patient *current = head;
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

double calculateAverageHeight(const Patient *head) {
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

void calcularIMC(const Patient *head) {
  const Patient *current = head;
  double weight = 0, height = 0, imc = 0;

  while (current != nullptr) {
    weight = current -> weight;
    height = current -> height;
    imc = weight / (height * height);

    cout << current -> name << "'s IMC is: " << imc << endl;
    current = current -> next;
  }}

void saveFile(const Patient *head) {
  ofstream file("pacientes.csv");

  if (file.is_open()) {
    file << "Name, Age, Weight, Height \n";
    const Patient * current = head;

    while (current != nullptr) {
      file << current -> name << "," << current -> age << ","
      << current -> weight << "," << current -> height << "\n";
      current = current -> next;
    }
    file.close();
    cout << "Saved successfully as 'patients.csv" << endl;
  } else {
    cout << "Error, try again." << endl;
  }}

void readFile(Patient *&head) {
  ifstream file("patients.csv");
  string line;

  while (head != nullptr) {
    Patient * dum = head;
    head = head -> next;
    delete dum;
  }

  if (file.is_open()) {
    getline(file, line);
    while (getline(file, line)) {
      stringstream ss(line);
      string name;
      int age;
      double weight, height;

      getline(ss, name, ',');
      ss >> age;
      ss.ignore();
      ss >> weight;
      ss.ignore();
      ss >> height;

      addPatient(head, name, age, weight, height);
    }
    file.close();
    cout << "Loaded successfully from 'patients.csv'" << endl;
  } else {
    cout << "Couldn't load the file." << endl;
  }
}

int main() {
  Patient *head = nullptr;
  char respuesta;

  while (true) {
    cout << "_____________________________________________________" << endl;
    cout << "                     MENU                     " << endl;
    cout << "m) Add a Patient." << endl;
    cout << "p) Print Patients." << endl;
    cout << "d) Delete Patient." << endl;
    cout << "a) Calculate the average Age of the Patients." << endl;
    cout << "w) Calculate the average Weight of the Patients.." << endl;
    cout << "h) Calculate the average Height of the Patients.." << endl;
    cout << "i) Calculate the IMC of a Patient." << endl; //I know IMC = BMI, I just didn't wanted to mess it up lol
    cout << "s) Save as a '.csv' file." << endl;
    cout << "l) Load Patients from a file '.csv'" << endl;
    cout << "x) Exit." << endl;
    cout << "_____________________________________________________" << endl;
    cin >> respuesta;

    switch (respuesta) {

    case 'm': { //ADD (M -> MÁS)
      string name;
      int age;
      double height;
      double weight;
      cout << "Insert name: ";
      cin >> name;
      cout << "Insert age: ";
      cin >> age;
      cout << "Insert weight in Kg: ";
      cin >> weight;
      cout << "Insert height in meters (1.70):"; 
      cin >> height;
      addPatient(head, name, age, weight, height);
      break;
    }
    case 'p': { //PRINT
      printPatient(head);
      break;
    }
    case 'd': { //DELETE
      string name;
      cout << "Insert the name of the patient you want to delete: ";
      cin >> name;
      deletePatient(head, name);
      cout << name << " Has been successfully deleted." << endl;
      break;
    }
    case 'a': { //AGE AVERAGE
      calculateAverageAge(head);
      break;
    }
    case 'w': { //WEIGHT AVERAGE
      calculateAverageAge(head);
      break;
    }
    case 'h': { //HEIGHT AVEAGE
      calculateAverageAge(head);
      break;
    }
    case 'i': {  //IMC
      calcularIMC(head);
      break;
    }
    case 's': {  //SAVE
      saveFile(head);
      break;
    }
    case 'l': { //LOAD
      readFile(head);
      break;
    }
    case 'x': { //EXIT
      while (head != nullptr) {
        Patient *dum = head;
        head = head -> next;
        delete dum;
      }
      return 0;
    }
    default:
      cout << "Please, insert correctly your answer (use lowercase)" << endl;
    }
  }
}