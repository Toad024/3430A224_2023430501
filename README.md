HASH TABLE WITH COLLISION RESOLUTION METHODS

Author: Emilio Fernando Vásquez Millar

DESCRIPTION

This program implements four collision resolution methods for a hash table: Linear Probing, Quadratic Probing, Double Hashing, and Chaining. It allows the user to input keys, which are then inserted and searched using the specified method. The method of collision resolution is determined at runtime by a command-line parameter.

FEATURES

Data Input: The program inserts a predefined set of keys into a hash table of 20 elements.

Collision Resolution:
Linear Probing (L): Resolves collisions by checking the next slot sequentially.
Quadratic Probing (C): Uses a quadratic function to find the next slot.
Double Hashing (D): Uses a second hash function to determine the step size for resolving collisions.
Chaining (E): Uses linked lists to handle collisions at each index.

Insertion and Search:
Prints the array contents and linked list (if chaining is used) after each insertion.
Indicates where collisions occurred and the final displacement during both insertion and search.

USAGE

Compile the program with a compatible C++ compiler.

To run the program insert:./hashing L/C/D/E
- L for Linear Probing
- C for Quadratic Probing
- D for Double Hashing
- E for Chaining

Enter the key you want to search when prompted.

Example Output
./hashing L

no notes this time lul
