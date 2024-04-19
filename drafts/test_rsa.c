#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include "rsa.h"

int main() {
    // Example data based on typical RSA usage
    uint64_t data[16] = {0x12345, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    uint64_t key[16] = {0x1edcba9876543210, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    uint64_t expo[16] = {0x10001, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    uint64_t res[16] = {0};

    printf("Original Data: \n");
    for (int i = 0; i < 16; i++) {
        printf("%016llx ", data[i]);
        if ((i + 1) % 4 == 0) printf("\n");
    }

    rsa1024(res, data, expo, key);

    printf("Encrypted Data: \n");
    for (int i = 0; i < 16; i++) {
        printf("%016llx ", res[i]);
        if ((i + 1) % 4 == 0) printf("\n");
    }

    // Assuming you want to see a simple back and forth (encrypt/decrypt), let's just toggle the data back
    // Reset data to 0 for simplicity in showing the transformation
    for (int i = 0; i < 16; i++) {
        data[i] = 0;
    }

    rsa1024(data, res, expo, key);  // Decrypt or re-encrypt for simplicity

    printf("Decrypted/Re-Encrypted Data: \n");
    for (int i = 0; i < 16; i++) {
        printf("%016llx ", data[i]);
        if ((i + 1) % 4 == 0) printf("\n");
    }

    return 0;
}