#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// DSA signature function (simplified)
void dsa_sign(int message, int *signature) {
    int k = rand() % 100 + 1; // Randomly generate k for each signature
    signature[0] = message * k; // Simplified signature calculation
    signature[1] = k;
}

// RSA signature function (simplified)
void rsa_sign(int message, int *signature) {
    int k = 10; // Fixed k for RSA signature
    signature[0] = message * k; // Simplified signature calculation
}

int main() {
    srand(time(NULL)); // Initialize random number generator

    int message = 123; // Example message
    int dsa_signature1[2], dsa_signature2[2];
    int rsa_signature1[2], rsa_signature2[2];

    // DSA signatures
    dsa_sign(message, dsa_signature1);
    dsa_sign(message, dsa_signature2);

    // RSA signatures
    rsa_sign(message, rsa_signature1);
    rsa_sign(message, rsa_signature2);

    printf("DSA Signatures:\n");
    printf("Signature 1: (%d, %d)\n", dsa_signature1[0], dsa_signature1[1]);
    printf("Signature 2: (%d, %d)\n", dsa_signature2[0], dsa_signature2[1]);

    printf("RSA Signatures:\n");
    printf("Signature 1: (%d, %d)\n", rsa_signature1[0], rsa_signature1[1]);
    printf("Signature 2: (%d, %d)\n", rsa_signature2[0], rsa_signature2[1]);

    return 0;
}
