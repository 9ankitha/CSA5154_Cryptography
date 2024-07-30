from Crypto.Cipher import AES
from Crypto.Util.Padding import pad, unpad
from Crypto.Random import get_random_bytes

def cbc_mac(key, message):
    """Compute CBC-MAC for a given message with a given key."""
    cipher = AES.new(key, AES.MODE_ECB)
    
    # Pad the message to the block size
    padded_message = pad(message, AES.block_size)
    
    # Initial vector is all zeros for CBC-MAC
    iv = bytes(AES.block_size)
    
    # Encrypt the padded message in CBC mode
    cipher_cbc = AES.new(key, AES.MODE_CBC, iv)
    mac = cipher_cbc.encrypt(padded_message)[-AES.block_size:]
    
    return mac

def main():
    key = get_random_bytes(16)  # AES key for 128-bit block cipher
    message = b"This is a one-block message."

    # Compute CBC-MAC for the original message
    mac = cbc_mac(key, message)
    print(f"Original Message MAC: {mac.hex()}")

    # Compute X ⊕ T
    xor_message = bytes([m ^ t for m, t in zip(message, mac)])
    extended_message = message + xor_message

    # Compute CBC-MAC for the extended message
    extended_mac = cbc_mac(key, extended_message)
    print(f"Extended Message MAC: {extended_mac.hex()}")

    # Verify that MACs are the same
    print(f"MAC of original message: {mac.hex()}")
    print(f"MAC of extended message: {extended_mac.hex()}")
    print(f"MACs match: {mac == extended_mac}")

if __name__ == "__main__":
    main()
