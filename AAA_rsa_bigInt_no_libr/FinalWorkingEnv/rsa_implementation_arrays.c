#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include "rsa.h"  
#include "rsa_params.h"


//gcc -std=c11 -o rsa_program rsa_implementation_arrays.c rsa.c rsa_params.c -lm

void print_array(const char *label, const uint64_t arr[], size_t size) {
    printf("%s:\n", label);
    for (size_t i = 0; i < size; i++) {
        printf("%016llx ", arr[i]);
        if ((i + 1) % 4 == 0)  
            printf("\n");
    }
    printf("\n");
}

int main() {

    // Display initial values.
    print_array("Initial Key", m, 20);
    print_array("Initial Exponent for RSA operation", e, 20);
    print_array("Initial Private Key", d, 20);
    print_array("Initial Data", data, 20);

    // Perform RSA encryption.
    printf("Performing RSA encryption...\n");
    if (!rsa1024(z, data, e, m)) {
        printf("RSA encryption failed.\n");
        return 1;  // Exit if encryption fails.
    }
    print_array("Output after RSA encryption", z, 20);

    // Prepare for decryption.
    memcpy(data, z, sizeof(z));
    memset(z, 0, sizeof(z)); 

    // Perform RSA decryption.
    if (!rsa1024(z, data, d, m)) {
        printf("RSA decryption failed.\n");
        return 1; 
    }
    print_array("Output after RSA decryption", z, 20);

    return 0;
}
