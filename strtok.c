#include "main.h"
#include <stdio.h>
#include <stdlib.h>
/*
*Author: Chillexy Steven   
*Program: WinMingle Community C Training
*Description: creates a program that scans through strings with a specified delimeter and returs the strings separetly
*@delimeter: the charactee to scan the string with
*UCALLER IS RESPONSIBLE FOR FREEING MEMORY
*/
char **_strtok(char *str, char *delim)
{
	char **strng = NULL;
	int i = 0;
	int start = 0;
	int token = 0;
	int len = 0;
	int k =0;
	int j = 0;
	int count = 0;
	int is_delim = 0;
	int in_token = 0;
	/*process to aquire each string count*/
	while (str[i])
	{
		is_delim = 0;
		j = 0;
		while (delim[j])/*compare each string characters with delimeter character*/
		{
			if (str[i] == delim[j])
			{
				is_delim = 1;
				break;
			}
			j++;
		}
		if (is_delim)/*if character is delimeter turn-off count*/
			in_token = 0;
		else if (!in_token)/* if character not delimeter increase count once by one*/
		{
			count++;
			in_token = 1;
		}
		i++;
	}
	/*__end__of___countng__process*/
	strng = malloc(sizeof(*strng) * (count + 1));
	if (strng == NULL)
		return (NULL);
	count = 0;
	/**/
	i = 0;
	while (str[i])
	{
		is_delim = 0;
		j = 0;
		while (delim[j])
		{
			if (str[i] == delim[j])
			{
				is_delim = 1;
				break;
			}
			j++;
		}
		if (is_delim)/*if on delimeter then... */
		{
			if (token == 1)/*to avoid duplicate allocations*/
			{
				k = 0;
				strng[count] = malloc(sizeof(*strng[count]) * (len + 1));
				if (strng[count] == NULL)/*allocation failure handler*/
				{
					while (count > 0)
					{
						count--;
						free(strng[count]);
					}
					free(strng);
					return (NULL);
				}
				while (k < len)
				{
					strng[count][k] = str[start + k];
					k++;
				}
				strng[count][k] = '\0';
				count++;
			}
			token = 0;/*we're definately not on the wanted character/string*/
		}
		else if (!is_delim)/*if not on delimeter then...*/
		{
			if (token == 0)/*checks that token has been reset before carrying out commands*/
			{
				start = i;/*knows where to start from whenever we get to delimeter to start the next word scanning*/
				token = 1;/*set character on*/
				len = 0;
			}

			len++;/*gets the length of each words tokenized by delimeter*/
		}
		i++;
	}
	if (token == 1)
	{
		k = 0;
		strng[count] = malloc(sizeof(*strng[count]) * (len + 1));
		if (strng[count] == NULL)
		{
			while (count > 0)
			{
				count--;
				free(strng[count]);
			}
			free(strng);
			return (NULL);
		}
		while (k < len)
		{
			strng[count][k] = str[start + k];
			k++;
		}
		strng[count][k] = '\0';
		count++;
	}
	strng[count] = NULL;
	return (strng);
}
