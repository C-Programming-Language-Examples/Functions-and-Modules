//----------------------------------------------------------------------
// beckett.c
//----------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//----------------------------------------------------------------------

// Write to standard output Beckett's stage instructions to have n
// actors enter (if parameter enter is true) or exit (if parameter
// enter is false) the stage.
void moves(int n, bool enter) {
    if (n == 0) {
        return;
    }
    moves(n - 1, true);
    if (enter) {
        printf("enter %d\n", n);
    } else {
        printf("exit  %d\n", n);
    }
    moves(n - 1, false);
}

//----------------------------------------------------------------------

// Main function: Accept integer n as a command-line argument.
// Write to standard output Beckett's stage instructions for n actors.
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
// gcc -o beckett beckett.c
// ./beckett 1
// enter 1

// ./beckett 2
// enter 1
// enter 2
// exit  1

// ./beckett 3
// enter 1
// enter 2
// exit  1
// enter 3
// enter 1
// exit  2
// exit  1
