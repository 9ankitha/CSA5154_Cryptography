from Crypto.Cipher import AES
from Crypto.Util.Padding import pad
from Crypto.Random import get_random_bytes

def generate_subkeys(block_size):
    # Create a block of all zeros
    zero_block = bytes(block_size // 8)
    
    # Initialize AES cipher in ECB mode
    cipher = AES.new(get_random_bytes(16), AES.MODE_ECB)
    
    # Encrypt the zero block
    L = cipher.encrypt(zero_block)
    
    # Generate the first subkey K1
    K1 = left_shift(L, block_size)
    
    # Generate the second subkey K2
    K2 = left_shift(K1, block_size)
    
    return K1, K2

def left_shift(block, block_size):
    """ Perform a left shift of one bit on the block. """
    shift = (int.from_bytes(block, byteorder='big') << 1) & ((1 << block_size) - 1)
    shifted_block = shift.to_bytes(block_size // 8, byteorder='big')
    
    # Determine the constant to XOR with
    if block_size == 128:
        constant = 0x87
    elif block_size == 64:
        constant = 0x1b
    else:
        raise ValueError("Unsupported block size")
    
    # Check if we need to XOR with the constant
    if (block[0] & 0x80) != 0:
        shifted_block = bytes(b ^ (constant if i == 0 else 0) for i, b in enumerate(shifted_block))
    
    return shifted_block

def main():
    block_size = 128  # Can be set to 64 or 128 bits
    K1, K2 = generate_subkeys(block_size)
    
    print(f"Subkey K1: {K1.hex()}")
    print(f"Subkey K2: {K2.hex()}")

if __name__ == "__main__":
    main()
