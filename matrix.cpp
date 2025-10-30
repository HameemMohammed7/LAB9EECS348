/**
 * EECS 348 Lab 9: Matrix Operations
 * This program implements various matrix operations including addition, 
 * multiplication, diagonal sums, row/column swapping, and element updates.
 * Author: Hameem Mohammed - Assisted by Lab 1 code and Chatgpt for generation and verification.
 */

#include <iostream>    // For input/output operations
#include <fstream>     // For file input/output operations
#include <vector>      // For dynamic array implementation
#include <iomanip>     // For output formatting (setw)
#include <string>      // For string operations

using namespace std;

/**
 * Matrix class to represent and manipulate N×N matrices
 * Uses vector<vector<int>> for dynamic array storage as required
 */
class Matrix {
private:
    vector<vector<int>> data;  // 2D vector to store matrix elements
    int size;                  // Size of the N×N matrix

public:
    /**
     * Constructor: Initialize a matrix of size n×n
     * @param n: Size of the square matrix
     */
    Matrix(int n) : size(n) {
        // Resize vector to n×n and initialize all elements to 0
        data.resize(n, vector<int>(n, 0));
    }

    /**
     * Load matrix from file
     * Reads first integer N, then reads N×N matrix elements
     * @param filename: Name of the file containing matrix data
     * @return true if successful, false otherwise
     */
    bool loadFromFile(const string& filename) {
        ifstream file(filename);
        
        // Check if file opened successfully
        if (!file.is_open()) {
            cout << "Error: Could not open file " << filename << endl;
            return false;
        }

        int n;
        file >> n;  // Read matrix size from first line
        size = n;
        
        // Resize matrix to N×N
        data.resize(n, vector<int>(n, 0));

        // Read matrix elements row by row
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                file >> data[i][j];
            }
        }

        file.close();
        return true;
    }

    /**
     * Display matrix with proper formatting
     * Uses setw(3) to align columns for clean output
     * @param name: Label to display before the matrix
     */
    void display(const string& name = "Matrix") const {
        cout << name << ":" << endl;
        
        // Print each row
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                cout << setw(3) << data[i][j] << " ";  // setw(3) ensures aligned columns
            }
            cout << endl;
        }
        cout << endl;
    }

    /**
     * Get element at position (i, j)
     * @param i: Row index
     * @param j: Column index
     * @return Element at position (i, j)
     */
    int get(int i, int j) const {
        return data[i][j];
    }

    /**
     * Set element at position (i, j)
     * @param i: Row index
     * @param j: Column index
     * @param value: New value to set
     */
    void set(int i, int j, int value) {
        data[i][j] = value;
    }

    /**
     * Get matrix size
     * @return Size of the square matrix
     */
    int getSize() const {
        return size;
    }

    /**
     * Matrix addition: Adds two matrices element-wise
     * Result[i][j] = this[i][j] + other[i][j]
     * @param other: Matrix to add to this matrix
     * @return New matrix containing the sum
     */
    Matrix add(const Matrix& other) const {
        Matrix result(size);
        
        // Add corresponding elements
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                result.data[i][j] = data[i][j] + other.data[i][j];
            }
        }
        return result;
    }

    /**
     * Matrix multiplication: Standard matrix multiplication
     * Result[i][j] = Σ(this[i][k] * other[k][j]) for k = 0 to size-1
     * Algorithm follows standard matrix multiplication: https://www.mathsisfun.com/algebra/matrix-multiplying.html
     * @param other: Matrix to multiply with this matrix
     * @return New matrix containing the product
     */
    Matrix multiply(const Matrix& other) const {
        Matrix result(size);
        
        // Triple nested loop for matrix multiplication
        // For each element in result matrix
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                // Calculate dot product of row i and column j
                for (int k = 0; k < size; k++) {
                    result.data[i][j] += data[i][k] * other.data[k][j];
                }
            }
        }
        return result;
    }

    /**
     * Calculate sum of main diagonal elements
     * Main diagonal: (0,0), (1,1), (2,2), ..., (n-1,n-1)
     * @return Sum of elements on the main diagonal
     */
    int getMainDiagonalSum() const {
        int sum = 0;
        
        // Sum elements where row index equals column index
        for (int i = 0; i < size; i++) {
            sum += data[i][i];
        }
        return sum;
    }

    /**
     * Calculate sum of secondary diagonal elements
     * Secondary diagonal: (0,n-1), (1,n-2), ..., (n-1,0)
     * @return Sum of elements on the secondary diagonal
     */
    int getSecondaryDiagonalSum() const {
        int sum = 0;
        
        // Sum elements where row + col = size - 1
        for (int i = 0; i < size; i++) {
            sum += data[i][size - 1 - i];
        }
        return sum;
    }

    /**
     * Swap two rows in the matrix
     * Validates that both indices are within valid bounds (0 to size-1)
     * @param row1: First row index (0-based)
     * @param row2: Second row index (0-based)
     * @return true if successful, false if invalid indices
     */
    bool swapRows(int row1, int row2) {
        // Validate indices are within bounds
        if (row1 < 0 || row1 >= size || row2 < 0 || row2 >= size) {
            cout << "Error: Invalid row indices" << endl;
            return false;
        }
        
        // Swap elements column by column
        for (int j = 0; j < size; j++) {
            swap(data[row1][j], data[row2][j]);
        }
        return true;
    }

    /**
     * Swap two columns in the matrix
     * Validates that both indices are within valid bounds (0 to size-1)
     * @param col1: First column index (0-based)
     * @param col2: Second column index (0-based)
     * @return true if successful, false if invalid indices
     */
    bool swapColumns(int col1, int col2) {
        // Validate indices are within bounds
        if (col1 < 0 || col1 >= size || col2 < 0 || col2 >= size) {
            cout << "Error: Invalid column indices" << endl;
            return false;
        }
        
        // Swap elements row by row
        for (int i = 0; i < size; i++) {
            swap(data[i][col1], data[i][col2]);
        }
        return true;
    }

    /**
     * Update an element at a specific position
     * Validates that both indices are within valid bounds (0 to size-1)
     * @param row: Row index (0-based)
     * @param col: Column index (0-based)
     * @param value: New value to set at position (row, col)
     * @return true if successful, false if invalid indices
     */
    bool updateElement(int row, int col, int value) {
        // Validate indices are within bounds
        if (row < 0 || row >= size || col < 0 || col >= size) {
            cout << "Error: Invalid indices" << endl;
            return false;
        }
        
        // Update the element
        data[row][col] = value;
        return true;
    }
};

