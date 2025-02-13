#ifndef FILES_SAVE_H
#define FILES_SAVE_H

#include "task.h"

extern void Save_Tasks(const struct TaskList *list, const char *filename);
extern int Load_Tasks(struct TaskList *list, const char *filename); 

#endif