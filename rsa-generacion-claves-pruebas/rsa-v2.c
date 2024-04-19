#include <stdio.h>
#include <gmp.h>

//gcc rsa-v2.c ../config/keys.c -o rsa -I/opt/homebrew/opt/gmp/include -L/opt/homebrew/opt/gmp/lib -lgmp

extern mpz_t client_p, client_q;

void initPrimes();

void rsa_encrypt(mpz_t ciphertext, mpz_t plaintext, mpz_t e, mpz_t n) {
    mpz_powm(ciphertext, plaintext, e, n); // Cifrado: ciphertext = plaintext^e mod n
}

void rsa_decrypt(mpz_t plaintext, mpz_t ciphertext, mpz_t d, mpz_t n) {
    mpz_powm(plaintext, ciphertext, d, n); // Descifrado: plaintext = ciphertext^d mod n
}

int main() {
    mpz_t n, phi, e, d, ciphertext, decrypted_msg;

    // La variable 'msg' solo debe ser inicializada una vez.
    mpz_t msg; 

    // Inicialización de variables GMP
    mpz_inits(n, phi, e, d, msg, ciphertext, decrypted_msg, NULL);

    // Inicialización de números primos p y q
    initPrimes();

    // Impresión de los valores de p y q para verificar su correcta inicialización
    gmp_printf("Valor de p: %Zd\n", client_p);
    gmp_printf("Valor de q: %Zd\n", client_q);

    // Calcula n = p * q
    mpz_mul(n, client_p, client_q);
    gmp_printf("n (p*q): %Zd\n", n);

    // Preparación de p y q para calcular phi = (p-1) * (q-1)
    mpz_t p_minus_1, q_minus_1;
    mpz_inits(p_minus_1, q_minus_1, NULL);
    mpz_sub_ui(p_minus_1, client_p, 1);
    mpz_sub_ui(q_minus_1, client_q, 1);
    mpz_mul(phi, p_minus_1, q_minus_1);
    gmp_printf("phi ((p-1)*(q-1)): %Zd\n", phi);

    // Elección de e, coprimo con phi y menor que phi
    mpz_set_ui(e, 65537);
    gmp_printf("e: %Zd\n", e);

    // Calcula d, el inverso modular de e mod phi
    if (mpz_invert(d, e, phi) == 0) {
        printf("Error: No se puede calcular el inverso modular de e mod phi.\n");
        return -1;
    }
    gmp_printf("d (inverso modular): %Zd\n", d);

    // Asignación del mensaje con un número grande usando una cadena de caracteres
    //------------100 bits---------------->>>OK
    //mpz_set_str(msg, "689988970373403812140697157966", 10);
    //------------500 bits---------------->>>OK
    //mpz_set_str(msg, "3189697435769709321000512726678094953256202406621026987135511048953596963052996376265261099908437597827518139390232566160431859537781459013976362995933", 10);
    //------------1000 bits--------------->>NOT OK -------> YA OK
    mpz_set_str(msg, "6643839173115983065901696984234387152417656552510024143528035243075932039141540887560891921413152283372617392972052858355392130164398195728846682147108335529399573584722630675668028759157420693015776494121027122236227911260946427912817705343653404799866060371935100989352961648363069353334496732725087", 10);

    gmp_printf("Mensaje original: %Zd\n", msg);

    // Cifrado del mensaje
    rsa_encrypt(ciphertext, msg, e, n);
    gmp_printf("CLAVE PUBLICA E: %Zd\n", e);
    gmp_printf("CLAVE PUBLICA N: %Zd\n", n);
    gmp_printf("Mensaje cifrado: %Zd\n", ciphertext);

    // Descifrado del mensaje
    rsa_decrypt(decrypted_msg, ciphertext, d, n);
    gmp_printf("CLAVE PRIVADA E: %Zd\n", d);
    gmp_printf("CLAVE PRIVADA N: %Zd\n", n);
    gmp_printf("Mensaje descifrado: %Zd\n", decrypted_msg);

    // Verificación de la desencriptación exitosa
    if (mpz_cmp(msg, decrypted_msg) == 0) {
        printf("La desencriptación fue exitosa.\n");
    } else {
        printf("Falló la desencriptación.\n");
    }

    // Limpieza de las variables GMP
    mpz_clears(n, phi, e, d, msg, ciphertext, decrypted_msg, p_minus_1, q_minus_1, NULL);

    return 0;
}
