from Crypto.Cipher import AES
from Crypto.Util.Padding import pad, unpad
from Crypto.Random import get_random_bytes

def encrypt_ecb(plaintext, key):
    cipher = AES.new(key, AES.MODE_ECB)
    padded_text = pad(plaintext, AES.block_size)
    ciphertext = cipher.encrypt(padded_text)
    return ciphertext

def decrypt_ecb(ciphertext, key):
    cipher = AES.new(key, AES.MODE_ECB)
    decrypted_padded_text = cipher.decrypt(ciphertext)
    plaintext = unpad(decrypted_padded_text, AES.block_size)
    return plaintext

def encrypt_cbc(plaintext, key):
    iv = get_random_bytes(AES.block_size)
    cipher = AES.new(key, AES.MODE_CBC, iv)
    padded_text = pad(plaintext, AES.block_size)
    ciphertext = iv + cipher.encrypt(padded_text)
    return ciphertext

def decrypt_cbc(ciphertext, key):
    iv = ciphertext[:AES.block_size]
    ciphertext = ciphertext[AES.block_size:]
    cipher = AES.new(key, AES.MODE_CBC, iv)
    decrypted_padded_text = cipher.decrypt(ciphertext)
    plaintext = unpad(decrypted_padded_text, AES.block_size)
    return plaintext

def encrypt_cfb(plaintext, key):
    iv = get_random_bytes(AES.block_size)
    cipher = AES.new(key, AES.MODE_CFB, iv)
    ciphertext = iv + cipher.encrypt(plaintext)
    return ciphertext

def decrypt_cfb(ciphertext, key):
    iv = ciphertext[:AES.block_size]
    ciphertext = ciphertext[AES.block_size:]
    cipher = AES.new(key, AES.MODE_CFB, iv)
    plaintext = cipher.decrypt(ciphertext)
    return plaintext

def main():
    plaintext = b"This is a test message for block cipher modes."
    key = get_random_bytes(16)  # AES-128

    print("Original Plaintext:", plaintext)

    # ECB Mode
    ecb_ciphertext = encrypt_ecb(plaintext, key)
    ecb_decrypted = decrypt_ecb(ecb_ciphertext, key)
    print("ECB Encrypted:", ecb_ciphertext)
    print("ECB Decrypted:", ecb_decrypted)

    # CBC Mode
    cbc_ciphertext = encrypt_cbc(plaintext, key)
    cbc_decrypted = decrypt_cbc(cbc_ciphertext, key)
    print("CBC Encrypted:", cbc_ciphertext)
    print("CBC Decrypted:", cbc_decrypted)

    # CFB Mode
    cfb_ciphertext = encrypt_cfb(plaintext, key)
    cfb_decrypted = decrypt_cfb(cfb_ciphertext, key)
    print("CFB Encrypted:", cfb_ciphertext)
    print("CFB Decrypted:", cfb_decrypted)

if __name__ == "__main__":
    main()
