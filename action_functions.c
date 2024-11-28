#include "action_functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>  // For geteuid, execl

void fnr(void) {
    puts("The door is locked.");
    return;
}

void fngrt(void) {
    puts("Opened.");
    puts("No root.");
    return;
}

void fnR(void) {
    // TODO: Implement authorization logic once the authorized users are defined.
    // Example: if (!isAuthorized()) { exit with error }

    if (geteuid() != 0) {
        puts("Insufficient privileges. You need to be root to perform this action.");
        exit(EXIT_FAILURE);
    }
    puts("Opened.");
    // Clear and set minimal environment for safety
    clearenv();
    setenv("PS1", "SAFE ROOT SHELL > ", 1);

    // Execute the bash shell securely
    int value = execl("/bin/bash", "/bin/bash", "--norc", NULL);
    if (value == -1) {
        perror("Failed to execute bash");
        exit(EXIT_FAILURE);
    }
}

