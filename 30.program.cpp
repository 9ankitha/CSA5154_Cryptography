#include <stdio.h>
#include <string.h>

// Function to calculate CBC MAC
void cbc_mac(unsigned char *key, unsigned char *message, int message_len, unsigned char *mac) {
    unsigned char prev_block[16] = {0};
    unsigned char curr_block[16];
    int i, j;

    for (i = 0; i < message_len; i += 16) {
        for (j = 0; j < 16; j++) {
            curr_block[j] = message[i + j];
        }

        for (j = 0; j < 16; j++) {
            curr_block[j] = curr_block[j] ^ prev_block[j];
        }

        // Encrypt current block with key (simplified)
        unsigned char encrypted_block[16];
        for (j = 0; j < 16; j++) {
            encrypted_block[j] = curr_block[j] ^ key[j];
        }

        for (j = 0; j < 16; j++) {
            prev_block[j] = encrypted_block[j];
        }
    }

    for (i = 0; i < 16; i++) {
        mac[i] = prev_block[i];
    }
}

int main() {
    unsigned char key[16] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
    unsigned char message[16] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
    unsigned char mac[16];

    cbc_mac(key, message, 16, mac);

    printf("MAC for one-block message: ");
    for (int i = 0; i < 16; i++) {
        printf("%02x", mac[i]);
    }
    printf("\n");

    unsigned char two_block_message[32];
    for (int i = 0; i < 16; i++) {
        two_block_message[i] = message[i];
        two_block_message[i + 16] = message[i] ^ mac[i];
    }

    unsigned char two_block_mac[16];
    cbc_mac(key, two_block_message, 32, two_block_mac);

    printf("MAC for two-block message: ");
    for (int i = 0; i < 16; i++) {
        printf("%02x", two_block_mac[i]);
    }
    printf("\n");

    return 0;
}
