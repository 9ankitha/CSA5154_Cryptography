#include <stdio.h>
#include<string.h>
void monoalphabetic_cipher(char key[], char plaintext[], int mode) {
    char ciphertext[100];
    int i;
    if (mode == 0) { // encryption
        for (i = 0; i < strlen(plaintext); i++) {
            ciphertext[i] = key[plaintext[i] - 'A'];
        }
    } else { // decryption
        for (i = 0; i < strlen(plaintext); i++) {
            int j;
            for (j = 0; j < 26; j++) {
                if (key[j] == plaintext[i]) {
                    ciphertext[i] = 'A' + j;
                    break;
                }
            }
        }
    }
    printf("%s\n", ciphertext);
}

int main() {
    char key[] = "EKMFLGDQVZNTOWYHXUSPAIBRCJ";
    char plaintext[] = "HELLO";
    printf("Plaintext: %s\n", plaintext);
    printf("Encrypted: ");
    monoalphabetic_cipher(key, plaintext, 0); // encryption
    printf("Decrypted: ");
    monoalphabetic_cipher(key, "XODLQ", 1); // decryption
    return 0;
}

