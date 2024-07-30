#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define ALPHABET_SIZE 26
#define TOP_N 10

// English letter frequency order (most to least frequent)
const char *english_freq_order = "ETAOINSHRDLCUMWFGYPBVKJXQZ";

// Function to count the frequency of each letter in the text
void count_frequencies(const char *text, int *freq) {
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        freq[i] = 0;
    }
    for (int i = 0; text[i] != '\0'; i++) {
        if (isalpha(text[i])) {
            freq[toupper(text[i]) - 'A']++;
        }
    }
}

// Function to sort frequencies and return the most frequent letters
void sort_frequencies(int *freq, char *sorted_letters) {
    int indices[ALPHABET_SIZE];
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        indices[i] = i;
    }

    // Sort indices based on frequencies in descending order
    for (int i = 0; i < ALPHABET_SIZE - 1; i++) {
        for (int j = i + 1; j < ALPHABET_SIZE; j++) {
            if (freq[indices[i]] < freq[indices[j]]) {
                int temp = indices[i];
                indices[i] = indices[j];
                indices[j] = temp;
            }
        }
    }

    // Map sorted indices to letters
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        sorted_letters[i] = 'A' + indices[i];
    }
}

// Function to decrypt the ciphertext with a given shift
void decrypt_with_shift(const char *ciphertext, int shift, char *plaintext) {
    for (int i = 0; ciphertext[i] != '\0'; i++) {
        if (isalpha(ciphertext[i])) {
            char base = isupper(ciphertext[i]) ? 'A' : 'a';
            plaintext[i] = (ciphertext[i] - base - shift + ALPHABET_SIZE) % ALPHABET_SIZE + base;
        } else {
            plaintext[i] = ciphertext[i];
        }
    }
    plaintext[strlen(ciphertext)] = '\0';
}

// Function to perform letter frequency attack on the ciphertext
void letter_frequency_attack(const char *ciphertext, int top_n) {
    int freq[ALPHABET_SIZE];
    char sorted_letters[ALPHABET_SIZE];
    char plaintext[256];

    count_frequencies(ciphertext, freq);
    sort_frequencies(freq, sorted_letters);

    printf("Top %d possible plaintexts:\n", top_n);
    for (int i = 0; i < top_n; i++) {
        int shift = (sorted_letters[0] - 'A') - (english_freq_order[i] - 'A');
        shift = (shift + ALPHABET_SIZE) % ALPHABET_SIZE;
        decrypt_with_shift(ciphertext, shift, plaintext);
        printf("Plaintext %d (shift %d): %s\n", i + 1, shift, plaintext);
    }
}

int main() {
    char ciphertext[256];
    int top_n;

    printf("Enter the ciphertext: ");
    fgets(ciphertext, sizeof(ciphertext), stdin);
    ciphertext[strcspn(ciphertext, "\n")] = 0; // Remove newline character

    printf("Enter the number of possible plaintexts to display: ");
    scanf("%d", &top_n);

    if (top_n > TOP_N) {
        top_n = TOP_N;
    }

    letter_frequency_attack(ciphertext, top_n);

    return 0;
}

