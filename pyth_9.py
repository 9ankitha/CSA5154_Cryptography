from Crypto.Cipher import DES
from Crypto.Random import get_random_bytes
import binascii

def pad(text):
    while len(text) % 8 != 0:
        text += ' '
    return text

def encrypt_des(plaintext, key):
    des = DES.new(key, DES.MODE_ECB)
    padded_text = pad(plaintext)
    encrypted_text = des.encrypt(padded_text.encode())
    return binascii.hexlify(encrypted_text).decode()

def decrypt_des(ciphertext, key):
    des = DES.new(key, DES.MODE_ECB)
    encrypted_text = binascii.unhexlify(ciphertext)
    decrypted_text = des.decrypt(encrypted_text)
    return decrypted_text.decode().rstrip(' ')

if __name__ == "__main__":
    key = b'8bytekey'  
    plaintext = "Hello DES World"
    
    encrypted_text = encrypt_des(plaintext, key)
    print("Encrypted:", encrypted_text)
    
    decrypted_text = decrypt_des(encrypted_text, key)
    print("Decrypted:", decrypted_text)
