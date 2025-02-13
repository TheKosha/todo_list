#ifndef TASK_H
#define TASK_H

#define MAX_TASK_LENGTH 100

struct Task {
    char Task[MAX_TASK_LENGTH];
    int isCompleted;            
};


struct TaskList {
    struct Task *tasks; 
    int count;          
};

void init_task(struct TaskList *list);
void add_task(struct TaskList *list, const char *Task);
void remove_task(struct TaskList *list, int index);
void print_tasks(const struct TaskList *list);
void free_task(struct TaskList *list);
void displayMenu();

#endif