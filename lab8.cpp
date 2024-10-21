#include <iostream>
#include <chrono>
#include <cstdlib> // Use of rand() and srand()
using namespace std;  

void selection(int A[], int N) { //Selection Method
    for (int I = 0; I < N - 1; I++) { //Go through the array
        int MENOR = A[I]; //A[I] = First element = 'MENOR' 
        int K = I; //K = INDEX of A = I
        for (int J = I + 1; J < N; J++) { //J = I+1, The buble will continue as long as J is lower than N, which is the total size of the array, and J+1(J++) is to move in the next element of the array in each interaction :)
            if (A[J] < MENOR) { //IF A[J] is lower than 'MENOR' then 
                MENOR = A[J]; // Now this will be the new value of 'MENOR'
                K = J;
            }}
        A[K] = A[I];
        A[I] = MENOR; //Now 'MENOR' is the first element of the array (A[I])
    }}

void printArray(int A[], int N) { //Function to print all the Array
    for (int i = 0; i < N; i++) {
        cout << A[i] << " ";
    }
    cout << endl;
}

void reduce(int A[], int INI, int FIN, int &POS) {
    int IZQ = INI, DER = FIN;
    POS = INI;
    bool BAND = true;
    
    while (BAND) { 
        while (A[POS] <= A[DER] && POS != DER) DER--;
        if (POS == DER) BAND = false; //If POS get to DER it means that there is no more elements to move and the loop is finished
        else { //Or the element of POS is changed with the one in DER
            swap(A[POS], A[DER]);
            POS = DER;
        }

        while (A[POS] >= A[IZQ] && POS != IZQ) IZQ++; //The same as above but this time with IZQ looking for the higher
        if (POS == IZQ) BAND = false; //If there is no other element higher then BAND will be 'FALSO' which means that the loop will be over.
        else {
            swap(A[POS], A[IZQ]);
            POS = IZQ;
        }}}

void quickSort(int A[], int N) {
    int PILAMENOR[N], PILAMAYOR[N]; //Stacks to save the 'limits' of the array
    int TOPE = 1;  //To set the actual position of the stacks
    PILAMENOR[TOPE] = 0;
    PILAMAYOR[TOPE] = N - 1;

    while (TOPE > 0) {
        int INI = PILAMENOR[TOPE]; //Initial index
        int FIN = PILAMAYOR[TOPE]; //Final index
        TOPE--;

        int POS;
        reduce(A, INI, FIN, POS);

        if (INI < POS - 1) {
            TOPE++;
            PILAMENOR[TOPE] = INI;
            PILAMAYOR[TOPE] = POS - 1;
        }
        if (FIN > POS + 1) {
            TOPE++;
            PILAMENOR[TOPE] = POS + 1;
            PILAMAYOR[TOPE] = FIN;
        }}}

int main(int argc, char *argv[]) {

    // Verifying that two arguments are provided: number of elements and "YES" (or anything else)
    if (argc < 3) {
        cout << "Usage: " << argv[0] << " <number_of_elements> <(Show Arrays?) YES/NO)>" << endl;   
        return 1;
    }

    int N = atoi(argv[1]); // First argument: number of elements
    bool showArray = string(argv[2]) == "YES"; // Second argument: "YES" or ""Anything"" to display or not display the arrays

    int A[N];

    if (N > 20) { // If number of elements is greater than 20, fill the array with random numbers
        for (int i = 0; i < N; i++) {
            A[i] = rand() % 10000 + 1; // Random numbers between 1 and 10000
        }
        cout << "\n ** Array generated automatically ** \n \n";
    } else { // If number of elements is 20 or less, ask the user to input them manually
        for (int i = 0; i < N; i++) {
            cout << "Insert the number '" << i+1 << "' of the array: \n";
            cin >> A[i];
        }}

    // Check if user wants to display the array
    if (showArray) {
        cout << "___________________________________________________\n";
        cout << "               Original Array: \n";
        cout << "___________________________________________________\n";
        printArray(A, N);
    }

    auto startsel = std::chrono::high_resolution_clock::now(); // Start timer for Selection Sort
    selection(A, N); // Perform Selection Sort
    auto endsel = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> durationsel = (endsel - startsel);

    // If "Show" is passed as argument, print the sorted array by Selection Sort
    if (showArray) {
        cout << "\n___________________________________________________\n";
        cout << "           Array in order of Selection: \n";
        cout << "___________________________________________________\n";
        printArray(A, N);
    }
    std::cout << "\n *** Selection Method finished in: " << durationsel.count() * 1000 << " milliseconds \n"<< std::endl;

    auto startqs = std::chrono::high_resolution_clock::now(); // Start timer for QuickSort
    quickSort(A, N); // Perform QuickSort
    auto endqs = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> durationqs = (endqs - startqs);

    // If "Show" is passed as argument, print the sorted array by QuickSort
    if (showArray) {
        cout << "___________________________________________________\n";
        cout << "           Array in order of QuickSort: \n";
        cout << "___________________________________________________\n";
        printArray(A, N);
    }
    std::cout << "\n *** QuickSort Method finished in: " << durationqs.count() * 1000 << " milliseconds \n"<< std::endl;
    
    return 0;
}
