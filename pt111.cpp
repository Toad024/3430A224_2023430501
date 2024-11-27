#include <iostream>
#include <vector>
#include <algorithm>

// Function to print the matrix
void printMatrix(const std::vector<std::vector<int>>& matrix) {
    for (const auto& row : matrix) {
        for (const auto& val : row) {
            std::cout << val << "\t";
        }
        std::cout << std::endl;
    }
}

int main() {
    // Sequences to align
    std::string seqA = "CAGCTA";
    std::string seqB = "CACATA";
    
    // Lengths of the sequences
    int lenA = seqA.length();
    int lenB = seqB.length();
    
    // Initialize the score matrix
    std::vector<std::vector<int>> matrix(lenB + 1, std::vector<int>(lenA + 1, 0));
    
    // Fill the first row and first column with penalties
    for (int i = 0; i <= lenA; ++i) {
        matrix[0][i] = -i;  // Gap penalty in row 0
    }
    
    for (int j = 0; j <= lenB; ++j) {
        matrix[j][0] = -j;  // Gap penalty in column 0
    }
    
    // Fill the matrix with scores for alignment
    for (int i = 1; i <= lenB; ++i) {
        for (int j = 1; j <= lenA; ++j) {
            int matchScore = (seqA[j-1] == seqB[i-1]) ? 1 : -1;  // +1 for a match, -1 for no match
            
            // Calculate possible values: diagonal, up, left
            int diagonal = matrix[i-1][j-1] + matchScore;
            int up = matrix[i-1][j] - 1;  // Gap penalty
            int left = matrix[i][j-1] - 1;  // Gap penalty
            
            // Take the maximum value between the three options
            matrix[i][j] = std::max({diagonal, up, left});
        }
    }
    
    // Print the resulting matrix
    std::cout << "Alignment matrix:" << std::endl;
    printMatrix(matrix);
    
    return 0;
}