/**
 * Main function: Demonstrates all matrix operations
 * Implements all 7 required lab functions:
 * 1. Read values from file into matrices
 * 2. Add two matrices
 * 3. Multiply two matrices
 * 4. Get sum of diagonal elements
 * 5. Swap matrix rows
 * 6. Swap matrix columns
 * 7. Update matrix element
 */
int main() {
    string filename;
    cout << "Enter the filename containing matrix data: ";
    cin >> filename;

    // 1. Load first matrix from file
    Matrix matrix1(0);
    if (!matrix1.loadFromFile(filename)) {
        return 1;  // Exit if file loading failed
    }

    // Load second matrix from the same file (after first matrix)
    // The file format is: N, then N×N matrix 1, then N×N matrix 2
    ifstream file(filename);
    int n;
    file >> n;
    
    // Skip first matrix that was already loaded
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int temp;
            file >> temp;
        }
    }
    
    // Read second matrix
    Matrix matrix2(n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int value;
            file >> value;
            matrix2.set(i, j, value);
        }
    }
    file.close();

    // Display both loaded matrices
    matrix1.display("Matrix 1");
    matrix2.display("Matrix 2");

    // 2. Add two matrices and display the result
    // Requirements: Implement matrix addition function
    cout << "=== Matrix Addition ===" << endl;
    Matrix sum = matrix1.add(matrix2);
    sum.display("Sum");

    // 3. Multiply two matrices and display the result
    // Requirements: Implement matrix multiplication function
    // Algorithm reference: https://www.mathsisfun.com/algebra/matrix-multiplying.html
    cout << "=== Matrix Multiplication ===" << endl;
    Matrix product = matrix1.multiply(matrix2);
    product.display("Product");

    // 4. Get the sum of diagonal elements
    // Requirements: Calculate and display sum of main and secondary diagonals
    cout << "=== Diagonal Sums ===" << endl;
    cout << "Main diagonal sum of Matrix 1: " << matrix1.getMainDiagonalSum() << endl;
    cout << "Secondary diagonal sum of Matrix 1: " << matrix1.getSecondaryDiagonalSum() << endl;
    cout << "Main diagonal sum of Matrix 2: " << matrix2.getMainDiagonalSum() << endl;
    cout << "Secondary diagonal sum of Matrix 2: " << matrix2.getSecondaryDiagonalSum() << endl;
    cout << endl;

    // 5. Swap matrix rows and display the result
    // Requirements: Swap rows with indices starting at 0, validate bounds
    cout << "=== Row Swapping ===" << endl;
    Matrix matrix1_copy = matrix1;
    if (matrix1_copy.swapRows(0, 1)) {
        matrix1_copy.display("Matrix 1 after swapping rows 0 and 1");
    }

    // 6. Swap matrix columns and display the result
    // Requirements: Swap columns with indices starting at 0, validate bounds
    cout << "=== Column Swapping ===" << endl;
    Matrix matrix2_copy = matrix2;
    if (matrix2_copy.swapColumns(0, 1)) {
        matrix2_copy.display("Matrix 2 after swapping columns 0 and 1");
    }

    // 7. Update matrix element and display the result
    // Requirements: Update element at specific position (row, col, value), validate bounds
    cout << "=== Element Update ===" << endl;
    Matrix matrix1_update = matrix1;
    if (matrix1_update.updateElement(0, 0, 99)) {
        matrix1_update.display("Matrix 1 after updating element (0,0) to 99");
    }

    return 0;
}