#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Function to compute the Greatest Common Divisor (GCD) of two numbers
unsigned long long gcd(unsigned long long a, unsigned long long b) {
    while (b != 0) {
        unsigned long long t = b;
        b = a % b;
        a = t;
    }
    return a;
}

// Function to compute the modular inverse of e modulo f(n)
unsigned long long mod_inverse(unsigned long long e, unsigned long long phi) {
    unsigned long long d = 0;
    unsigned long long x1 = 0, x2 = 1, y1 = 1;
    unsigned long long temp_phi = phi;
    unsigned long long temp1, temp2;

    while (e > 0) {
        temp1 = temp_phi / e;
        temp2 = temp_phi - temp1 * e;
        temp_phi = e;
        e = temp2;

        d = x1 - temp1 * x2;
        x1 = x2;
        x2 = d;
    }

    if (temp_phi == 1)
        return x1 + phi;

    return 0;  // modular inverse doesn't exist
}

// Function to perform modular exponentiation (base^exp) % mod
unsigned long long mod_exp(unsigned long long base, unsigned long long exp, unsigned long long mod) {
    unsigned long long result = 1;
    base = base % mod;
    while (exp > 0) {
        if (exp % 2 == 1) {
            result = (result * base) % mod;
        }
        exp = exp >> 1;
        base = (base * base) % mod;
    }
    return result;
}

int main() {
    // Example prime numbers p and q
    unsigned long long p = 61;
    unsigned long long q = 53;
    unsigned long long n = p * q;  // n = pq
    unsigned long long phi = (p - 1) * (q - 1);  // f(n) = (p-1)(q-1)

    // Public exponent e (1 < e < f(n) and gcd(e, f(n)) = 1)
    unsigned long long e = 17;
    while (gcd(e, phi) != 1) {
        e++;
    }

    // Private exponent d (modular inverse of e modulo f(n))
    unsigned long long d = mod_inverse(e, phi);

    printf("Public Key: (n = %llu, e = %llu)\n", n, e);
    printf("Private Key: (d = %llu)\n", d);

    // Example plaintext (integer)
    unsigned long long plaintext = 42;
    printf("Plaintext: %llu\n", plaintext);

    // Encrypting the plaintext
    unsigned long long ciphertext = mod_exp(plaintext, e, n);
    printf("Ciphertext: %llu\n", ciphertext);

    // Decrypting the ciphertext
    unsigned long long decrypted_plaintext = mod_exp(ciphertext, d, n);
    printf("Decrypted Plaintext: %llu\n", decrypted_plaintext);

    return 0;
}
