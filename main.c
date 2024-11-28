#include <stdio.h>
#include <stdlib.h>
#include <limits.h>  // For integer range checking

#include "action_functions.h"
#include "validation_functions.h"

// Helper function for safer integer parsing
int safe_atoi(const char *str, int *value) {
    char *endptr;
    long int result;

    // Convert string to long with error checking
    result = strtol(str, &endptr, 10);

    // Check for conversion errors
    if (*endptr != '\0' || str == endptr) {
        fprintf(stderr, "Error: Invalid integer input '%s'.\n", str);
        return -1; // Indicate failure
    }

    // Check for integer overflow/underflow
    if (result < INT_MIN || result > INT_MAX) {
        fprintf(stderr, "Error: Integer input '%s' out of range.\n", str);
        return -1; // Indicate failure
    }

    *value = (int)result; // Safe to cast since range is checked
    return 0; // Indicate success
}

int main(int argc, char *argv[]) {
    int check;
    int in0, in1;

    // Validate the number of arguments
    if (argc != 3) {
        puts("Usage: client <chiffre0> <chiffre1>");
        return 1; // Return error code
    }

    // Validate and parse `argv[1]` and `argv[2]`
    if (safe_atoi(argv[1], &in1) != 0 || safe_atoi(argv[2], &in0) != 0) {
        return 1; // Exit on invalid input
    }

    // Validate the inputs using the `validate` function
    check = validate(argv);
    if (check != 0) {
        fnr(); // Handle validation failure
        return 1;
    }

    puts("\nChecking values...");
    check = fnchck(in1, in0);

    if (check == 0xf) { // Check for success status
        fngrt(); // Handle success case
    } else {
        fnr(); // Handle failure case
    }

    return 0; // Return success
}
