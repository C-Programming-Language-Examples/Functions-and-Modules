//----------------------------------------------------------------------
// estimate.c
//----------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define MAX_N 100

// Generate a random boolean matrix with given probability p
void generateRandomMatrix(bool matrix[MAX_N][MAX_N], int n, double p) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            matrix[i][j] = ((double)rand() / RAND_MAX) < p;
        }
    }
}

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

// Check if the system percolates (if any site in the bottom row is full)
bool percolates(bool isFull[MAX_N][MAX_N], int n) {
    for (int j = 0; j < n; j++) {
        if (isFull[n-1][j]) {
            return true;
        }
    }
    return false;
}

// Compute the full sites from the open sites
void flow(bool isOpen[MAX_N][MAX_N], bool isFull[MAX_N][MAX_N], int n) {
    for (int j = 0; j < n; j++) {
        _flow(isOpen, isFull, n, 0, j);
    }
}

// Estimate the empirical percolation probability
double evaluate(int n, double p, int trials) {
    int count = 0;
    bool isOpen[MAX_N][MAX_N];
    bool isFull[MAX_N][MAX_N];
    for (int i = 0; i < trials; i++) {
        generateRandomMatrix(isOpen, n, p);
        flow(isOpen, isFull, n);
        if (percolates(isFull, n)) {
            count++;
        }
    }
    return (double)count / trials;
}

// Main function: Accept n, p, and trials as command-line arguments
int main(int argc, char *argv[]) {
    if (argc != 4) {
        printf("Usage: %s <n> <p> <trials>\n", argv[0]);
        return 1;
    }
    int n = atoi(argv[1]);
    double p = atof(argv[2]);
    int trials = atoi(argv[3]);
    srand(time(NULL));
    double q = evaluate(n, p, trials);
    printf("%f\n", q);
    return 0;
}

//----------------------------------------------------------------------

// Compile and run:
// gcc -o estimate estimate.c
// ./estimate 20 0.55 100
// ./estimate 20 0.65 100
// ./estimate 20 0.65 100
// ./estimate 40 0.55 1000
