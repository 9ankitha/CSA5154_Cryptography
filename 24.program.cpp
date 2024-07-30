#include <stdio.h>
#include <stdlib.h>

// Function to compute gcd and x, y such that ax + by = gcd(a, b)
int extended_gcd(int a, int b, int *x, int *y) {
    if (a == 0) {
        *x = 0;
        *y = 1;
        return b;
    }
    int x1, y1;
    int gcd = extended_gcd(b % a, a, &x1, &y1);
    *x = y1 - (b / a) * x1;
    *y = x1;
    return gcd;
}

// Function to find modular multiplicative inverse of a under modulo m
int mod_inverse(int a, int m) {
    int x, y;
    int g = extended_gcd(a, m, &x, &y);
    if (g != 1) {
        printf("Inverse doesn't exist\n");
        exit(1);
    }
    return (x % m + m) % m;
}

// Function to find p and q and private key d
void rsa_private_key(int n, int e) {
    int p, q;
    int found = 0;

    // Factor n to find p and q
    for (p = 2; p <= n / 2; p++) {
        if (n % p == 0) {
            q = n / p;
            // Check if both p and q are primes
            int is_p_prime = 1, is_q_prime = 1;

            for (int i = 2; i <= p / 2; i++) {
                if (p % i == 0) {
                    is_p_prime = 0;
                    break;
                }
            }
            for (int i = 2; i <= q / 2; i++) {
                if (q % i == 0) {
                    is_q_prime = 0;
                    break;
                }
            }
            if (is_p_prime && is_q_prime) {
                found = 1;
                break;
            }
        }
    }

    if (!found) {
        printf("Failed to find p and q.\n");
        return;
    }

    int phi_n = (p - 1) * (q - 1);
    int d = mod_inverse(e, phi_n);

    printf("p = %d\n", p);
    printf("q = %d\n", q);
    printf("phi(n) = %d\n", phi_n);
    printf("Private key d = %d\n", d);
}

int main() {
    int n = 3599;
    int e = 31;

    rsa_private_key(n, e);

    return 0;
}

