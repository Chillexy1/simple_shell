#include "shell.h"
/*
*Author: Chillexy Steven  
*Program: WinMingle Community C Training
*Description: this a custom function that returns the length of a string
*/
int _strlen(char *str)
{
	int i = 0;
	while (str && str[i])
		i++;
	return (i);
}
