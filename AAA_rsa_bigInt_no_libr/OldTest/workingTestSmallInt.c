#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include "rsa.h"



#include <stdio.h>
#include <stdint.h>
#include <string.h>



int main() {
    // Result array initialized with zeros
    uint64_t z[20] = {0};

    // Modulus array (key), initialized according to given values, with extra slots set to 0
    uint64_t m[20] = {0x2b21, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0};

    // Public exponent array, commonly using the Fermat's little theorem recommended value 65537 (0x10001)
    uint64_t e[18] = {0x10001, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0};

    // Private key array, derived from the modulus and public key; the actual values should be calculated securely
    uint64_t d[20] = {0xd91, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0};

    // Data to be encrypted; small example value
    uint64_t data[20] = {0};
    data[0] = 0xba;

    printf("Initial values:\n");
    printf("Key[0]: %016llx\n", m[0]);
    printf("Exponent for RSA operation (e[0]): %016llx\n", e[0]);
    printf("Private key (d[0]): %016llx\n", d[0]);
    printf("Input data (data[0]): %016llx\n", data[0]);

    // Perform RSA encryption
    printf("Performing RSA encryption...\n");
    if (!rsa1024(z, data, e, m)) {
        printf("RSA encryption failed.\n");
        return 1;  // Exit if encryption fails
    }
    
    printf("Output after RSA encryption (z[0]): %016llx\n", z[0]);
    printf("---------------------------------------------------------------------\n");
    // Prepare for decryption
    memcpy(data, z, sizeof(z)); // Copy encrypted data back to data array
    memset(z, 0, sizeof(z)); // Clear the result array

    // Perform RSA decryption
    if (!rsa1024(z, data, d, m)) {
        printf("RSA decryption failed.\n");
        return 1;  // Exit if decryption fails
    }
    printf("Output after RSA decryption (z[0]): %016llx\n", z[0]);
    printf("---------------------------------------------------------------------");

    return 0;
}
