#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <locale.h>
#include "caesar_cipher.h"

wchar_t caesar_crypt(wchar_t ch, int key) {
    if (ch >= L'а' && ch <= L'я') {
        return L'а' + (ch - L'а' + key) % 32;
    }
    else if (ch >= L'А' && ch <= L'Я') {
        return L'А' + (ch - L'А' + key) % 32;
    }
    else if (ch == L'ё') {
        return L'а' + (33 + key) % 32;
    }
    else if (ch == L'Ё') {
        return L'А' + (33 + key) % 32;
    }
    else if (ch >= L'a' && ch <= L'z') {
        return L'a' + (ch - L'a' + key) % 26;
    }
    else if (ch >= L'A' && ch <= L'Z') {
        return L'A' + (ch - L'A' + key) % 26;
    }
    return ch;
}

wchar_t caesar_decrypt(wchar_t ch, int key) {
    if (ch >= L'а' && ch <= L'я') {
        return L'а' + (ch - L'а' - key + 32) % 32;
    }
    else if (ch >= L'А' && ch <= L'Я') {
        return L'А' + (ch - L'А' - key + 32) % 32;
    }
    else if (ch == L'ё') {
        return L'а' + (33 - key + 32) % 32;
    }
    else if (ch == L'Ё') {
        return L'А' + (33 - key + 32) % 32;
    }
    else if (ch >= L'a' && ch <= L'z') {
        return L'a' + (ch - L'a' - key + 26) % 26;
    }
    else if (ch >= L'A' && ch <= L'Z') {
        return L'A' + (ch - L'A' - key + 26) % 26;
    }
    return ch;
}

void cryptFile(const char *inputFile, const char *outputFile, int key) {
    FILE *fin = fopen(inputFile, "r");
    FILE *fout = fopen(outputFile, "w");

    if (!fin || !fout) {
        perror("Ошибка открытия файла");
        return;
    }

    wchar_t ch;
    while ((ch = fgetwc(fin)) != WEOF) {
        fputwc(caesar_crypt(ch, key), fout);
    }

    fclose(fin);
    fclose(fout);
}

void decryptFile(const char *inputFile, const char *outputFile, int key) {
    FILE *fin = fopen(inputFile, "r");
    FILE *fout = fopen(outputFile, "w");

    if (!fin || !fout) {
        perror("Ошибка открытия файла");
        return;
    }

    wchar_t ch;
    while ((ch = fgetwc(fin)) != WEOF) {
        fputwc(caesar_decrypt(ch, key), fout);
    }

    fclose(fin);
    fclose(fout);
}