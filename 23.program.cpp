#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Function to preprocess the message by removing spaces and converting to lowercase
void preprocess(const char *input, char *output) {
    int k = 0;
    for (int i = 0; input[i] != '\0'; i++) {
        if (isalpha(input[i])) {
            output[k++] = tolower(input[i]);
        }
    }
    output[k] = '\0';
}

// Function to encrypt the plaintext using the one-time pad Vigenère cipher
void encrypt(const char *plaintext, char *ciphertext, int *key, int key_length) {
    int length = strlen(plaintext);
    for (int i = 0; i < length; i++) {
        int shift = key[i % key_length];
        ciphertext[i] = ((plaintext[i] - 'a' + shift) % 26) + 'a';
    }
    ciphertext[length] = '\0';
}

// Function to decrypt the ciphertext using the one-time pad Vigenère cipher
void decrypt(const char *ciphertext, char *plaintext, int *key, int key_length) {
    int length = strlen(ciphertext);
    for (int i = 0; i < length; i++) {
        int shift = key[i % key_length];
        plaintext[i] = ((ciphertext[i] - 'a' - shift + 26) % 26) + 'a';
    }
    plaintext[length] = '\0';
}

// Function to find the key needed to decrypt the ciphertext to a given plaintext
void find_key(const char *ciphertext, const char *plaintext, int *key) {
    int length = strlen(ciphertext);
    for (int i = 0; i < length; i++) {
        key[i] = ((ciphertext[i] - plaintext[i] + 26) % 26);
    }
}

int main() {
    const char plaintext[] = "send more money";
    const int key_stream[] = {9, 0, 1, 7, 23, 15, 21, 14, 11, 11, 2, 8, 9};
    const int key_length = sizeof(key_stream) / sizeof(key_stream[0]);

    char processed_plaintext[256];
    char ciphertext[256];
    preprocess(plaintext, processed_plaintext);

    encrypt(processed_plaintext, ciphertext, (int *)key_stream, key_length);
    printf("Encrypted ciphertext: %s\n", ciphertext);

    const char target_plaintext[] = "cash not needed";
    char processed_target_plaintext[256];
    preprocess(target_plaintext, processed_target_plaintext);

    int key[256];
    find_key(ciphertext, processed_target_plaintext, key);

    printf("Key needed for decryption to 'cash not needed': ");
    for (int i = 0; i < strlen(ciphertext); i++) {
        printf("%d ", key[i]);
    }
    printf("\n");

    char decrypted_text[256];
    decrypt(ciphertext, decrypted_text, key, strlen(ciphertext));
    printf("Decrypted text using the new key: %s\n", decrypted_text);

    return 0;
}

