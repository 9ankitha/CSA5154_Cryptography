from Crypto.PublicKey import RSA
from Crypto.Cipher import PKCS1_OAEP
from Crypto.Random import get_random_bytes

def rsa_encrypt(message, public_key):
    """Encrypt the message using RSA public key."""
    cipher = PKCS1_OAEP.new(public_key)
    encrypted_message = cipher.encrypt(message)
    return encrypted_message

def rsa_decrypt(encrypted_message, private_key):
    """Decrypt the message using RSA private key."""
    cipher = PKCS1_OAEP.new(private_key)
    decrypted_message = cipher.decrypt(encrypted_message)
    return decrypted_message

def encode_message(message):
    """Encode message as integer values (A=0, B=1, ..., Z=25)."""
    return [ord(char) - ord('A') for char in message.upper()]

def decode_message(encoded_message):
    """Decode integer values back to characters (0=A, 1=B, ..., 25=Z)."""
    return ''.join(chr(num + ord('A')) for num in encoded_message)

def main():
    # Generate RSA keys
    key = RSA.generate(2048)  # RSA key size
    public_key = key.publickey()
    private_key = key

    # Example message
    message = "HELLO"
    print(f"Original message: {message}")

    # Encode message
    encoded_message = encode_message(message)
    print(f"Encoded message: {encoded_message}")

    # Encrypt each integer separately
    encrypted_message = []
    for number in encoded_message:
        encrypted_number = rsa_encrypt(number.to_bytes(2, byteorder='big'), public_key)
        encrypted_message.append(encrypted_number)

    # Decrypt each number separately
    decrypted_message = []
    for encrypted_number in encrypted_message:
        decrypted_number = rsa_decrypt(encrypted_number, private_key)
        decrypted_message.append(int.from_bytes(decrypted_number, byteorder='big'))

    # Decode message
    decoded_message = decode_message(decrypted_message)
    print(f"Decrypted message: {decoded_message}")

if __name__ == "__main__":
    main()
