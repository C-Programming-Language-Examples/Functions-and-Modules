//----------------------------------------------------------------------
// 02_gauss.c
//----------------------------------------------------------------------

#include <stdio.h>

// Main function: Takes command-line arguments.
// argc: Number of arguments (including program name).
// argv: Array of argument strings (argv[0] is the program name).
//    - argv[0] is always the name of the program (or the path used to execute it).
//    - argv[1], argv[2], ... contain the additional command-line arguments provided by the user.
int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: ./gauss <name>\n");
        return 1;
    }
    printf("Hi, %s. How are you?\n", argv[1]);
    return 0;
}

//----------------------------------------------------------------------

// Compile and run:
// gcc -o 02_gauss 02_gauss.c
// ./02_gauss Alice
// Hi, Alice. How are you?
