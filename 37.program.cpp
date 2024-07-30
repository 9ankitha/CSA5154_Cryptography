#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// English letter frequency (in order of decreasing frequency)
const char *english_freq_order = "ETAOINSHRDLCUMWFGYPBVKJXQZ";

// Function to count letter frequencies in a given text
void count_frequencies(const char *text, int *freq) {
    for (int i = 0; i < 26; i++) {
        freq[i] = 0;
    }
    for (int i = 0; text[i] != '\0'; i++) {
        if (isalpha(text[i])) {
            freq[toupper(text[i]) - 'A']++;
        }
    }
}

// Function to sort frequencies and map them to letters
void sort_and_map(int *freq, char *map) {
    int sorted_indices[26];
    for (int i = 0; i < 26; i++) {
        sorted_indices[i] = i;
    }

    for (int i = 0; i < 25; i++) {
        for (int j = i + 1; j < 26; j++) {
            if (freq[sorted_indices[i]] < freq[sorted_indices[j]]) {
                int temp = sorted_indices[i];
                sorted_indices[i] = sorted_indices[j];
                sorted_indices[j] = temp;
            }
        }
    }

    for (int i = 0; i < 26; i++) {
        map[sorted_indices[i]] = english_freq_order[i];
    }
}

// Function to decrypt using a given frequency map
void decrypt_with_map(const char *ciphertext, const char *map, char *plaintext) {
    for (int i = 0; ciphertext[i] != '\0'; i++) {
        if (isalpha(ciphertext[i])) {
            int index = toupper(ciphertext[i]) - 'A';
            if (isupper(ciphertext[i])) {
                plaintext[i] = map[index];
            } else {
                plaintext[i] = tolower(map[index]);
            }
        } else {
            plaintext[i] = ciphertext[i];
        }
    }
    plaintext[strlen(ciphertext)] = '\0';
}

// Function to print the top N possible plaintexts
void print_top_plaintexts(const char *ciphertext, int top_n) {
    int freq[26];
    char map[26];
    char plaintext[256];

    count_frequencies(ciphertext, freq);
    sort_and_map(freq, map);

    for (int i = 0; i < top_n; i++) {
        // Shift the frequency map for each iteration
        char shifted_map[26];
        for (int j = 0; j < 26; j++) {
            shifted_map[j] = map[(j + i) % 26];
        }
        decrypt_with_map(ciphertext, shifted_map, plaintext);
        printf("Possible plaintext %d: %s\n", i + 1, plaintext);
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

    print_top_plaintexts(ciphertext, top_n);

    return 0;
}

