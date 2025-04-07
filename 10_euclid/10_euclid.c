//----------------------------------------------------------------------
// euclid.c
//----------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>

//----------------------------------------------------------------------

// Return the greatest common divisor of p and q.
int gcd(int p, int q) {
    if (q == 0) {
        return p;
    }
    return gcd(q, p % q);
}

//----------------------------------------------------------------------

// Main function: Accept integers p and q as command-line arguments,
// compute the greatest common divisor of p and q, and print the result.
int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <p> <q>\n", argv[0]);
        return 1;
    }
    int p = atoi(argv[1]);
    int q = atoi(argv[2]);
    int divisor = gcd(p, q);
    printf("%d\n", divisor);
    return 0;
}

//----------------------------------------------------------------------

// Compile and run:
// gcc -o euclid euclid.c
// ./euclid 1440 408
// 24

// ./euclid 314159 271828
// 1
