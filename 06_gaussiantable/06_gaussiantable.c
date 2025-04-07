//----------------------------------------------------------------------
// 06_gaussiantable.c
//----------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include "gaussian.h"

//----------------------------------------------------------------------

// Main function: Accept mean (mu) and standard deviation (sigma) as command-line arguments.
// Print a table of Gaussian distribution percentages for SAT scores ranging from 400 to 1600.
int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <mu> <sigma>\n", argv[0]);
        return 1;
    }
    const double mu = atof(argv[1]);
    const double sigma = atof(argv[2]);

    for (int score = 400; score <= 1600; score += 100) {
        double percent = cdf(score, mu, sigma);
        printf("%4d  %.4f\n", score, percent);
    }
    return 0;
}

//----------------------------------------------------------------------

// Compile and run:
// gcc -o 06_gaussiantable 06_gaussiantable.c ../05_gaussian/05_gaussian.c -lm
// ./06_gaussiantable 1019 209
// Example output:
//  400  0.0015
//  500  0.0065
//  600  0.0225
//  700  0.0635
//  800  0.1474
//  900  0.2845
// 1000  0.4638
// 1100  0.6508
// 1200  0.8068
// 1300  0.9106
// 1400  0.9658
// 1500  0.9893
// 1600  0.9973
