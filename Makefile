CC = gcc
Flag = -Wall -Wextra -Werror

Target:To_Do_List

To_Do_List: src/main.o src/task.o src/files_save.o src/caesar_cipher.o
	$(CC) $(Flag) -c src/main.c -o src/main.o
	$(CC) $(Flag) -c src/task.c -o src/task.o
	$(CC) $(Flag) -c src/caesar_cipher.c -o src/caesar_cipher.o
	$(CC) $(Flag) -c src/files_save.c -o src/files_save.o
	$(CC) $(Flag) src/main.o src/task.o src/files_save.o src/caesar_cipher.o -o start/To_Do_List
	rm src/main.o src/task.o src/files_save.o src/caesar_cipher.o
clean:
	rm start/To_Do_List