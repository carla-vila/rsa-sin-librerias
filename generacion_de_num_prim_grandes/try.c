#include "../config/keys.h"


// gcc generaltools/try.c config/keys.c -o try -I/opt/homebrew/opt/gmp/include -L/opt/homebrew/opt/gmp/lib -lgmp
int main() {
    // Initialize primes
    initPrimes();

    // Use the primes or perform other operations

    // Clear memory allocated for primes
    mpz_clear(client_p);
    mpz_clear(client_q);
    mpz_clear(server_p);
    mpz_clear(server_q);

    return 0;
}