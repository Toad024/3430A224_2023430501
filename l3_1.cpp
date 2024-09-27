#include <iostream>
#include <stack>

using namespace std;

int main() {
  stack<int> stack;
  int n, opcion, respuesta;

  cout << "Insert the number of elements for the stack: ";
  cin >> n;

  while (true) {
    cout << "________________________" << endl;
    cout << "         Menu       " << endl;
    cout << "1) Add (Push)." << endl;
    cout << "2) Delete (Pop)." << endl;
    cout << "3) Print stack." << endl;
    cout << "4) Exit." << endl;
    cout << "________________________" << endl;
    cin >> opcion;

    switch (opcion) {
    case 1: {
      if (stack.size() < n) {
        cout << "Inert a value to add: \n";
        cin >> respuesta;
        stack.push(respuesta);
        cout << "Element " << respuesta << "  to the stack.\n";
      } else {
        cout << "The stack is full. You can't add more elements.\n";
      }
      break;
    }
    case 2: {
      if (!stack.empty()) {
        cout << "Element " << stack.top() << " deleted from the stack.\n";
        stack.pop();
      } else {
        cout << "The stack is empty. You can't delete any element.\n";
      }
      break;
    }
    case 3: {
      if (!stack.empty()) {
        cout << "Elements in the stack: ";
        std::stack<int> temp = stack;
        while (!temp.empty()) {
          cout << temp.top() << " ";
          temp.pop();
        }
        cout << endl;
      } else {
        cout << "La stack está vacía.\n";
      }
      break;
    }
    case 4: {
      cout << "\n";
      return 0;
    }
    default:
      cout << "Unexpected error, Try again later.\n";
    }}

  return 0;
}