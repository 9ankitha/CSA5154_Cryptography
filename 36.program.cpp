#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to compute the greatest common divisor
int gcd(int a, int b) {
    while (b != 0) {
        int t = b;
        b = a % b;
        a = t;
    }
    return a;
}

// Function to find the modular inverse of a under modulo m using the extended Euclidean algorithm
int mod_inverse(int a, int m) {
    int m0 = m, t, q;
    int x0 = 0, x1 = 1;

    if (m == 1)
        return 0;

    while (a > 1) {
        q = a / m;
        t = m;

        m = a % m, a = t;
        t = x0;
        x0 = x1 - q * x0;
        x1 = t;
    }

    if (x1 < 0)
        x1 += m0;

    return x1;
}

void affine_encrypt(char *plaintext, int a, int b, char *ciphertext) {
    for (int i = 0; i < strlen(plaintext); i++) {
        char p = plaintext[i];
        if (p >= 'A' && p <= 'Z') {
            ciphertext[i] = ((a * (p - 'A') + b) % 26) + 'A';
        } else if (p >= 'a' && p <= 'z') {
            ciphertext[i] = ((a * (p - 'a') + b) % 26) + 'a';
        } else {
            ciphertext[i] = p; // Non-alphabetic characters remain unchanged
        }
    }
    ciphertext[strlen(plaintext)] = '\0';
}

void affine_decrypt(char *ciphertext, int a, int b, char *plaintext) {
    int a_inv = mod_inverse(a, 26);
    if (a_inv == -1) {
        printf("Inverse of a does not exist, decryption not possible.\n");
        exit(1);
    }

    for (int i = 0; i < strlen(ciphertext); i++) {
        char c = ciphertext[i];
        if (c >= 'A' && c <= 'Z') {
            plaintext[i] = ((a_inv * ((c - 'A' - b + 26)) % 26) + 'A');
        } else if (c >= 'a' && c <= 'z') {
            plaintext[i] = ((a_inv * ((c - 'a' - b + 26)) % 26) + 'a');
        } else {
            plaintext[i] = c; // Non-alphabetic characters remain unchanged
        }
    }
    plaintext[strlen(ciphertext)] = '\0';
}

int main() {
    char plaintext[256];
    int a, b;

    printf("Enter the plaintext: ");
    fgets(plaintext, sizeof(plaintext), stdin);
    plaintext[strcspn(plaintext, "\n")] = 0; // Remove newline character

    printf("Enter values for a and b (a should be coprime with 26): ");
    scanf("%d %d", &a, &b);

    if (gcd(a, 26) != 1) {
        printf("Invalid value for a. It must be coprime with 26.\n");
        return 1;
    }

    char ciphertext[strlen(plaintext) + 1];
    char decrypted_text[strlen(plaintext) + 1];

    affine_encrypt(plaintext, a, b, ciphertext);
    printf("Ciphertext: %s\n", ciphertext);

    affine_decrypt(ciphertext, a, b, decrypted_text);
    printf("Decrypted text: %s\n", decrypted_text);

    return 0;
}

