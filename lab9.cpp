#include <iostream>
#include <vector>
#include <list>

using namespace std;

const int TABLE_SIZE = 20;

// Hash function to map a key to an index in the table
int hashFunction(int key) {
    return key % TABLE_SIZE;
}

// Linear Probing: Resolves collisions by checking the next slot sequentially
int linearTest(vector<int>& table, int key, bool& collision) {
    int index = hashFunction(key);
    while (table[index] != -1) {
        collision = true;
        index = (index + 1) % TABLE_SIZE;
    }
    table[index] = key;
    return index;
}

// Quadratic Probing: Uses a quadratic function to resolve collisions
int quadraticTest(vector<int>& table, int key, bool& collision) {
    int index = hashFunction(key);
    int i = 1;
    while (table[index] != -1) {
        collision = true;
        index = (index + i * i) % TABLE_SIZE;
        i++;
    }
    table[index] = key;
    return index;
}

// Double Hashing: Uses a second hash function to determine the step size for resolving collisions
int doubleHashing(vector<int>& table, int key, bool& collision) {
    int index = hashFunction(key);
    int step = 7 - (key % 7);
    while (table[index] != -1) {
        collision = true;
        index = (index + step) % TABLE_SIZE;
    }
    table[index] = key;
    return index;
}

// Chaining: Uses linked lists to handle collisions at each index
void chaining(vector<list<int>>& table, int key) {
    int index = hashFunction(key);
    table[index].push_back(key);
}

// Insert a key into the hash table using the specified collision resolution method
void insertKey(vector<int>& table, vector<list<int>>& chainTable, int key, char method) {
    bool collision = false;
    int index;
    switch (method) {
        case 'L':
            index = linearTest(table, key, collision);
            cout << "\n_________________________________________________________\n";
            cout << "Inserted " << key << " at position " << index << " using Linear Test.\n" << endl; 
            break;
        case 'C':
            index = quadraticTest(table, key, collision);
            cout << "\n_________________________________________________________\n";
            cout << "Inserted " << key << " at position " << index << " using Quadratic Test.\n" << endl;
            break;
        case 'D':
            index = doubleHashing(table, key, collision);
            cout << "\n_________________________________________________________\n";
            cout << "Inserted " << key << " at position " << index << " using Double Hashing.\n" << endl;
            break;
        case 'E':
            chaining(chainTable, key);
            cout << "\n_________________________________________________________\n";
            cout << "Inserted " << key << " in the chain at position " << hashFunction(key) << ".\n" << endl;
            break;
        default:
            cout << "\nError in the execution of the program\n";
            cout << "Try ./'name' (L/C/D/E)\n \n";
            exit(1); // The program ends immediately if the user inserts a wrong parameter
    }
    if (collision) {
        cout << "Collision occurred. Final position: " << index << "\n";
    }

    // Print array contents
    cout << "Array contents: ";
    for (int i = 0; i < TABLE_SIZE; ++i) {
        if (table[i] != -1)
            cout << table[i] << " ";
        else
            cout << ". ";
    }
    cout << "\n";

    // Print linked list contents if chaining is used
    if (method == 'E') {
        cout << "Chaining contents: \n";
        for (int i = 0; i < TABLE_SIZE; ++i) {
            cout << i << ":";
            for (int val : chainTable[i]) {
                cout << " " << val;
            }
            cout << "\n";
        }
    }
}

// Search for a key in the hash table using the specified collision resolution method
void searchKey(const vector<int>& table, const vector<list<int>>& chainTable, int key, char method) {
    int index = hashFunction(key);
    bool collision = false;
    if (method == 'E') {
        for (int item : chainTable[index]) {
            if (item == key) {
                cout << "Found " << key << " in the chain at position " << index << ".\n";
                return;
            }
        }
    } else {
        int originalIndex = index, step = 0;
        while (table[index] != key) {
            collision = true;
            if (method == 'L') index = (index + 1) % TABLE_SIZE;
            else if (method == 'C') index = (index + step * step++) % TABLE_SIZE;
            else if (method == 'D') index = (index + (7 - (key % 7))) % TABLE_SIZE;
            if (index == originalIndex) break;
        }
        if (table[index] == key) {
            cout << "Found " << key << " at position " << index << ".\n";
            if (collision) {
                cout << "Collision occurred during search. Final position: " << index << "\n";
            }
            return;
        }
    }
    cout << key << " not found.\n";
    if (collision) {
        cout << "Collision occurred during search.\n";
    }
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cout << "Usage: ./hash {L|C|D|E}\n";
        return 1;
    }

    // Read the collision resolution method from the command line
    char method = argv[1][0];
    vector<int> table(TABLE_SIZE, -1); // Initialize hash table with -1 indicating empty slots
    vector<list<int>> chainTable(TABLE_SIZE); // Initialize table for chaining with lists

    vector<int> keys = {23, 42, 5, 66, 14, 43, 59, 81, 37, 49, 28, 55, 94, 80, 64};

    // Insert keys into the hash table using the chosen method
    for (int key : keys) {
        insertKey(table, chainTable, key, method);
    }

    // Prompt user to enter a key to search for in the table
    int searchKeyVal;
    cout << "Enter key to search: ";
    cin >> searchKeyVal;
    searchKey(table, chainTable, searchKeyVal, method);

    return 0;
}
