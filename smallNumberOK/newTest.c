#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include "rsa.h"

uint64_t x[20] = {0}, y[20] = {0}, z[20] = {0}, e[18] = {0};

int main() {
    uint64_t m[20] = {0}, e[18] = {0}, d[20] = {0}, data[20] = {0};

    m[0] = 0x21;  // Small product of two primes for example
    e[0] = 0x7;         // Common public exponent
    d[0] = 0x3;   // Example private exponent (must be derived properly)
    data[0] = 0x1d;        // Some data to encrypt

    printf("Initial values:\n");
    printf("Key[0]: %016llx\n", m[0]);
    printf("Exponent for RSA operation (expo[0]): %016llx\n", e[0]);
    printf("Private key (priv[0]): %016llx\n", d[0]);
    printf("Input data (data[0]): %016llx\n", data[0]);

    // Perform first RSA operation (Encryption)
    printf("Performing RSA encryption...\n");
    rsa1024(z, data, e, m);
    rsa1024(z, data, d, m);
    
    printf("Output after RSA encryption (z[0]): %016llx\n", z[0]);
    return 0;
}
