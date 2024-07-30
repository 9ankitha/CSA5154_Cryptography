import string
from collections import Counter

# Frequency of letters in the English language
ENGLISH_FREQ = {
    'E': 12.70, 'T': 9.06, 'A': 8.17, 'O': 7.51, 'I': 6.97,
    'N': 6.75, 'S': 6.33, 'H': 6.09, 'R': 5.99, 'D': 4.25,
    'L': 4.03, 'C': 2.78, 'U': 2.76, 'M': 2.41, 'W': 2.36,
    'F': 2.23, 'G': 2.02, 'Y': 1.97, 'P': 1.93, 'B': 1.29,
    'V': 0.98, 'K': 0.77, 'J': 0.15, 'X': 0.15, 'Q': 0.10, 'Z': 0.07
}

def calculate_frequency(text):
    text = text.upper()
    text = ''.join(filter(str.isalpha, text))
    counter = Counter(text)
    total = sum(counter.values())
    freq = {char: count / total * 100 for char, count in counter.items()}
    return freq

def frequency_score(text):
    cipher_freq = calculate_frequency(text)
    score = 0
    for char in string.ascii_uppercase:
        cipher_char_freq = cipher_freq.get(char, 0)
        english_char_freq = ENGLISH_FREQ.get(char, 0)
        score += abs(cipher_char_freq - english_char_freq)
    return score

def decrypt_caesar_cipher(ciphertext, shift):
    decrypted_text = []
    for char in ciphertext:
        if char.isalpha():
            shifted = ord(char.upper()) - shift
            if shifted < ord('A'):
                shifted += 26
            decrypted_text.append(chr(shifted))
        else:
            decrypted_text.append(char)
    return ''.join(decrypted_text)

def generate_possible_plaintexts(ciphertext, top_n=10):
    possible_plaintexts = []
    for shift in range(26):
        plaintext = decrypt_caesar_cipher(ciphertext, shift)
        score = frequency_score(plaintext)
        possible_plaintexts.append((plaintext, score))
    
    possible_plaintexts.sort(key=lambda x: x[1])
    return possible_plaintexts[:top_n]

def main():
    ciphertext = input("Enter the ciphertext: ")
    top_n = int(input("Enter the number of possible plaintexts to display: "))
    
    possible_plaintexts = generate_possible_plaintexts(ciphertext, top_n)
    
    for i, (plaintext, score) in enumerate(possible_plaintexts, start=1):
        print(f"Plaintext {i}: {plaintext} (Score: {score})")

if __name__ == "__main__":
    main()
