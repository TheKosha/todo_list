CC = gcc
Flag = -Wall -Wextra -Werror

Target:To_Do_List

To_Do_List: src/main.o src/task.o src/todo_list.o src/utils.o
	$(CC) $(Flag) -c src/main.c -o src/main.o
	$(CC) $(Flag) -c src/task.c -o src/task.o
	$(CC) $(Flag) -c src/todo_list.c -o src/todo_list.o
	$(CC) $(Flag) -c src/utils.c -o src/utils.o
	$(CC) $(Flag) src/main.o src/task.o src/todo_list.o src/utils.o -o start/To_Do_List
	rm src/main.o src/task.o src/todo_list.o src/utils.o
clean:
	rm start/To_Do_List