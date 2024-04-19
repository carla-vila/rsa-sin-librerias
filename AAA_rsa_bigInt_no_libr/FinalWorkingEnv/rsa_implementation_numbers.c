#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include "rsa.h"  // Ensure this header file correctly declares the rsa1024 function.
#include "rsa_params.h"


//gcc -std=c11 -o rsa_program rsa_implementation_numbers.c rsa.c rsa_params.c -lm
// Function to print a number represented as an array of uint64_t
void print_big_number(const char *label, const uint64_t arr[], size_t size) {
    printf("%s:\n0x", label);
    bool leading = true;
    for (int i = size - 1; i >= 0; i--) { // Start from the most significant part
        if (arr[i] != 0 || !leading) {
            printf("%s%016llx", leading ? "" : " ", arr[i]);
            leading = false; // Once we start printing, no more leading checks
        }
    }
    if (leading) { // If nothing was printed, it means the number is zero
        printf("0");
    }
    printf("\n");
}

int main() {
    // Display initial values.
    print_big_number("Initial Key", m, 20);
    print_big_number("Initial Exponent for RSA operation", e, 20);
    print_big_number("Initial Private Key", d, 20);
    print_big_number("Initial Data", data, 20);

    // Perform RSA encryption.
    printf("Performing RSA encryption...\n");
    if (!rsa1024(z, data, e, m)) {
        printf("RSA encryption failed.\n");
        return 1;  // Exit if encryption fails.
    }
    print_big_number("Output after RSA encryption", z, 20);

    // Prepare for decryption.
    memcpy(data, z, sizeof(z)); // Copy encrypted data back to data array for decryption.
    memset(z, 0, sizeof(z)); // Clear the result array.

    // Perform RSA decryption.
    printf("Performing RSA decryption...\n");
    if (!rsa1024(z, data, d, m)) {
        printf("RSA decryption failed.\n");
        return 1;  // Exit if decryption fails.
    }
    print_big_number("Output after RSA decryption", z, 20);

    return 0;
}
