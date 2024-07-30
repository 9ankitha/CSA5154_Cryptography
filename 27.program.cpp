#include <stdio.h>
#include <stdlib.h>

unsigned long long modExp(unsigned long long base, unsigned long long exp, unsigned long long mod) {
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

void encryptAndDecrypt(char *message, unsigned long long e, unsigned long long n) {
    printf("Original Message: %s\n", message);
    printf("Encrypted: ");

    // Encrypt each character
    while (*message) {
        char c = *message;
        unsigned long long m = c - 'A'; // Map A-Z to 0-25
        unsigned long long ciph = modExp(m, e, n);
        printf("%llu ", ciph);
        message++;
    }
    printf("\n");
}

void bruteForceAttack(unsigned long long *ciphertext, int len, unsigned long long e, unsigned long long n) {
    printf("Brute-forcing decryption...\n");

    // Try all possible plaintext values (0-25)
    for (int i = 0; i < len; i++) {
        for (unsigned long long m = 0; m < 26; m++) {
            if (modExp(m, e, n) == ciphertext[i]) {
                printf("%c", (char)(m + 'A'));
                break;
            }
        }
    }
    printf("\n");
}

int main() {
    // RSA public key components (example values, normally these would be large)
    unsigned long long e = 65537; // Public exponent
    unsigned long long n = 3233;  // Modulus (example, should be the product of two large primes)

    // Example message
    char message[] = "HELLO";

    // Encrypt the message
    encryptAndDecrypt(message, e, n);

    // Example ciphertext (this would be received or intercepted)
    unsigned long long ciphertext[] = {1336, 2676, 2051, 2051, 879};

    // Brute-force attack to decrypt the message
    bruteForceAttack(ciphertext, 5, e, n);

    return 0;
}
