#include "files_save.h"
#include "caesar_cipher.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PASSWORD_FILE "Save/password.log"
#define MAX_PASSWORD_ATTEMPTS 3
#define XOR_KEY 42 

void bitwise_encrypt_decrypt(char *data, int key) {
    for (size_t i = 0; i < strlen(data); i++) {
        data[i] ^= key; 
    }
}

void create_password() {
    char password[100];
    printf("Файл с задачами не найден. Создайте новый пароль: ");
    fgets(password, sizeof(password), stdin);
    password[strcspn(password, "\n")] = '\0';

    bitwise_encrypt_decrypt(password, XOR_KEY);

    FILE *file = fopen(PASSWORD_FILE, "w");
    if (!file) {
        perror("Ошибка при создании файла пароля");
        return;
    }
    fprintf(file, "%s", password);
    fclose(file);

    printf("Пароль успешно создан.\n");
}

int check_password() {
    char saved_password[100];
    char input[100];
    int attempts = 0;

    FILE *file = fopen(PASSWORD_FILE, "r");
    if (!file) {
        printf("Ошибка при чтении файла пароля.\n");
        return 0;
    }
    fgets(saved_password, sizeof(saved_password), file);
    fclose(file);
    saved_password[strcspn(saved_password, "\n")] = '\0';

    bitwise_encrypt_decrypt(saved_password, XOR_KEY);

    while (attempts < MAX_PASSWORD_ATTEMPTS) {
        printf("Введите пароль: ");
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = '\0';

        if (strcmp(input, saved_password) == 0) {
            return 1;
        } else {
            attempts++;
            printf("Неверный пароль. Осталось попыток: %d\n", MAX_PASSWORD_ATTEMPTS - attempts);
        }
    }

    return 0;
}

void Save_Tasks(const struct TaskList *list, const char *filename) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        perror("Ошибка при открытии файла для записи");
        return;
    }

    for (int i = 0; i < list->count; i++) {
        fprintf(file, "%d|%s\n", list->tasks[i].isCompleted, list->tasks[i].Task);
    }

    fclose(file);

    cryptFile(filename, "temp.txt", 3);
    remove(filename);
    rename("temp.txt", filename);
}

int Load_Tasks(struct TaskList *list, const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        create_password();
        return 1;
    }

    if (!check_password()) {
        printf("Неверный пароль. Файл будет удален.\n");
        remove(filename);
        return 0;
    }

    decryptFile(filename, "temp.txt", 3);
    fclose(file);

    file = fopen("temp.txt", "r");
    if (!file) {
        perror("Ошибка при открытии дешифрованного файла");
        return 0;
    }

    char line[MAX_TASK_LENGTH + 10];
    while (fgets(line, sizeof(line), file)) {
        line[strcspn(line, "\n")] = '\0';
        int isCompleted;
        char Task[MAX_TASK_LENGTH];
        sscanf(line, "%d|%[^\n]", &isCompleted, Task);
        add_task(list, Task);
        list->tasks[list->count - 1].isCompleted = isCompleted;
    }

    fclose(file);
    remove("temp.txt");
    return 1;
}