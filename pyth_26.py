from cryptography.hazmat.primitives.asymmetric import rsa
from cryptography.hazmat.primitives import serialization
from cryptography.hazmat.primitives import hashes
from cryptography.hazmat.primitives.asymmetric import padding

def generate_keys():
    """Generate RSA public and private keys."""
    private_key = rsa.generate_private_key(
        public_exponent=65537,
        key_size=2048
    )
    public_key = private_key.public_key()
    return private_key, public_key

def serialize_key(key, private=False):
    """Serialize the key for storage or transmission."""
    if private:
        return key.private_bytes(
            encoding=serialization.Encoding.PEM,
            format=serialization.PrivateFormat.PKCS8,
            encryption_algorithm=serialization.NoEncryption()
        )
    else:
        return key.public_bytes(
            encoding=serialization.Encoding.PEM,
            format=serialization.PublicFormat.SubjectPublicKeyInfo
        )

def encrypt_message(message, public_key):
    """Encrypt a message using RSA public key."""
    encrypted_message = public_key.encrypt(
        message.encode(),
        padding.OAEP(
            mgf=padding.MGF1(algorithm=hashes.SHA256()),
            algorithm=hashes.SHA256(),
            label=None
        )
    )
    return encrypted_message

def decrypt_message(encrypted_message, private_key):
    """Decrypt a message using RSA private key."""
    decrypted_message = private_key.decrypt(
        encrypted_message,
        padding.OAEP(
            mgf=padding.MGF1(algorithm=hashes.SHA256()),
            algorithm=hashes.SHA256(),
            label=None
        )
    )
    return decrypted_message.decode()

def generate_new_keys(old_modulus):
    """Generate new RSA keys but use the same modulus (for demonstration)."""
    new_private_key = rsa.generate_private_key(
        public_exponent=65537,
        key_size=2048
    )
    new_public_key = new_private_key.public_key()
    # Note: This is not a secure approach in practice.
    return new_private_key, new_public_key

def main():
    # Generate initial RSA keys
    old_private_key, old_public_key = generate_keys()
    old_modulus = old_private_key.private_numbers().public_numbers.n

    # Encrypt and decrypt a message
    message = "Hello, Bob!"
    encrypted_message = encrypt_message(message, old_public_key)
    decrypted_message = decrypt_message(encrypted_message, old_private_key)

    print(f"Original message: {message}")
    print(f"Encrypted message: {encrypted_message}")
    print(f"Decrypted message: {decrypted_message}")

    # Simulate Bob generating new keys but keeping the old modulus
    new_private_key, new_public_key = generate_new_keys(old_modulus)

    # Encrypt and decrypt with new keys
    encrypted_message_new = encrypt_message(message, new_public_key)
    decrypted_message_new = decrypt_message(encrypted_message_new, new_private_key)

    print(f"Encrypted message with new keys: {encrypted_message_new}")
    print(f"Decrypted message with new keys: {decrypted_message_new}")

if __name__ == "__main__":
    main()
