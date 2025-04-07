//----------------------------------------------------------------------
// gauss.c
//----------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//----------------------------------------------------------------------

// Return the value of the Gaussian probability function with mean 0.0
// and standard deviation 1.0 at the given x value.
static double phi(const double x) {
    return exp(-x * x / 2.0) / sqrt(2.0 * M_PI);
}

//----------------------------------------------------------------------

// Return the value of the Gaussian probability function with mean mu
// and standard deviation sigma at the given x value.
static double pdf(const double x, const double mu, const double sigma) {
    return phi((x - mu) / sigma) / sigma;
}

//----------------------------------------------------------------------

// Return the value of the cumulative Gaussian distribution function
// with mean 0.0 and standard deviation 1.0 at the given z value.
static double Phi(const double z) {
    if (z < -8.0) return 0.0;
    if (z > 8.0) return 1.0;
    double total = 0.0;
    double term = z;
    int i = 3;
    while (total != total + term) {
        total += term;
        term *= z * z / (double)i;
        i += 2;
    }
    return 0.5 + phi(z) * total;
}

//----------------------------------------------------------------------

// Return the value of the cumulative Gaussian distribution function
// with mean mu and standard deviation sigma at the given z value.
static double cdf(const double z, const double mu, const double sigma) {
    return Phi((z - mu) / sigma);
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
// gcc -lm -o gauss gauss.c
// ./gauss 820 1019 209
// 0.170510
