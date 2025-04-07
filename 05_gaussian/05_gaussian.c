//----------------------------------------------------------------------

// 05_gaussian.c
//----------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "gaussian.h"

//----------------------------------------------------------------------

// Return the value of the Gaussian probability function with mean mu
// and standard deviation sigma at the given x value.
double pdf(const double x, const double mu, const double sigma) {
    double normalized_x = (x - mu) / sigma;
    return exp(-normalized_x * normalized_x / 2.0) / (sqrt(2.0 * M_PI) * sigma);
}

//----------------------------------------------------------------------

// Return the value of the cumulative Gaussian distribution function
// with mean mu and standard deviation sigma at the given z value.
double cdf(const double z, const double mu, const double sigma) {
    double normalized_z = (z - mu) / sigma;
    if (normalized_z < -8.0) return 0.0;
    if (normalized_z > 8.0) return 1.0;
    double total = 0.0;
    double term = normalized_z;
    int i = 3;
    while (total != total + term) {
        total += term;
        term *= normalized_z * normalized_z / i;
        i += 2;
    }
    return 0.5 + total * pdf(normalized_z, 0.0, 1.0);
}

//----------------------------------------------------------------------

// Main function: Accept floats z, mu, and sigma as command-line arguments.
// Print the cdf() result.
int main(int argc, char *argv[]) {
    if (argc != 4) {
        printf("Usage: %s <z> <mu> <sigma>\n", argv[0]);
        return 1;
    }
    const double z = atof(argv[1]);
    const double mu = atof(argv[2]);
    const double sigma = atof(argv[3]);
    const double result = cdf(z, mu, sigma);
    printf("%f\n", result);
    return 0;
}

//----------------------------------------------------------------------

// Compile and run:
// gcc -o 05_gaussian 05_gaussian.c -lm
// ./05_gaussian 820 1019 209
// 0.170510
