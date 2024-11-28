#include <stdio.h>
#include <string.h>
#include <stdlib.h>  // Added for `exit` 

#include "validation_functions.h"

int fnchck(int a, int b) {
    int check;
    if (b == a) {
        puts("Valid access.");
        check = 0xf;
    } else {
        check = 0;
    }
    return check;
}

int validate(char * argv[]) {
    char buffer[20];
    // Validate `argv` inputs to prevent NULL dereference
    if (!argv[1] || !argv[2]) {
        fprintf(stderr, "Error: Missing required arguments.\n");
        exit(EXIT_FAILURE);  // Exit if arguments are not properly provided
    }
    // Controlled output to avoid potential format string issues
    printf("You entered \"%s\" and \"%s\". \nDo you agree ? (Y,n):\n", argv[1], argv[2]);

    // Use `%19s` to limit input to the size of `buffer` - 1 (for null terminator)
    if (scanf("%19s", buffer) != 1) {  // Ensure proper reading
        fprintf(stderr, "Error: Failed to read input.\n");
        return -1;  // Indicate failure
    }
    // Compare buffer safely
    return strcmp(buffer, "Y") && strcmp(buffer, "y");
}
