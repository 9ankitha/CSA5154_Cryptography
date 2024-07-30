#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BLOCK_SIZE 8
#define KEY_SIZE 10

// Placeholder for S-DES encryption and decryption functions
// Replace these with the actual S-DES functions
void sdes_encrypt(unsigned char *plaintext, unsigned char *key, unsigned char *ciphertext) {
    // Placeholder implementation
    for (int i = 0; i < BLOCK_SIZE; i++) {
        ciphertext[i] = plaintext[i] ^ key[i % KEY_SIZE];
    }
}

void sdes_decrypt(unsigned char *ciphertext, unsigned char *key, unsigned char *plaintext) {
    // Placeholder implementation
    for (int i = 0; i < BLOCK_SIZE; i++) {
        plaintext[i] = ciphertext[i] ^ key[i % KEY_SIZE];
    }
}

void increment_counter(unsigned char *counter) {
    for (int i = BLOCK_SIZE - 1; i >= 0; i--) {
        if (counter[i] < 255) {
            counter[i]++;
            break;
        } else {
            counter[i] = 0;
        }
    }
}

void ctr_encrypt_sdes(unsigned char *plaintext, int plaintext_len, unsigned char *key, unsigned char *counter, unsigned char *ciphertext) {
    unsigned char keystream[BLOCK_SIZE];
    unsigned char block[BLOCK_SIZE];
    for (int i = 0; i < plaintext_len; i += BLOCK_SIZE) {
        // Encrypt the counter to get the keystream
        sdes_encrypt(counter, key, keystream);
        // XOR the keystream with the plaintext to get the ciphertext
        for (int j = 0; j < BLOCK_SIZE; j++) {
            block[j] = (i + j < plaintext_len) ? plaintext[i + j] : 0;
        }
        for (int j = 0; j < BLOCK_SIZE; j++) {
            ciphertext[i + j] = block[j] ^ keystream[j];
        }
        // Increment the counter
        increment_counter(counter);
    }
}

void ctr_decrypt_sdes(unsigned char *ciphertext, int ciphertext_len, unsigned char *key, unsigned char *counter, unsigned char *plaintext) {
    unsigned char keystream[BLOCK_SIZE];
    unsigned char block[BLOCK_SIZE];
    for (int i = 0; i < ciphertext_len; i += BLOCK_SIZE) {
        // Encrypt the counter to get the keystream
        sdes_encrypt(counter, key, keystream);
        // XOR the keystream with the ciphertext to get the plaintext
        for (int j = 0; j < BLOCK_SIZE; j++) {
            block[j] = (i + j < ciphertext_len) ? ciphertext[i + j] : 0;
        }
        for (int j = 0; j < BLOCK_SIZE; j++) {
            plaintext[i + j] = block[j] ^ keystream[j];
        }
        // Increment the counter
        increment_counter(counter);
    }
}

int main() {
    unsigned char key[KEY_SIZE] = {0x1F, 0xBD, 0x0F, 0x3C, 0x2D, 0x8A, 0x6E, 0xFF, 0x4A, 0x5C}; // Example key
    unsigned char counter[BLOCK_SIZE] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}; // Initial counter

    // Example plaintext
    unsigned char plaintext[] = {0x00, 0x01, 0x10, 0x20, 0x40}; // Binary 0000 0001 0000 0010 0000 0100
    unsigned char ciphertext[BLOCK_SIZE * 2]; // Buffer for encrypted text
    unsigned char decrypted[BLOCK_SIZE * 2]; // Buffer for decrypted text

    int plaintext_len = sizeof(plaintext);

    // Encrypt the plaintext using CTR mode
    ctr_encrypt_sdes(plaintext, plaintext_len, key, counter, ciphertext);
    printf("CTR Ciphertext:\n");
    for (int i = 0; i < plaintext_len; i++) {
        printf("%02x ", ciphertext[i]);
    }
    printf("\n");

    // Reset the counter for decryption
    memset(counter, 0, BLOCK_SIZE);

    // Decrypt the ciphertext using CTR mode
    ctr_decrypt_sdes(ciphertext, plaintext_len, key, counter, decrypted);
    printf("CTR Decrypted:\n");
    for (int i = 0; i < plaintext_len; i++) {
        printf("%02x ", decrypted[i]);
    }
    printf("\n");

    return 0;
}

