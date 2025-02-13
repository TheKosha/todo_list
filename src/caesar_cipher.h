#ifndef CAESAR_CIPHER_H
#define CAESAR_CIPHER_H

#include <wchar.h>

wchar_t caesar_crypt(wchar_t ch, int key);
wchar_t caesar_decrypt(wchar_t ch, int key);
void cryptFile(const char *inputFile, const char *outputFile, int key);
void decryptFile(const char *inputFile, const char *outputFile, int key);

#endif