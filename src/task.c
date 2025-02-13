#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "task.h"

void init_task(struct TaskList *list) {
    list->tasks = NULL;
    list->count = 0;
}

void add_task(struct TaskList *list, const char *Task) {
    list->count++;
    list->tasks = (struct Task *)realloc(list->tasks, list->count * sizeof(struct Task));

    strncpy(list->tasks[list->count - 1].Task, Task, MAX_TASK_LENGTH);
    list->tasks[list->count - 1].Task[MAX_TASK_LENGTH - 1] = '\0';
    list->tasks[list->count - 1].isCompleted = 0;
}

void remove_task(struct TaskList *list, int index) {
    if (index < 0 || index >= list->count) {
        return;
    }
    for (int i = index; i < list->count - 1; i++) {
        list->tasks[i] = list->tasks[i + 1];
    }
    list->count--;
    list->tasks = (struct Task *)realloc(list->tasks, list->count * sizeof(struct Task));
}

void print_tasks(const struct TaskList *list) {
    printf("Ваш список задач:\n");
    for (int i = 0; i < list->count; i++) {
        printf("%d. [%s] %s\n", i + 1, list->tasks[i].isCompleted ? "X" : " ", list->tasks[i].Task);
    }
}

void free_task(struct TaskList *list) {
    free(list->tasks);
    list->tasks = NULL;
    list->count = 0;
}


void displayMenu() {
    printf("\n-------Меню--------\n\n");
    printf("1. Показать задачи\n");
    printf("2. Добавить задачу\n");
    printf("3. Отметить выполненную\n");
    printf("4. Удалить задачу\n");
    printf("5. Сохранить и выйти\n");
    printf("\n-------------------\n");
    printf("Выберите действие: ");
}