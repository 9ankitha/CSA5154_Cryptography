#include <stdio.h>
#include<string.h>

void playfair_cipher(char key[], char plaintext[]) {
    char ciphertext[100];
    int i, j;
    for (i = 0; i < strlen(plaintext); i += 2) {
        if (plaintext[i] == plaintext[i + 1]) {
            plaintext[i + 1] = 'X';
        }
        for (j = 0; j < 25; j++) {
            if (key[j] == plaintext[i]) {
                plaintext[i] = key[(j + 1) % 25];
            }
            if (key[j] == plaintext[i + 1]) {
                plaintext[i + 1] = key[(j + 1) % 25];
            }
        }
        ciphertext[i] = plaintext[i];
        ciphertext[i + 1] = plaintext[i + 1];
    }
    printf("%s", ciphertext);
}

int main() {
    char key[] = "MONARCHY";
    char plaintext[] = "ATTACK";
    playfair_cipher(key, plaintext);
    return 0;
}

