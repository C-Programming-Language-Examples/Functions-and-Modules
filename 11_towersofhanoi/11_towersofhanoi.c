//----------------------------------------------------------------------
// towersofhanoi.c
//----------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//----------------------------------------------------------------------

// Write to standard output instructions to move n Towers of Hanoi
// disks to the left (if parameter left is true) or to the right (if
// parameter left is false).
void moves(int n, bool left) {
    if (n == 0) {
        return;
    }
    moves(n - 1, !left);
    if (left) {
        printf("%d left\n", n);
    } else {
        printf("%d right\n", n);
    }
    moves(n - 1, !left);
}

//----------------------------------------------------------------------

// Main function: Accept integer n as a command-line argument.
// Write to standard output instructions to move n Towers of Hanoi disks to the left.
int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <n>\n", argv[0]);
        return 1;
    }
    int n = atoi(argv[1]);
    moves(n, true);
    return 0;
}

//----------------------------------------------------------------------

// Compile and run:
// gcc -o towersofhanoi towersofhanoi.c
// ./towersofhanoi 1
// 1 left

// ./towersofhanoi 2
// 1 right
// 2 left
// 1 right

// ./towersofhanoi 3
// 1 left
// 2 right
// 1 left
// 3 left
// 1 left
// 2 right
// 1 left
