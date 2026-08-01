#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

// Class to handle all Matrix operations and storage
class Matrix {
private:
    int rows;
    int cols;
    vector<vector<double>> data;

public:
    // Constructor to initialize matrix dimensions
    Matrix(int r, int c) : rows(r), cols(c), data(r, vector<double>(c, 0.0)) {}

    // Function to read matrix elements from user
    void input() {
        cout << "Enter elements row by row:\n";
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                cout << "Element [" << i + 1 << "][" << j + 1 << "]: ";
                while (!(cin >> data[i][j])) {
                    cout << "Invalid input. Enter a number: ";
                    cin.clear();
                    cin.ignore(1000, '\n');
                }
            }
        }
    }

    // Function to display matrix cleanly
    void display() const {
        for (int i = 0; i < rows; ++i) {
            cout << "[ ";
            for (int j = 0; j < cols; ++j) {
                cout << setw(8) << data[i][j] << " ";
            }
            cout << "]\n";
        }
    }

    // Addition Operation
    Matrix add(const Matrix& other) const {
        Matrix result(rows, cols);
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                result.data[i][j] = this->data[i][j] + other.data[i][j];
            }
        }
        return result;
    }

    // Subtraction Operation
    Matrix subtract(const Matrix& other) const {
        Matrix result(rows, cols);
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                result.data[i][j] = this->data[i][j] - other.data[i][j];
            }
        }
        return result;
    }

    // Multiplication Operation
    Matrix multiply(const Matrix& other) const {
        Matrix result(this->rows, other.cols);
        for (int i = 0; i < this->rows; ++i) {
            for (int j = 0; j < other.cols; ++j) {
                for (int k = 0; k < this->cols; ++k) {
                    result.data[i][j] += this->data[i][k] * other.data[k][j];
                }
            }
        }
        return result;
    }

    // Transpose Operation
    Matrix transpose() const {
        Matrix result(cols, rows);
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                result.data[j][i] = data[i][j];
            }
        }
        return result;
    }

    // Getters for dimensional validation
    int getRows() const { return rows; }
    int getCols() const { return cols; }
};

// Main interface handler
int main() {
    int choice;
    
    while (true) {
        cout << "\n===============================\n";
        cout << "       MATRIX CALCULATOR       \n";
        cout << "===============================\n";
        cout << "1. Add Matrices\n";
        cout << "2. Subtract Matrices\n";
        cout << "3. Multiply Matrices\n";
        cout << "4. Transpose Matrix\n";
        cout << "5. Exit\n";
        cout << "Enter your choice (1-5): ";
        cin >> choice;

        if (choice == 5) {
            cout << "Exiting calculator. Goodbye!\n";
            break;
        }

        if (choice < 1 || choice > 5) {
            cout << "Invalid choice! Please select between 1 and 5.\n";
            continue;
        }

        int r1, c1, r2, c2;

        if (choice == 4) { // Transpose only needs 1 matrix
            cout << "Enter rows and columns for the matrix: ";
            cin >> r1 >> c1;
            Matrix m(r1, c1);
            m.input();
            
            cout << "\nOriginal Matrix:\n";
            m.display();
            
            cout << "\nTransposed Matrix:\n";
            m.transpose().display();
        } 
        else { // Addition, Subtraction, Multiplication need 2 matrices
            cout << "Enter rows and columns for Matrix A: ";
            cin >> r1 >> c1;
            cout << "Enter rows and columns for Matrix B: ";
            cin >> r2 >> c2;

            // Mathematical rule validation before matrix allocation
            if ((choice == 1 || choice == 2) && (r1 != r2 || c1 != c2)) {
                cout << "Error: Matrices must have identical dimensions for addition/subtraction!\n";
                continue;
            }
            if (choice == 3 && c1 != r2) {
                cout << "Error: Matrix A columns must equal Matrix B rows for multiplication!\n";
                continue;
            }

            cout << "\n--- Matrix A ---\n";
            Matrix a(r1, c1);
            a.input();

            cout << "\n--- Matrix B ---\n";
            Matrix b(r2, c2);
            b.input();

            cout << "\nResult:\n";
            if (choice == 1) {
                a.add(b).display();
            } else if (choice == 2) {
                a.subtract(b).display();
            } else if (choice == 3) {
                a.multiply(b).display();
            }
        }
    }
    return 0;
}
