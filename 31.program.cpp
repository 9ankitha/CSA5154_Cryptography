#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define BLOCK_SIZE_64 8
#define BLOCK_SIZE_128 16

// Function to print data in hexadecimal format
void print_hex(const char *label, const uint8_t *data, size_t len) {
    printf("%s: ", label);
    for (size_t i = 0; i < len; i++) {
        printf("%02x", data[i]);
    }
    printf("\n");
}

// Simplified AES-like block encryption (substitution and permutation only)
void simple_aes_encrypt(const uint8_t *input, uint8_t *output, size_t len) {
    // Example substitution: simply reverse the bytes (not actual AES encryption)
    for (size_t i = 0; i < len; i++) {
        output[i] = input[len - 1 - i];
    }
}

// Function to left shift a block of data by 1 bit
void left_shift(uint8_t *output, const uint8_t *input, size_t len) {
    uint8_t carry = 0;
    for (int i = len - 1; i >= 0; i--) {
        output[i] = (input[i] << 1) | carry;
        carry = (input[i] & 0x80) ? 1 : 0;
    }
}

// CMAC subkey generation
void generate_subkeys(const uint8_t *key, size_t block_size, uint8_t *K1, uint8_t *K2) {
    uint8_t L[BLOCK_SIZE_128] = {0}; // Buffer to hold the result of encryption
    uint8_t zero_block[BLOCK_SIZE_128] = {0}; // All-zero block
    uint8_t const_R;

    // Set the constant R based on block size
    if (block_size == BLOCK_SIZE_64) {
        const_R = 0x1B;
    } else if (block_size == BLOCK_SIZE_128) {
        const_R = 0x87;
    } else {
        fprintf(stderr, "Unsupported block size\n");
        return;
    }

    // Encrypt the all-zero block
    simple_aes_encrypt(zero_block, L, block_size);

    print_hex("L", L, block_size);

    // Generate K1
    left_shift(K1, L, block_size);
    if (L[0] & 0x80) {
        K1[block_size - 1] ^= const_R;
    }

    // Generate K2
    left_shift(K2, K1, block_size);
    if (K1[0] & 0x80) {
        K2[block_size - 1] ^= const_R;
    }
}

int main() {
    uint8_t key[BLOCK_SIZE_128] = {0x00}; // Example key, normally should be random and secret
    uint8_t K1[BLOCK_SIZE_128], K2[BLOCK_SIZE_128];

    // Generate subkeys for 128-bit block size
    generate_subkeys(key, BLOCK_SIZE_128, K1, K2);
    print_hex("K1", K1, BLOCK_SIZE_128);
    print_hex("K2", K2, BLOCK_SIZE_128);

    // Generate subkeys for 64-bit block size
    uint8_t key_64[BLOCK_SIZE_64] = {0x00}; // Example key, normally should be random and secret
    uint8_t K1_64[BLOCK_SIZE_64], K2_64[BLOCK_SIZE_64];
    generate_subkeys(key_64, BLOCK_SIZE_64, K1_64, K2_64);
    print_hex("K1 (64-bit)", K1_64, BLOCK_SIZE_64);
    print_hex("K2 (64-bit)", K2_64, BLOCK_SIZE_64);

    return 0;
}
