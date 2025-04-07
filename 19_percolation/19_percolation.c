//----------------------------------------------------------------------
// percolation.c
//----------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_N 100

// Recursive function to update full sites from open sites
void _flow(bool isOpen[MAX_N][MAX_N], bool isFull[MAX_N][MAX_N], int n, int i, int j) {
    if (i < 0 || i >= n || j < 0 || j >= n) return;
    if (!isOpen[i][j] || isFull[i][j]) return;
    isFull[i][j] = true;
    _flow(isOpen, isFull, n, i + 1, j);  // Down
    _flow(isOpen, isFull, n, i, j + 1);  // Right
    _flow(isOpen, isFull, n, i, j - 1);  // Left
    _flow(isOpen, isFull, n, i - 1, j);  // Up
}

// Compute the full sites from the open sites
void flow(bool isOpen[MAX_N][MAX_N], bool isFull[MAX_N][MAX_N], int n) {
    for (int j = 0; j < n; j++) {
        _flow(isOpen, isFull, n, 0, j);
    }
}

// Check if the system percolates
bool percolates(bool isFull[MAX_N][MAX_N], int n) {
    for (int j = 0; j < n; j++) {
        if (isFull[n - 1][j]) {
            return true;
        }
    }
    return false;
}

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

// Main function: Read open sites, compute full sites, and print the result
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
// gcc -o percolation percolation.c
// ./percolation < test5.txt
// ./percolation < test8.txt
