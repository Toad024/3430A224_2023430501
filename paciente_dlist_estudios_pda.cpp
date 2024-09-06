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
  double bmi;
  double a1c;
  int priority;
  Patient *next;
};

void calculateBMI(Patient *patient) {
  patient->bmi = patient->weight / (patient->height * patient->height);
}

void calculatePriority(Patient *patient) {
  patient->priority =
      (int)(patient->bmi * 2 + patient->a1c * 1.2 + patient->age * 0.8);
}

void addPatient(Patient *&head, const string &name, int age,
                double weight, double height, double a1c) {
  Patient *newPatient = new Patient();
  newPatient->name = name;
  newPatient->age = age;
  newPatient->weight = weight;
  newPatient->height = height;
  newPatient->a1c = a1c;
  calculateBMI(newPatient);
  calculatePriority(newPatient);
  newPatient->next = head;
  head = newPatient;
}

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
      previous->next = current->next;
    }
    delete current;
    cout << name << " has been successfully deleted." << endl;
  } else {
    cout << "Patient not found." << endl;
  }
}

void printPatients(const Patient *head) {
  const Patient *current = head;
  while (current != nullptr) {
    cout << "\n" << current->name << "\n"
         << "Age: " << current->age << " years old.\n"
         << "Weight: " << current->weight << " kilos.\n"
         << "Height: " << current->height << " meters tall.\n"
         << "BMI: " << current->bmi << "\n"
         << "A1C: " << current->a1c << "\n"
         << "Priority: " << current->priority << endl;
    current = current->next;
  }
}

double calculateAverageWeight(const Patient *head) {
  const Patient *current = head;
  double weightSum = 0;
  int patientCount = 0;

  while (current != nullptr) {
    weightSum += current->weight;
    patientCount++;
    current = current->next;
  }

  if (patientCount == 0)
    return 0;
  return weightSum / patientCount;
}

double calculateAverageHeight(const Patient *head) {
  const Patient *current = head;
  double heightSum = 0;
  int patientCount = 0;

  while (current != nullptr) {
    heightSum += current->height;
    patientCount++;
    current = current->next;
  }
  if (patientCount == 0)
    return 0;
  return heightSum / patientCount;
}

double calculateAverageAge(const Patient *head) {
  const Patient *current = head;
  int ageSum = 0;
  int patientCount = 0;

  while (current != nullptr) {
    ageSum += current->age;
    patientCount++;
    current = current->next;
  }

  if (patientCount == 0)
    return 0;
  return (double)ageSum / patientCount;
}

void searchByBMI(const Patient *head, double bmiMin, double bmiMax) {
  const Patient *current = head;
  while (current != nullptr) {
    if (current->bmi >= bmiMin && current->bmi <= bmiMax) {
      cout << current->name << " - BMI: " << current->bmi << endl;
    }
    current = current->next;
  }
}

void searchByA1C(const Patient *head, double a1cMin, double a1cMax) {
  const Patient *current = head;
  while (current != nullptr) {
    if (current->a1c >= a1cMin && current->a1c <= a1cMax) {
      cout << current->name << " - A1C: " << current->a1c << endl;
    }
    current = current->next;
  }
}

void saveToFile(const Patient *head) {
  ofstream file("patients.csv");
  if (file.is_open()) {
    file << "Name,Age,Weight,Height,BMI,A1C,Priority\n";
    const Patient *current = head;
    while (current != nullptr) {
      file << current->name << "," << current->age << ","
           << current->weight << "," << current->height << "," << current->bmi
           << "," << current->a1c << "," << current->priority << "\n";
      current = current->next;
    }
    file.close();
    cout << "Saved successfully as 'patients.csv'" << endl;
  } else {
    cout << "Error, try again." << endl;
  }
}

void readFromFile(Patient *&head) {
  ifstream file("patients.csv");
  string line;

  while (head != nullptr) {
    Patient *temp = head;
    head = head->next;
    delete temp;
  }

  if (file.is_open()) {
    getline(file, line); // Skip the first line
    while (getline(file, line)) {
      stringstream ss(line);
      string name;
      int age;
      double weight, height, bmi, a1c;
      int priority;

      getline(ss, name, ',');
      ss >> age;
      ss.ignore();
      ss >> weight;
      ss.ignore();
      ss >> height;
      ss.ignore();
      ss >> bmi;
      ss.ignore();
      ss >> a1c;
      ss.ignore();
      ss >> priority;

      addPatient(head, name, age, weight, height, a1c);
    }
    file.close();
    cout << "Loaded successfully from 'patients.csv'" << endl;
  } else {
    cout << "Couldn't load the file." << endl;
  }
}

