#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#include <locale.h>
#include "task.h"
#include "files_save.h"
#include "caesar_cipher.h"

#define FILENAME "Save/tasks.log"

void clear_screen() {
    printf("\033[H\033[J");
}

int main() {
    setlocale(LC_ALL, "");
    struct TaskList list;
    init_task(&list);

    if (!Load_Tasks(&list, FILENAME)) {
        printf("Не удалось загрузить задачи. Программа завершает работу.\n");
        return 1;
    }

    int choice;
    char input[MAX_TASK_LENGTH];

    while (1) {
        clear_screen();
        displayMenu();
        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1:
                clear_screen();
                print_tasks(&list);
                printf("\nНажмите Enter, чтобы вернуться в меню...");
                getchar();
                break;

            case 2:
                clear_screen();
                printf("Введите описание задачи: ");
                fgets(input, MAX_TASK_LENGTH, stdin);
                input[strcspn(input, "\n")] = '\0';
                add_task(&list, input);
                printf("Задача добавлена.\n");
                printf("\nНажмите Enter, чтобы вернуться в меню...");
                getchar();
                break;

            case 3:
                clear_screen();
                printf("Введите номер задачи для отметки как выполненной: ");
                int taskIndex;
                scanf("%d", &taskIndex);
                getchar();
                if (taskIndex > 0 && taskIndex <= list.count) {
                    list.tasks[taskIndex - 1].isCompleted = 1;
                    printf("Задача отмечена как выполненная.\n");
                } else {
                    printf("Неверный номер задачи!\n");
                }
                printf("\nНажмите Enter, чтобы вернуться в меню...");
                getchar();
                break;

            case 4:
                clear_screen();
                printf("Введите номер задачи для удаления: ");
                scanf("%d", &taskIndex);
                getchar();
                if (taskIndex > 0 && taskIndex <= list.count) {
                    remove_task(&list, taskIndex - 1);
                    printf("Задача удалена.\n");
                } else {
                    printf("Неверный номер задачи!\n");
                }
                printf("\nНажмите Enter, чтобы вернуться в меню...");
                getchar();
                break;

            case 5:
                clear_screen();
                Save_Tasks(&list, FILENAME);
                printf("Задачи сохранены. Выход из программы.\n");
                free_task(&list);
                return 0;

            default:
                printf("Попробуйте снова.\n");
                printf("\nНажмите Enter, чтобы продолжить...");
                getchar();
        }
    }

    return 0;
}