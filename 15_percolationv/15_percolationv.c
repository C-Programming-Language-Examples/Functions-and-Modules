//----------------------------------------------------------------------
// percolationv.c
//----------------------------------------------------------------------

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAX_N 100

// Read a boolean matrix from standard input
void readBool2D(bool matrix[MAX_N][MAX_N], int *n) {
    scanf("%d", n);
    for (int i = 0; i < *n; i++) {
        for (int j = 0; j < *n; j++) {
            int val;
            scanf("%d", &val);
            matrix[i][j] = (val == 1);
        }
    }
}

// Print a boolean matrix to standard output
void printBool2D(bool matrix[MAX_N][MAX_N], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", matrix[i][j] ? 1 : 0);
        }
        printf("\n");
    }
}

// Compute the full sites from the open sites (vertical percolation)
void flow(bool isOpen[MAX_N][MAX_N], bool isFull[MAX_N][MAX_N], int n) {
    for (int j = 0; j < n; j++) {
        isFull[0][j] = isOpen[0][j];
    }
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (isOpen[i][j] && isFull[i-1][j]) {
                isFull[i][j] = true;
            }
        }
    }
}

// Check if the system percolates (if any site in the bottom row is full)
bool percolates(bool isFull[MAX_N][MAX_N], int n) {
    for (int j = 0; j < n; j++) {
        if (isFull[n-1][j]) {
            return true;
        }
    }
    return false;
}

// Main function: Read open sites from input, compute full sites, and print the result
int main() {
    int n;
    bool isOpen[MAX_N][MAX_N] = {false};
    bool isFull[MAX_N][MAX_N] = {false};

    readBool2D(isOpen, &n);
    flow(isOpen, isFull, n);
    printBool2D(isFull, n);
    printf("%s\n", percolates(isFull, n) ? "True" : "False");
    return 0;
}

//----------------------------------------------------------------------

// Compile and run:
// gcc -o percolationv percolationv.c
// ./percolationv < test5.txt
// ./percolationv < test8.txt