void attendPriorityPatients(Patient *&head, int numPatients) {
  for (int i = 0; i < numPatients; i++) {
    if (head == nullptr) {
      cout << "No more patients in the waiting list." << endl;
      return;
    }

    Patient *maxPriority = head;
    Patient *current = head->next;
    Patient *prevMax = nullptr;
    Patient *prev = head;

    while (current != nullptr) {
      if (current->priority > maxPriority->priority) {
        maxPriority = current;
        prevMax = prev;
      }
      prev = current;
      current = current->next;
    }

    if (prevMax == nullptr) {
      head = head->next;
    } else {
      prevMax->next = maxPriority->next;
    }

    cout << "Attending to " << maxPriority->name
         << " (Priority: " << maxPriority->priority << ")" << endl;
    delete maxPriority;
  }
}

int main() {
  Patient *head = nullptr;
  char response;

  while (true) {
    cout << "_____________________________________________________" << endl;
    cout << "                     MENU                     " << endl;
    cout << "m) Add a Patient." << endl;
    cout << "p) Print Patients." << endl;
    cout << "d) Delete a Patient." << endl;
    cout << "w) Calculate the average Weight of the Patients." << endl;
    cout << "a) Calculate the average Age of the Patients." << endl;
    cout << "h) Calculate the average Height of the Patients." << endl;
    cout << "s) Save as a '.csv' file." << endl;
    cout << "l) Load Patients from a file '.csv'" << endl;
    cout << "b) Search by BMI." << endl;
    cout << "1) Search by A1C." << endl;
    cout << "n) Attend priority patients." << endl;
    cout << "x) Exit." << endl;
    cout << "_____________________________________________________" << endl;
    cin >> response;

    switch (response) {
      case 'm': { // ADD PATIENT
        string name;
        int age;
        double height, weight, a1c;
        cout << "Enter the name: ";
        cin >> name;
        cout << "Enter the age: ";
        cin >> age;
        cout << "Enter the weight in Kg: ";
        cin >> weight;
        cout << "Insert height in meters (1.70):"; 
        cin >> height;
        cout << "Enter the A1C: ";
        cin >> a1c;
        addPatient(head, name, age, weight, height, a1c);
        break;
      }
      case 'p': { // PRINT PATIENTS
        printPatients(head);
        break;
      }
      case 'd': { // DELETE PATIENT
        string name;
        cout << "Insert the name of the patient you want to delete: ";
        cin >> name;
        deletePatient(head, name);
        break;
      }
      case 'w': { // AVERAGE WEIGHT
        double weightSum = calculateAverageWeight(head);
        cout << "The average weight of the patients is: " << weightSum << " Kg" << endl;
        break;
      }
      case 'h': { // AVERAGE HEIGHT
        double heightSum = calculateAverageHeight(head);
        cout << "The average height of the patients is: " << heightSum << " meters" << endl;
        break;
      }
      case 'a': { // AVERAGE AGE
        double ageSum = calculateAverageAge(head); 
        cout << "The average age of the patients is: " << ageSum << " years" << endl;
        break;
      }
      case 's': { // SAVE
        saveToFile(head);
        break;
      }
      case 'l': { // LOAD
        readFromFile(head);
        break;
      }
      case 'b': { // BMI
        double bmiMin, bmiMax;
        cout << "Enter the minimum BMI: ";
        cin >> bmiMin;
        cout << "Enter the maximum BMI: ";
        cin >> bmiMax;
        searchByBMI(head, bmiMin, bmiMax);
        break;
      }
      case '1': { // A1C
        double a1cMin, a1cMax;
        cout << "Enter the minimum A1C: ";
        cin >> a1cMin;
        cout << "Enter the maximum A1C: ";
        cin >> a1cMax;
        searchByA1C(head, a1cMin, a1cMax);
        break;
      }
      case 'n': { // PRIORITY
        int numPatients;
        cout << "Enter the number of patients to attend: ";
        cin >> numPatients;
        attendPriorityPatients(head, numPatients);
        break;
      }
      case 'x': { // EXIT
        while (head != nullptr) {
          Patient *temp = head;
          head = head->next;
          delete temp;
        }
        return 0;
      }
      default:
        cout << "Please, insert correctly your answer (use lowercase)" << endl;
        break;
    }
  }
}
