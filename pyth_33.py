from Crypto.Cipher import DES
from Crypto.Util.Padding import pad, unpad
from Crypto.Random import get_random_bytes

def des_encrypt(plaintext, key):
    """Encrypt the plaintext using DES."""
    cipher = DES.new(key, DES.MODE_ECB)
    padded_text = pad(plaintext, DES.block_size)
    ciphertext = cipher.encrypt(padded_text)
    return ciphertext

def des_decrypt(ciphertext, key):
    """Decrypt the ciphertext using DES."""
    cipher = DES.new(key, DES.MODE_ECB)
    decrypted_padded_text = cipher.decrypt(ciphertext)
    plaintext = unpad(decrypted_padded_text, DES.block_size)
    return plaintext

def main():
    plaintext = b"This is a test message for DES encryption."
    
    # Ensure the plaintext is a multiple of 8 bytes (64 bits)
    if len(plaintext) % DES.block_size != 0:
        plaintext = pad(plaintext, DES.block_size)
    
    # DES key must be 8 bytes long (64 bits)
    key = get_random_bytes(8)
    
    print(f"Original Plaintext: {plaintext}")
    print(f"Key: {key.hex()}")

    # Encrypt
    ciphertext = des_encrypt(plaintext, key)
    print(f"Ciphertext: {ciphertext.hex()}")

    # Decrypt
    decrypted_text = des_decrypt(ciphertext, key)
    print(f"Decrypted Text: {decrypted_text.decode('utf-8')}")

if __name__ == "__main__":
    main()
