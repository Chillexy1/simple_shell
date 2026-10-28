#ifndef MAIN_H
#define MAIN_H

#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>

int simple_shell(int argc, char *argx[]);
char *my_getline(void);
void exec_command(char *dir, char *command[]);
int _strlen(char *str);
void str(long int n, char *s);

#endif /* MAIN_H */
