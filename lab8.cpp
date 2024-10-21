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
        if (POS == DER) BAND = false;
        else {
            swap(A[POS], A[DER]);
            POS = DER;
        }

        while (A[POS] >= A[IZQ] && POS != IZQ) IZQ++;
        if (POS == IZQ) BAND = false;
        else {
            swap(A[POS], A[IZQ]);
            POS = IZQ;
        }}}

void quickSort(int A[], int N) {
    int PILAMENOR[N], PILAMAYOR[N];
    int TOPE = 1;
    PILAMENOR[TOPE] = 0;
    PILAMAYOR[TOPE] = N - 1;

    while (TOPE > 0) {
        int INI = PILAMENOR[TOPE];
        int FIN = PILAMAYOR[TOPE];
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

int main() {
    int N;

    cout << "How many elements have your array?: ";
    cin >> N;

    int A[N];

    if (N > 20){ //If the number inserted is higher than 20 then the content of the array will be random
        for (int i = 0; i < N; i++) {
            A[i] = rand() % 10000 + 1; //Random numbers between 10000 and 1
    }
    cout << "\n ** Array generated automatically ** \n \n";
    } else {
        for (int i = 0; i < N; i++){
            cout << "Insert the number '" << i+1 << "' of the array: \n";
            cin >> A[i];
        }}

    cout << "___________________________________________________\n";
    cout << "               Original Array: \n";
    cout << "___________________________________________________\n";
    printArray(A, N);


    auto startsel = std::chrono::high_resolution_clock::now(); //Start Selection Method with its respective timer
    selection(A, N); //With this the selection is made
    auto endsel = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> durationsel = (endsel-startsel);

    cout << "\n___________________________________________________\n";
    cout << "           Array in order of Selection: \n"; //Print of the array in Selection sort and the time it took
    cout << "___________________________________________________\n";
    printArray(A, N);
    std::cout << "\n *** Selection Mehtod finished in: " << durationsel.count() * 1000 << " milliseconds \n"<< std::endl;

    auto startqs = std::chrono::high_resolution_clock::now(); //Start Selection Method with its respective timer
    quickSort(A, N);
    auto endqs = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> durationqs = (endqs-startqs);

    cout << "___________________________________________________\n";
    cout << "           Array in order of QuickSort: \n"; //Print of the array in QuickSort and the time it took
    cout << "___________________________________________________\n";
    printArray(A, N);
    std::cout << "\n *** QuickSort Method finished in: " << durationqs.count() * 1000 << " milliseconds \n"<< std::endl;
    return 0;
}