#include <stdio.h>
#include<string.h>

void caesar_cipher(int shift, char plaintext[]) {
    char ciphertext[100];
    int i;
    for (i = 0; i < strlen(plaintext); i++) {
        ciphertext[i] = plaintext[i] + shift;
        if (ciphertext[i] > 'Z') {
            ciphertext[i] = 'A' + (ciphertext[i] - 'Z' - 1);
        }
    }
    printf("%s", ciphertext);
}

int main() {
    int shift = 3;
    char plaintext[] = "WORLD";
    caesar_cipher(shift, plaintext);
    return 0;
}

