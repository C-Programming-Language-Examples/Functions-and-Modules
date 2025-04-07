//----------------------------------------------------------------------
// estimatev.c
//----------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define MAX_N 100

// Generate a random n-by-n matrix with site vacancy probability p
void generateRandomMatrix(bool matrix[MAX_N][MAX_N], int n, double p) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            matrix[i][j] = ((double)rand() / RAND_MAX) < p;
        }
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
// gcc -o estimatev estimatev.c
// ./estimatev 20 0.75 10
// ./estimatev 20 0.95 10
// ./estimatev 20 0.85 1000
// ./estimatev 40 0.85 100
