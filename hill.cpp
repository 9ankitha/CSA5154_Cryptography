#include <stdio.h>
#include <string.h>

void hill_cipher(int key[3][3], char plaintext[], int mode) {
    int ciphertext[3];
    int i;
    for (i = 0; i < strlen(plaintext); i += 3) {
        if (mode == 0) { 
            ciphertext[0] = (key[0][0] * (plaintext[i] - 'A') + key[0][1] * (plaintext[i + 1] - 'A') + key[0][2] * (plaintext[i + 2] - 'A')) % 26;
            ciphertext[1] = (key[1][0] * (plaintext[i] - 'A') + key[1][1] * (plaintext[i + 1] - 'A') + key[1][2] * (plaintext[i + 2] - 'A')) % 26;
            ciphertext[2] = (key[2][0] * (plaintext[i] - 'A') + key[2][1] * (plaintext[i + 1] - 'A') + key[2][2] * (plaintext[i + 2] - 'A')) % 26;
        } else { 
        }
        printf("%c%c%c", ciphertext[0] + 'A', ciphertext[1] + 'A', ciphertext[2] + 'A');
    }
}

int main() {
    int key[3][3] = {{6, 24, 1}, {13, 16, 10}, {20, 17, 15}};
    char plaintext[] = "ACT"; 
    printf("Plaintext: %s\n", plaintext);
    printf("Encrypted: ");
    hill_cipher(key, plaintext, 0); 
    printf("\n");
    return 0;
}

