import random
import sympy

def diffie_hellman(p, g, alice_secret, bob_secret):
    # Alice computes A = g^a mod p
    A = pow(g, alice_secret, p)
    # Bob computes B = g^b mod p
    B = pow(g, bob_secret, p)

    # Alice and Bob exchange A and B, then compute the shared secret
    alice_shared_key = pow(B, alice_secret, p)
    bob_shared_key = pow(A, bob_secret, p)

    return A, B, alice_shared_key, bob_shared_key

def main():
    # Public parameters
    p = sympy.nextprime(random.randint(100, 1000))  # A large prime number
    g = sympy.randprime(2, p)  # A primitive root modulo p

    # Alice and Bob's secret numbers
    alice_secret = random.randint(1, p-1)
    bob_secret = random.randint(1, p-1)

    print(f"Public parameters:\n p = {p}\n g = {g}")
    print(f"Alice's secret: {alice_secret}")
    print(f"Bob's secret: {bob_secret}")

    A, B, alice_shared_key, bob_shared_key = diffie_hellman(p, g, alice_secret, bob_secret)

    print(f"Alice's public value: {A}")
    print(f"Bob's public value: {B}")
    print(f"Alice's computed shared key: {alice_shared_key}")
    print(f"Bob's computed shared key: {bob_shared_key}")

    # Check if the computed keys match
    print(f"Shared keys match: {alice_shared_key == bob_shared_key}")

if __name__ == "__main__":
    main()
