#include <stdio.h>
#include <stdint.h>
#include "rsa.h"

int main() {
    uint64_t mod[2] = {0xFFFFFFFFFFFFFFC5, 0xFFFFFFFFFFFFFFFF}; // Un módulo grande pero simplificado
    uint64_t data[2] = {0x1234567890ABCDEF, 0x0};  // Datos más significativos para cifrar
    uint64_t expo[2] = {0x10001, 0x0};  // Exponente público típico 65537
    uint64_t res[2] = {0};  // Resultado

    // Cifrado
    if (rsa1024(res, data, expo, mod)) {
        printf("Encrypted Data:\n");
        for (int i = 1; i >= 0; i--) {
            printf("%llx ", res[i]);
        }
        printf("\n");
    }

    // Decifrado usando un exponente privado hipotético
    uint64_t decrypted[2] = {0};
    uint64_t private_expo[2] = {0x1, 0x0}; // Un exponente privado simplificado para prueba

    if (rsa1024(decrypted, res, private_expo, mod)) {
        printf("Decrypted Data:\n");
        for (int i = 1; i >= 0; i--) {
            printf("%llx ", decrypted[i]);
        }
        printf("\n");
    }

    return 0;
}