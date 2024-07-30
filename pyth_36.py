import string
import math

def gcd(a, b):
    """Compute the greatest common divisor of a and b."""
    while b != 0:
        a, b = b, a % b
    return a

def mod_inverse(a, m):
    """Find the modular inverse of a under modulo m."""
    a = a % m
    for x in range(1, m):
        if (a * x) % m == 1:
            return x
    raise ValueError(f"No modular inverse for {a} under modulo {m}")

def affine_encrypt(plaintext, a, b):
    """Encrypt the plaintext using the Affine Caesar cipher."""
    if gcd(a, 26) != 1:
        raise ValueError(f"The value of 'a' must be coprime with 26. Got 'a' = {a}.")
    ciphertext = []
    for char in plaintext:
        if char.isalpha():
            p = ord(char.upper()) - ord('A')
            c = (a * p + b) % 26
            ciphertext.append(chr(c + ord('A')))
        else:
            ciphertext.append(char)
    return ''.join(ciphertext)

def affine_decrypt(ciphertext, a, b):
    """Decrypt the ciphertext using the Affine Caesar cipher."""
    if gcd(a, 26) != 1:
        raise ValueError(f"The value of 'a' must be coprime with 26. Got 'a' = {a}.")
    plaintext = []
    a_inv = mod_inverse(a, 26)
    for char in ciphertext:
        if char.isalpha():
            c = ord(char.upper()) - ord('A')
            p = (a_inv * (c - b)) % 26
            plaintext.append(chr(p + ord('A')))
        else:
            plaintext.append(char)
    return ''.join(plaintext)

def main():
    plaintext = input("Enter the plaintext: ")
    a = int(input("Enter the value of 'a' (must be coprime with 26): "))
    b = int(input("Enter the value of 'b': "))
    
    ciphertext = affine_encrypt(plaintext, a, b)
    print(f"Ciphertext: {ciphertext}")
    
    decrypted_text = affine_decrypt(ciphertext, a, b)
    print(f"Decrypted Text: {decrypted_text}")

if __name__ == "__main__":
    main()
