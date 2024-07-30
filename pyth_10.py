def mod_inv_matrix(matrix, mod):
    """Find the modular inverse of a matrix under modulo."""
    det = int(round(np.linalg.det(matrix)))
    det_inv = pow(det, -1, mod)
    matrix_modulus_inv = (det_inv * Matrix(matrix).adjugate()) % mod
    return np.array(matrix_modulus_inv).astype(int)

def break_hill_cipher(plain_text_pairs, cipher_text_pairs, mod):
    """
    Given plaintext-ciphertext pairs, find the encryption matrix.
    
    Args:
        plain_text_pairs: List of plaintext vectors.
        cipher_text_pairs: List of corresponding ciphertext vectors.
        mod: The modulo used in the Hill cipher.
        
    Returns:
        The encryption matrix.
    """
    # Convert the list of pairs into matrices
    P = np.array(plain_text_pairs).T
    C = np.array(cipher_text_pairs).T
    
    # Ensure we have a square matrix for the plaintext
    assert P.shape[0] == P.shape[1], "Plaintext matrix must be square"
    
    # Find the modular inverse of the plaintext matrix
    P_inv = mod_inv_matrix(P, mod)
    
    # Calculate the encryption matrix
    K = (C.dot(P_inv)) % mod
    return K

# Example usage
if __name__ == "__main__":
    # Example known plaintext-ciphertext pairs (3x3 Hill cipher with modulo 26)
    plain_text_pairs = [
        [7, 8, 11],
        [19, 10, 16],
        [2, 3, 4]
    ]
    
    cipher_text_pairs = [
        [15, 14, 23],
        [8, 25, 3],
        [21, 18, 11]
    ]
    
    mod = 26  # For the standard English alphabet
    
    encryption_matrix = break_hill_cipher(plain_text_pairs, cipher_text_pairs, mod)
    print("Encryption Matrix:")
    print(encryption_matrix)
[DEBUG ON]
[DEBUG OFF]
