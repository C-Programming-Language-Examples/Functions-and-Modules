//----------------------------------------------------------------------
// 03_coupon.c
//----------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

//----------------------------------------------------------------------

// Return a random coupon between 0 and n-1.
static int getCoupon(const int n) {
    return rand() % n;
}

//----------------------------------------------------------------------

// Collect coupons until getting one of each value in the range
// 0 to n-1. Return the number of coupons collected.
static int collect(const int n) {
    bool found[n];
    for (int i = 0; i < n; ++i) {
        found[i] = false;
    }
    int couponCount = 0;
    int distinctCouponCount = 0;
    while (distinctCouponCount < n) {
        int coupon = getCoupon(n);
        couponCount++;
        if (!found[coupon]) {
            distinctCouponCount++;
            found[coupon] = true;
        }
    }
    return couponCount;
}

//----------------------------------------------------------------------

// Main function: Accept integer n as a command-line argument.
// Print the number of coupons collected.
int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <n>\n", argv[0]);
        return 1;
    }
    srand(time(NULL));
    const int n = atoi(argv[1]);
    const int couponCount = collect(n);
    printf("%d\n", couponCount);
    return 0;
}

//----------------------------------------------------------------------

// Compile and run:
// gcc -o 03_coupon 03_coupon.c
// ./03_coupon 1000
// Example output: 6456
