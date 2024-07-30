#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Function to calculate (a^x) mod q
long long power(long long a, long long x, long long q) {
    long long res = 1;
    while (x > 0) {
        if (x % 2 == 1)
            res = (res * a) % q;
        a = (a * a) % q;
        x /= 2;
    }
    return res;
}

int main() {
    long long q = 23; // A prime number
    long long a = 5; // A primitive root of q

    // Alice selects a secret number x
    long long x = 4;
    long long X = power(a, x, q);

    // Bob selects a secret number y
    long long y = 3;
    long long Y = power(a, y, q);

    // Alice sends X to Bob
    // Bob sends Y to Alice

    // Alice calculates the key
    long long k1 = power(Y, x, q);

    // Bob calculates the key
    long long k2 = power(X, y, q);

    printf("Alice's secret number: %lld\n", x);
    printf("Bob's secret number: %lld\n", y);
    printf("Alice's public number: %lld\n", X);
    printf("Bob's public number: %lld\n", Y);
    printf("Alice's key: %lld\n", k1);
    printf("Bob's key: %lld\n", k2);

    return 0;
}
