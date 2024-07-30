#include <stdio.h>
#include <stdlib.h>

// Function to compute the Greatest Common Divisor (GCD) of two numbers
unsigned long long gcd(unsigned long long a, unsigned long long b) {
    while (b != 0) {
        unsigned long long t = b;
        b = a % b;
        a = t;
    }
    return a;
}

int main() {
    // Public key parameters (example values, should be replaced with real ones)
    unsigned long long n = 589; // Example n = 23 * 13 (must be the product of two primes)
    unsigned long long e = 17;  // Public exponent
    unsigned long long M = 23;  // Example plaintext block

    // Calculate GCD of M and n
    unsigned long long factor = gcd(M, n);

    if (factor > 1) {
        // Found a common factor, which should be a prime
        unsigned long long p = factor;
        unsigned long long q = n / p;

        printf("Common factor found: %llu\n", factor);
        printf("The primes are p = %llu and q = %llu\n", p, q);

        // We can now compute f(n) and potentially the private key d if needed
        unsigned long long phi_n = (p - 1) * (q - 1);
        printf("f(n) = %llu\n", phi_n);

        // In a full implementation, we would compute the private key d
        // d = e^(-1) mod f(n)
    } else {
        printf("No common factor found. RSA remains secure in this case.\n");
    }

    return 0;
}
