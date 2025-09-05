# RSA-Algorithm-Implementation
# RSA CLI Tool 

A command-line implementation of the **RSA algorithm** in C++.  
The project includes **key generation, encryption, decryption**, and an optimization using the **Chinese Remainder Theorem (CRT)**.  

This project was built to deepen understanding of number theory, modular arithmetic, and applied cryptography.  
It is intended for **educational purposes only**; the key sizes are small and not secure for production use.  

---

## Features
- Key generation (public and private keys)  
- Encryption of ASCII text messages into ciphertext blocks  
- Decryption of ciphertext back into text  
- Optimized decryption using the Chinese Remainder Theorem (CRT)  
- Lightweight single-binary CLI  

---

## Installation

Clone the repository and compile with `g++`:

```bash
git clone https://github.com/Anirudh-cheedella/RSA-Algorithm-Implementation
cd rsa-cli
g++ src.cpp -o rsa
