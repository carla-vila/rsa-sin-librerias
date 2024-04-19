#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include "rsa.h"

uint64_t x[20] = {0}, y[20] = {0}, z[20] = {0}, e[18] = {0};

int main() {
    int i;
    uint64_t key[20] = {0};
    key[0] = 0x85;  // Example modulus, typically should be a large prime product
    e[0] = 0x5;     // Example public exponent, typically larger and prime
    y[0] = 0x41;    // Example private exponent for demonstration
    z[0] = 0x9;     // Input value for encryption/decryption

    // Display initial values
    printf("Initial values:\n");
    printf("Key[0]: %016lx\n", key[0]);
    printf("Exponent for first RSA operation (e[0]): %016lx\n", e[0]);
    printf("Exponent for second RSA operation (y[0]): %016lx\n", y[0]);
    printf("Input data (z[0]): %016lx\n", z[0]);

    // Perform first RSA operation
    printf("Performing first RSA operation...\n");
    rsa1024(z, x, e, key);
    printf("Output after first RSA operation (z[0]): %016lx\n", z[0]);

    // Perform second RSA operation
    printf("Performing second RSA operation...\n");
    rsa1024(z, x, y, key);
    printf("Output after second RSA operation (z[0]): %016lx\n", z[0]);

    return 0;
}

void temp_disp(uint64_t x[], uint32_t n) {
    printf("[");
    for (uint32_t i = 0; i < n; i++) {
        if (i > 0) printf(", ");
        //printf("%016lx", x[i]);
    }
    printf("]\n");
}