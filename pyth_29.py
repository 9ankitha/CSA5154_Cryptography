import numpy as np

# Constants
BLOCK_SIZE = 1024  # Block size in bits
LANE_SIZE = 64  # Each lane size in bits
NUM_LANES = BLOCK_SIZE // LANE_SIZE  # Number of lanes
NUM_ROWS = 5  # Number of rows in the SHA-3 state matrix
NUM_COLS = 5  # Number of columns in the SHA-3 state matrix

def initialize_state():
    """Initialize the SHA-3 state matrix with zeros for capacity lanes."""
    state = np.zeros((NUM_ROWS, NUM_COLS, LANE_SIZE), dtype=np.uint8)
    return state

def absorb_block(state, block):
    """Absorb a message block into the state."""
    for i in range(NUM_LANES):
        row = i // NUM_COLS
        col = i % NUM_COLS
        state[row, col] ^= block[i * LANE_SIZE:(i + 1) * LANE_SIZE]

def print_state(state):
    """Print the state matrix."""
    for row in state:
        print(" ".join("".join(f"{x:02x}" for x in lane) for lane in row))

def main():
    # Initialize state
    state = initialize_state()
    
    # Example block with each lane having at least one non-zero bit
    block = np.random.randint(0, 256, size=BLOCK_SIZE // 8, dtype=np.uint8)  # Random non-zero block
    print("Initial state:")
    print_state(state)

    # Absorb the block
    absorb_block(state, block)
    print("\nState after absorbing the block:")
    print_state(state)

    # Count the steps to ensure all lanes have at least one non-zero bit
    steps = 0
    while np.any(state == 0):
        steps += 1
        # Create a new random block
        block = np.random.randint(0, 256, size=BLOCK_SIZE // 8, dtype=np.uint8)
        absorb_block(state, block)

    print(f"\nAll lanes have at least one non-zero bit after {steps} steps.")
    print_state(state)

if __name__ == "__main__":
    main()
