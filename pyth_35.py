import random
import string

def generate_random_key(length):
    """Generate a random key of given length where each number is between 0 and 25."""
    return [random.randint(0, 25) for _ in range(length)]

def encrypt(plaintext, key):
    """Encrypt the plaintext using the one-time pad Vigenère cipher."""
    ciphertext = []
    for i, char in enumerate(plaintext):
        if char.isalpha():
            shift = key[i]
            char = char.upper()
            encrypted_char = chr(((ord(char) - ord('A') + shift) % 26) + ord('A'))
            ciphertext.append(encrypted_char)
        else:
            ciphertext.append(char)
    return ''.join(ciphertext)

def decrypt(ciphertext, key):
    """Decrypt the ciphertext using the one-time pad Vigenère cipher."""
    plaintext = []
    for i, char in enumerate(ciphertext):
        if char.isalpha():
            shift = key[i]
            char = char.upper()
            decrypted_char = chr(((ord(char) - ord('A') - shift + 26) % 26) + ord('A'))
            plaintext.append(decrypted_char)
        else:
            plaintext.append(char)
    return ''.join(plaintext)

def main():
    plaintext = input("Enter the plaintext: ")
    key_length = len(plaintext)
    key = generate_random_key(key_length)
    
    ciphertext = encrypt(plaintext, key)
    decrypted_text = decrypt(ciphertext, key)
    
    print(f"Generated Key: {key}")
    print(f"Ciphertext: {ciphertext}")
    print(f"Decrypted Text: {decrypted_text}")

if __name__ == "__main__":
    main()
