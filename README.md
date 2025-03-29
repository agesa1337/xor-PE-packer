# XOR Packer for PE Files

This project implements a simple XOR encryption and decryption mechanism for Portable Executable (PE) files. It allows you to encrypt and decrypt executable files using a user-defined XOR key.

## Description

This program reads an executable file, encrypts it using the XOR encryption algorithm, and saves the encrypted version as a new file. It is based on a simple XOR algorithm where each byte of the data is XORed with a key.

## Features

- XOR-based encryption and decryption of files
- The ability to read an executable file and save the encrypted file
- Easy-to-use C++ implementation

## Requirements

- C++11 or later
- A C++ compiler (e.g., GCC, MSVC, or Clang)
- Windows OS (for Windows-specific functions like `CreateProcessW`)

## Compilation

To compile the program, you can use a C++ compiler such as `g++` or `cl` (on Windows). Here is an example command using `g++`:

```bash
g++ -o xor_encrypt_decrypt CustomPacker.cpp
