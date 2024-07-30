#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define LANE_SIZE 8 // Each lane is 64 bits (8 bytes)
#define NUM_LANES 25 // Total number of lanes (5x5 matrix)
#define BLOCK_SIZE 1024 // Block size in bits
#define NUM_CAPACITY_LANES 17 // Number of lanes in capacity portion (25 lanes - (BLOCK_SIZE / LANE_SIZE) lanes)

typedef uint8_t lane_t[LANE_SIZE];

void initialize_state(lane_t state[NUM_LANES]) {
    // Initialize all lanes to zero
    memset(state, 0, NUM_LANES * LANE_SIZE);
}

void process_block(lane_t state[NUM_LANES], lane_t block[NUM_LANES]) {
    // XOR the block with the state
    for (int i = 0; i < NUM_LANES; i++) {
        for (int j = 0; j < LANE_SIZE; j++) {
            state[i][j] ^= block[i][j];
        }
    }
}

int check_capacity_lanes(lane_t state[NUM_LANES]) {
    // Check if all lanes in the capacity portion have at least one nonzero bit
    for (int i = (BLOCK_SIZE / LANE_SIZE); i < NUM_LANES; i++) {
        int is_zero = 1;
        for (int j = 0; j < LANE_SIZE; j++) {
            if (state[i][j] != 0) {
                is_zero = 0;
                break;
            }
        }
        if (is_zero) {
            return 0;
        }
    }
    return 1;
}

int main() {
    lane_t state[NUM_LANES];
    initialize_state(state);

    int num_blocks = 0;

    // Assume each lane in the first message block (P0) has at least one nonzero bit
    lane_t block[NUM_LANES];
    for (int i = 0; i < NUM_LANES; i++) {
        for (int j = 0; j < LANE_SIZE; j++) {
            block[i][j] = 1; // Set to a nonzero value for simplicity
        }
    }

    while (!check_capacity_lanes(state)) {
        process_block(state, block);
        num_blocks++;
    }

    printf("Number of blocks processed until all capacity lanes have at least one nonzero bit: %d\n", num_blocks);

    return 0;
}
