#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_LEN 500

void analyzeFrequency(char *ciphertext, int *freq);
void decryptMessage(char *ciphertext, char *key, char *plaintext);

int main() {
    char ciphertext[MAX_LEN] = "53‡‡†305))6*;4826)4‡.)4‡);806*;48†8¶60))85;;]8*;:‡*8†83"
                               "(88)5*†;46(;88*96*?;8)*‡(;485);5*†2:*‡(;4956*2(5*—4)8¶8*"
                               ";4069285);)6†8)4‡‡;1(‡9;48081;8:8‡1;48†85;4)485†528806*81"
                               " (‡9;48;(88;4(‡?34;48)4‡;161;:188;‡?";
    char key[256];
    char plaintext[MAX_LEN];
    int freq[256] = {0};
    
    analyzeFrequency(ciphertext, freq);

    // Display frequency analysis results
    printf("Frequency analysis of the ciphertext:\n");
    for (int i = 0; i < 256; i++) {
        if (freq[i] > 0) {
            printf("'%c': %d\n", i, freq[i]);
        }
    }

    // Initialize key with unknown characters as '?'
    for (int i = 0; i < 256; i++) {
        key[i] = '?';
    }

    // Based on frequency analysis and common patterns, make initial guesses
    // Let's assume '‡' is 'e', '8' is 't', and '4' is 'h'
    key['‡'] = 'e';
    key['8'] = 't';
    key['4'] = 'h';

    // Additional guesses can be made based on context and further analysis
    // This step usually requires manual intervention and is iterative

    // Decrypt the message using the current key
    decryptMessage(ciphertext, key, plaintext);
    printf("\nPartially decrypted message:\n%s\n", plaintext);

    return 0;
}

void analyzeFrequency(char *ciphertext, int *freq) {
    int i;
    for (i = 0; ciphertext[i] != '\0'; i++) {
        freq[(unsigned char)ciphertext[i]]++;
    }
}

void decryptMessage(char *ciphertext, char *key, char *plaintext) {
    int i;
    for (i = 0; ciphertext[i] != '\0'; i++) {
        if (isprint(ciphertext[i])) {
            plaintext[i] = key[(unsigned char)ciphertext[i]];
        } else {
            plaintext[i] = ciphertext[i];
        }
    }
    plaintext[i] = '\0';
}

