#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include "rsa.h"  // Make sure this file contains all necessary function declarations

// Function to print uint64_t arrays for debugging
void print_uint64_array(const char* prompt, uint64_t arr[], int size) {
    printf("%s:\n", prompt);
    for (int i = 0; i < size; i++) {
        printf("%016llx ", arr[i]);
        if ((i + 1) % 4 == 0) printf("\n");
    }
    printf("\n");
}

int main() {
    uint64_t data[16] = {12345};  // Simple data to encrypt (e.g., the number 12345)
    uint64_t encrypted[16] = {0}; // Array to store encrypted data
    uint64_t decrypted[16] = {0}; // Array to store decrypted data
    uint64_t n[16] = {0};         // Modulus for RSA operations
    uint64_t e[16] = {0};         // Public exponent
    uint64_t d[16] = {0};         // Private exponent

    // Simple example values for n, e, d (These should be replaced with real RSA values)
    n[0] = 0xFFFFFFFEFFFFAC73;   // A small RSA modulus for testing (not secure)
    e[0] = 0x10001;              // Common public exponent 65537
    d[0] = 0x123456789ABCDEF;    // Dummy private exponent for testing

    // Print original data
    print_uint64_array("Original Data", data, 16);

    // Encrypt the data
    rsa1024(encrypted, data, e, n);
    print_uint64_array("Encrypted Data", encrypted, 16);

    // Decrypt the data
    rsa1024(decrypted, encrypted, d, n);
    print_uint64_array("Decrypted Data", decrypted, 16);

    // Check if the decrypted data matches the original
    if (decrypted[0] == data[0]) {
        printf("Success: The decrypted data matches the original data.\n");
    } else {
        printf("Failure: The decrypted data does not match the original data.\n");
    }

    return 0;
}