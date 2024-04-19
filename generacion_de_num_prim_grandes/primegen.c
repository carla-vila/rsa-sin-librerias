#include <stdio.h>
#include <gmp.h>
#include <stdlib.h>
#include <time.h>

//gcc primegen.c -o primegen -I/opt/homebrew/opt/gmp/include -L/opt/homebrew/opt/gmp/lib -lgmp

//-------------------------------------------------------------------------------------------------
// Este código genera dos números primos de 500 (ha subido a 800 ya que si no no funciona el codigo ) bits para usar en los algoritmos de cifrado necesarios
// y asegura que los primos generados sean distintos.
//-------------------------------------------------------------------------------------------------

void generar_primo_de_500_bits(mpz_t primo) {
    gmp_randstate_t r_state;
    gmp_randinit_default(r_state);
    gmp_randseed_ui(r_state, time(NULL)); // Usar tiempo como semilla para la generación de números aleatorios.

    do {
        mpz_urandomb(primo, r_state, 800); // Genera un número aleatorio de 500 bits.
        mpz_setbit(primo, 0); // Asegura que el número sea impar.
    } while (mpz_probab_prime_p(primo, 15) == 0); // Verifica si es primo, repite si no lo es.

    gmp_randclear(r_state);
}

void generar_primos(mpz_t p, mpz_t q) {
    generar_primo_de_500_bits(p); // Genera el primer primo
    do {
        generar_primo_de_500_bits(q); // Genera el segundo primo
    } while (mpz_cmp(p, q) == 0); // Asegura que p y q sean distintos
}

int main() {
    mpz_t p, q;

    mpz_inits(p, q, NULL); // Inicializa los números primos.

    generar_primos(p, q); // Genera dos números primos distintos.

    // Imprime los números primos generados.
    gmp_printf("Primo p: %Zd\n", p);
    gmp_printf("Primo q: %Zd\n", q);

    // Limpia y libera los recursos.
    mpz_clears(p, q, NULL);

    return 0;
}
