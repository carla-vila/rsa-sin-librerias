#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include "rsa.h"

int main() {
    uint64_t mod[18] = {0xD5, 0xC4, 0xB3, 0xA2, 0x91, 0x81, 0x71, 0x61, 0x51, 0x41, 0x31, 0x21, 0x11, 0x1, 0, 0, 0, 0}; // modulo for RSA (simple example)
    uint64_t data[18] = {0x2};  // The data to be encrypted, simple small number
    uint64_t expo[18] = {0x11};  // Public exponent e for encryption (small prime number)
    uint64_t res[18] = {0};  // Result array initialized to zero

    // Encrypt data
    if (rsa1024(res, data, expo, mod)) {
        printf("Encrypted Data:\n");
        for (int i = 17; i >= 0; i--) {
            printf("%llx ", res[i]);
        }
        printf("\n");
    }

    // Assume we now decrypt using private exponent d (which should be set properly)
    uint64_t decrypted[18] = {0};
    uint64_t private_expo[18] = {0x101}; // Private exponent (not a real one, just for example)

    if (rsa1024(decrypted, res, private_expo, mod)) {
        printf("Decrypted Data:\n");
        for (int i = 17; i >= 0; i--) {
            printf("%llx ", decrypted[i]);
        }
        printf("\n");
    }

    return 0;
}
