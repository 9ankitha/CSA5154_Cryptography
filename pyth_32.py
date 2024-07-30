from Crypto.PublicKey import DSA
from Crypto.Signature import DSS
from Crypto.Hash import SHA256
from Crypto.Random import get_random_bytes

def dsa_sign(message, key):
    """Sign a message using DSA."""
    h = SHA256.new(message)
    signer = DSS.new(key, 'fips-186-3')
    signature = signer.sign(h)
    return signature

def dsa_verify(message, signature, key):
    """Verify a message using DSA."""
    h = SHA256.new(message)
    verifier = DSS.new(key, 'fips-186-3')
    try:
        verifier.verify(h, signature)
        return True
    except ValueError:
        return False

def main():
    # Generate a new DSA key
    key = DSA.generate(2048)
    print("Generated DSA key.")

    message = b"This is a test message for DSA."

    # Sign the message
    signature1 = dsa_sign(message, key)
    print(f"Signature 1: {signature1.hex()}")

    # Sign the message again to show different signatures
    signature2 = dsa_sign(message, key)
    print(f"Signature 2: {signature2.hex()}")

    # Verify the signatures
    is_valid1 = dsa_verify(message, signature1, key)
    is_valid2 = dsa_verify(message, signature2, key)
    
    print(f"Signature 1 is valid: {is_valid1}")
    print(f"Signature 2 is valid: {is_valid2}")

if __name__ == "__main__":
    main()
