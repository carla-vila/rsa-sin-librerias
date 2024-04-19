#include <stdlib.h> 
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>
#include "rsa.h"

bool modbignum(uint64_t res[], uint64_t op1[], uint64_t op2[], uint32_t n);
bool modmult1024(uint64_t res[], uint64_t op1[], uint64_t op2[], uint64_t mod[]);
uint32_t bit_length(uint64_t op[], uint32_t n);

bool rsa1024(uint64_t res[], uint64_t data[], uint64_t expo[], uint64_t key[]) {
    int32_t i, j, expo_len;
    uint64_t mod_data[18] = {0}, result[18] = {0};
    uint64_t temp_expo = 0;

    printf("Initial Data in RSA: ");
    for (i = 0; i < 16; i++) printf("%016llx ", data[i]);
    printf("\n");

    modbignum(mod_data, data, key, 16);
    printf("Data modulo Key: ");
    for (i = 0; i < 18; i++) printf("%016llx ", mod_data[i]);
    printf("\n");

    result[0] = 1;
    expo_len = bit_length(expo, 16) / 64;

    for (i = 0; i <= expo_len; i++) {
        temp_expo = expo[i];
        for (j = 0; j < 64; j++) {
            if (temp_expo & 1) {
                modmult1024(result, result, mod_data, key);
            }
            modmult1024(mod_data, mod_data, mod_data, key);
            temp_expo >>= 1;
        }
    }

    memcpy(res, result, 16 * sizeof(uint64_t));
    return 1;
}

int main() {
    uint64_t x[20] = {0}, y[20] = {0}, z[20] = {0}, e[18] = {0}, res[18] = {0};

    z[0] = 0x123456;  // Set non-zero data to test
    memcpy(x, z, sizeof(z));  // Copy to `x` to use as input data

    uint64_t key[20] = {0xb1a2bc2ec5007}, expo[18] = {0x10001};
    rsa1024(res, x, expo, key);  // Perform RSA operation

    printf("Result after RSA operation: ");
    for (int i = 0; i < 18; i++) printf("%016llx ", res[i]);
    printf("\n");

    return 0;
}
