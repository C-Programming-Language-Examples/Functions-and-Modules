//----------------------------------------------------------------------
// 04_playthetune.c
//----------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define SPS 44100
#define CONCERT_A_HZ 440.0
#define NOTES_ON_SCALE 12.0

//----------------------------------------------------------------------

// Superpose arrays a and b, weighted by aWeight and bWeight.
static void superpose(double *c, const double *a, const double *b, const double aWeight, const double bWeight, const int length) {
    for (int i = 0; i < length; ++i) {
        c[i] = a[i] * aWeight + b[i] * bWeight;
    }
}

//----------------------------------------------------------------------

// Generate a tone of frequency hz for duration t.
static double* tone(const double hz, const double t, int *length) {
    *length = (int)(SPS * t) + 1;
    double *a = (double*)malloc(*length * sizeof(double));
    for (int i = 0; i < *length; ++i) {
        a[i] = sin(2.0 * M_PI * i * hz / SPS);
    }
    return a;
}

//----------------------------------------------------------------------

// Generate a note with harmonics for duration t.
static double* note(const int pitch, const double t, int *length) {
    double hz = CONCERT_A_HZ * pow(2.0, pitch / NOTES_ON_SCALE);
    int len_a, len_hi, len_lo;
    double *a = tone(hz, t, &len_a);
    double *hi = tone(2 * hz, t, &len_hi);
    double *lo = tone(hz / 2, t, &len_lo);
    double *h = (double*)malloc(len_a * sizeof(double));
    double *result = (double*)malloc(len_a * sizeof(double));
    superpose(h, hi, lo, 0.5, 0.5, len_a);
    superpose(result, a, h, 0.5, 0.5, len_a);
    free(a); free(hi); free(lo); free(h);
    *length = len_a;
    return result;
}

//----------------------------------------------------------------------

int main(void) {
    int pitch;
    double duration;
    while (scanf("%d %lf", &pitch, &duration) != EOF) {
        int length;
        double *samples = note(pitch, duration, &length);
        for (int i = 0; i < length; ++i) {
            printf("%f\n", samples[i]);
        }
        free(samples);
    }
    return 0;
}

//----------------------------------------------------------------------

// Compile and run:
// gcc -o 04_playthetune 04_playthetune.c -lm
// ./04_playthetune < ascale.txt
