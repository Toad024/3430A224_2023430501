Array Sorting by the using of 'Selection' and 'QuickSort'
Author: Emilio Fernando Vásquez Millar
Description
This program implements two sorting methods: Selection and QuickSort. It allows the user to input a specific number of elements into an array if they are lower than 20, which are then sorted using both methods. 
If the user chooses more than 20 elements, the program will automatically generate random numbers to fill the array.

Features
Data Input: The user can enter the size of the array and the elements. If the size exceeds 20, random elements will be generated between 1 and 10000.
Sorting: Implements two sorting methods:
Selection Sort: An algorithm that selects the smallest element from the unsorted part in each iteration.
QuickSort: A more efficient algorithm, selecting a "pivot" and reordering the array around this pivot, leaving the lower numbers at the left and the higher on its right side.
Time Measurement: Measures and displays the time taken by each algorithm to sort the array in milliseconds.

Usage
Compile the program with a compatible C++ compiler.
Run the program.
Enter the number of elements you want in the array.
If you enter more than 20, random numbers will be generated automatically; otherwise, you will be prompted to input each number manually.
Observe the output of the original and sorted arrays, along with the time taken by each algorithm.
Example Output

How many elements have your array?: 25
Array generated automatically: 5 12 3 7 19 ...

Original Array: 5 12 3 7 19 ...

Array in order of Selection: 3 5 7 12 19 ...
Selection took X milliseconds

Array in order of QuickSort: 3 5 7 12 19 ...
QuickSort took Y milliseconds

Requirements
Compatible C++ compiler (e.g., g++, clang++)
Basic knowledge of C++ for code modification.

Notes
- Make sure to include #include <cstdlib> for using rand(). and #include <chrono> for the time management.
- The random array parameter (input a number higher than '20') can be changed in the 'if (N > 20){' located in main.
- You also can adjust the range of the random numbers by changing the parameters in 'rand() % 10000 + 1' located in main too.
