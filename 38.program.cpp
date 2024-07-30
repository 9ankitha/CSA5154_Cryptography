#include <stdio.h>
#include <stdlib.h>

// Function to perform matrix multiplication
void matrix_multiply(int *a, int *b, int *result, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            result[i * size + j] = 0;
            for (int k = 0; k < size; k++) {
                result[i * size + j] += a[i * size + k] * b[k * size + j];
            }
            result[i * size + j] %= 26;
        }
    }
}

// Function to find the modular inverse of a number under modulo 26
int mod_inverse(int a, int m) {
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1) {
            return x;
        }
    }
    return -1;
}

// Function to find the determinant of a matrix
int determinant(int *matrix, int size) {
    if (size == 2) {
        return (matrix[0] * matrix[3] - matrix[1] * matrix[2]) % 26;
    } else if (size == 3) {
        int det = matrix[0] * (matrix[4] * matrix[8] - matrix[5] * matrix[7]) -
                  matrix[1] * (matrix[3] * matrix[8] - matrix[5] * matrix[6]) +
                  matrix[2] * (matrix[3] * matrix[7] - matrix[4] * matrix[6]);
        return det % 26;
    }
    return 0;
}

// Function to find the inverse of a 2x2 matrix under modulo 26
void inverse_matrix(int *matrix, int *inverse, int size) {
    int det = determinant(matrix, size);
    int det_inv = mod_inverse(det, 26);

    if (size == 2) {
        inverse[0] = (matrix[3] * det_inv) % 26;
        inverse[1] = (-matrix[1] * det_inv + 26) % 26;
        inverse[2] = (-matrix[2] * det_inv + 26) % 26;
        inverse[3] = (matrix[0] * det_inv) % 26;
    } else if (size == 3) {
        // Inverse matrix calculation for 3x3 is more complex; implementing the adjugate method here
        int adj[9];

        adj[0] = (matrix[4] * matrix[8] - matrix[5] * matrix[7]) % 26;
        adj[1] = (matrix[2] * matrix[7] - matrix[1] * matrix[8]) % 26;
        adj[2] = (matrix[1] * matrix[5] - matrix[2] * matrix[4]) % 26;
        adj[3] = (matrix[5] * matrix[6] - matrix[3] * matrix[8]) % 26;
        adj[4] = (matrix[0] * matrix[8] - matrix[2] * matrix[6]) % 26;
        adj[5] = (matrix[2] * matrix[3] - matrix[0] * matrix[5]) % 26;
        adj[6] = (matrix[3] * matrix[7] - matrix[4] * matrix[6]) % 26;
        adj[7] = (matrix[1] * matrix[6] - matrix[0] * matrix[7]) % 26;
        adj[8] = (matrix[0] * matrix[4] - matrix[1] * matrix[3]) % 26;

        for (int i = 0; i < 9; i++) {
            adj[i] = (adj[i] * det_inv) % 26;
            if (adj[i] < 0) adj[i] += 26;
        }

        for (int i = 0; i < 9; i++) {
            inverse[i] = adj[i];
        }
    }
}

// Function to solve the Hill cipher using known plaintext attack
void solve_hill_cipher(int *plaintext_matrix, int *ciphertext_matrix, int size) {
    int inverse_plaintext_matrix[9];
    inverse_matrix(plaintext_matrix, inverse_plaintext_matrix, size);

    int key_matrix[9];
    matrix_multiply(inverse_plaintext_matrix, ciphertext_matrix, key_matrix, size);

    printf("Key matrix:\n");
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            printf("%d ", key_matrix[i * size + j]);
        }
        printf("\n");
    }
}

int main() {
    int size;
    printf("Enter the matrix size (2 or 3): ");
    scanf("%d", &size);

    int plaintext_matrix[9], ciphertext_matrix[9];
    
    printf("Enter the plaintext matrix:\n");
    for (int i = 0; i < size * size; i++) {
        scanf("%d", &plaintext_matrix[i]);
    }

    printf("Enter the ciphertext matrix:\n");
    for (int i = 0; i < size * size; i++) {
        scanf("%d", &ciphertext_matrix[i]);
    }

    solve_hill_cipher(plaintext_matrix, ciphertext_matrix, size);

    return 0;
}

