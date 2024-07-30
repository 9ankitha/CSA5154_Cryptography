import numpy as np

def mod_inv(a, m):
    """Compute the modular multiplicative inverse of a under modulo m."""
    a = a % m
    for x in range(1, m):
        if (a * x) % m == 1:
            return x
    raise ValueError(f"No modular inverse for {a} under modulo {m}")

def matrix_mod_inv(matrix, mod):
    """Compute the modular inverse of a matrix under modulo."""
    det = int(np.round(np.linalg.det(matrix)))
    det_inv = mod_inv(det, mod)
    matrix_mod_inv = (
        det_inv * np.round(det * np.linalg.inv(matrix)).astype(int) % mod
    )
    return matrix_mod_inv

def encrypt(plaintext, key_matrix):
    """Encrypt plaintext using the Hill cipher with the given key matrix."""
    n = key_matrix.shape[0]
    plaintext_vector = np.array([ord(char) - ord('A') for char in plaintext])
    ciphertext_vector = np.dot(key_matrix, plaintext_vector) % 26
    ciphertext = ''.join(chr(int(num) + ord('A')) for num in ciphertext_vector)
    return ciphertext

def chosen_plaintext_attack(plaintexts, ciphertexts):
    """Perform a chosen plaintext attack to recover the key matrix."""
    n = len(plaintexts[0])
    P = np.array([[ord(char) - ord('A') for char in pt] for pt in plaintexts]).T
    C = np.array([[ord(char) - ord('A') for char in ct] for ct in ciphertexts]).T

    P_inv = matrix_mod_inv(P, 26)
    K = np.dot(C, P_inv) % 26
    return K

def main():
    # Example plaintexts and ciphertexts
    plaintexts = ['HE', 'LL']
    ciphertexts = ['XM', 'OJ']
    
    key_matrix = chosen_plaintext_attack(plaintexts, ciphertexts)
    print("Recovered Key Matrix:")
    print(key_matrix)

if __name__ == "__main__":
    main()
