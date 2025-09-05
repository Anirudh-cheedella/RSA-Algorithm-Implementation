#include <bits/stdc++.h>
using namespace std;

// Modular exponentiation
long long modexp(long long base, long long exp, long long mod) {
    long long result = 1;
    base %= mod;
    while (exp > 0) {
        if (exp & 1) result = (result * base) % mod;
        base = (base * base) % mod;
        exp >>= 1;
    }
    return result;
}

// Extended Euclidean Algorithm
long long gcdExtended(long long a, long long b, long long &x, long long &y) {
    if (a == 0) { x = 0; y = 1; return b; }
    long long x1, y1;
    long long g = gcdExtended(b % a, a, x1, y1);
    x = y1 - (b / a) * x1;
    y = x1;
    return g;
}

long long modInverse(long long a, long long m) {
    long long x, y;
    long long g = gcdExtended(a, m, x, y);
    if (g != 1) return -1;
    return (x % m + m) % m;
}

// RSA key structure
struct RSAKey {
    long long e, d, n, p, q;
};

// Key generation (small primes for demo)
RSAKey generateKeys() {
    long long p = 61, q = 53;
    long long n = p * q;
    long long phi = (p - 1) * (q - 1);
    long long e = 17;
    long long d = modInverse(e, phi);
    return {e, d, n, p, q};
}

// Encrypt single integer
long long encryptInt(long long msg, RSAKey key) {
    return modexp(msg, key.e, key.n);
}

// Decrypt single integer (CRT optimization)
long long decryptInt(long long cipher, RSAKey key) {
    long long dp = key.d % (key.p - 1);
    long long dq = key.d % (key.q - 1);
    long long qinv = modInverse(key.q, key.p);

    long long m1 = modexp(cipher, dp, key.p);
    long long m2 = modexp(cipher, dq, key.q);

    long long h = (qinv * (m1 - m2)) % key.p;
    if (h < 0) h += key.p;

    return m2 + h * key.q;
}

// Encrypt string
vector<long long> encryptText(const string &text, RSAKey key) {
    vector<long long> cipher;
    for (char c : text) {
        cipher.push_back(encryptInt((int)c, key));
    }
    return cipher;
}

// Decrypt to string
string decryptText(const vector<long long> &cipher, RSAKey key) {
    string result;
    for (long long c : cipher) {
        result.push_back((char)decryptInt(c, key));
    }
    return result;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cout << "Usage:\n";
        cout << "  rsa-keygen\n";
        cout << "  rsa-encrypt <message>\n";
        cout << "  rsa-decrypt <c1,c2,c3,...>\n";
        return 0;
    }

    RSAKey key = generateKeys();
    string mode = argv[1];

    if (mode == "rsa-keygen") {
        cout << "Public Key (e, n): (" << key.e << ", " << key.n << ")\n";
        cout << "Private Key (d, n): (" << key.d << ", " << key.n << ")\n";
    }
    else if (mode == "rsa-encrypt") {
        if (argc < 3) { cout << "Provide a message!\n"; return 0; }
        string msg = argv[2];
        vector<long long> cipher = encryptText(msg, key);

        cout << "Ciphertext: ";
        for (size_t i = 0; i < cipher.size(); i++) {
            cout << cipher[i];
            if (i + 1 != cipher.size()) cout << ",";
        }
        cout << "\n";
    }
    else if (mode == "rsa-decrypt") {
        if (argc < 3) { cout << "Provide ciphertext values!\n"; return 0; }
        string cipherStr = argv[2];
        vector<long long> cipher;
        stringstream ss(cipherStr);
        string token;

        while (getline(ss, token, ',')) {
            cipher.push_back(stoll(token));
        }

        string msg = decryptText(cipher, key);
        cout << "Decrypted Message: " << msg << "\n";
    }
    else {
        cout << "Invalid mode!\n";
    }

    return 0;
}
