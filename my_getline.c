#include "main.h"
/*
*Author: Chillexy Steven    
*Program: WinMingle Community C Training
*Description: A cutsom getline function
*/
char *my_getline(void)
{
	int i = 0, found = 0, n, j, k, l, len;
	char buff[1024];
	static char leftover[1024];
	static char line[1024];
	if (leftover[0] != '\0') /* copy leftover into line if leftover contains words before the read call */
	{
		l = 0;
		while (leftover[l])
		{
			if (leftover[l] == '\n')
			{
				found = 1;
				j = 0;
				while (j <= l)
				{
					line[j] = leftover[j];/*copy leftover to line*/
					j++;
				}
				line[j] = '\0';
				j = 0;
				k = l + 1;
				while (leftover[k])
				{
					leftover[j] = leftover[k];/*move the leftover to begining*/
					k++;
					j++;
				}
				leftover[j] = '\0';
				break;
			}
			l++;
		}
		if (!found)
		{
			j = 0;
			while (j <= l)
			{
				line[j] = leftover[j];
				j++;
			}
			line[j] = '\0';
			len = _strlen(line);
			leftover[0] = '\0';
		}
		while (!found)
		{	
			n = read(0, buff, 1024);
			buff[n] = '\0';
			i = 0;
			while (i < n)
			{
				if (buff[i] == '\n')
				{
					found = 1;
					k = 0;
					while (k <= i)
					{
						line[len] = buff[k];
						k++;
						len++;
					}
					line[len] = '\0';/* save first line to \n to line*/
					/*copy remainder to leftover*/
					j = 0;
					k = i + 1;
					while (buff[k])
					{
						leftover[j] = buff[k];/*copy leftover words to leftover variable*/
						j++;
						k++;
					}
					leftover[j] = '\0';
					break;
				}
				i++;
			}
			if (!found)
			{
				j = 0;
				while (buff[j])
				{
					line[len] = buff[j];/*append to line if \n not found*/
					len++;
					j++;
				}
				line[len] = '\0';
			}
		}
	}
	else
	{
		n = read(0, buff, 1024);
		buff[n] = '\0'; /* make the byte a valid c string */
		i = 0;
		while (i < n)
		{
			/* inspect buff for the \n character*/
			if (buff[i] == '\n')
			{
				found = 1;
				l = 0;
				while (l <= i)
				{
					line[l] = buff[l];
					l++;
				}
				line[l] = '\0'; /* save the first line */
				j = 0;
				k = i + 1;
				while (buff[k] != '\0')
				{
					leftover[j] = buff[k];
					j++;
					k++;
				}
				leftover[j] = '\0'; /* save the leftover */
				break;
			}
			i++;
		}
		while (!found)/* implement contion if \n isn't found */
		{
			n = read(0, buff, 1024);
			buff[n] = '\0';
			j = 0;
			len = _strlen(line);
			while (j < n)
			{
				if (buff[j] == '\n')
				{
					found = 1;
					l = 0;
					while (l <= j)
					{
						line[len] = buff[l]; /*append first line of words to line */ 
						l++;
						len++;
					}
					line[len] = '\0';
					l = 0;
					k = j +1;
					while (buff[k])
					{
						leftover[l] = buff[k];/* move remaining words to leftover */
						l++;
						k++;
					}
					leftover[l] = '\0';
					break;
				}
				j++;
			}
			if (!found)
			{
				l = 0;
				while (buff[l])
				{
					line[len] = buff[l];/* copy words to line */
					l++;
					len++;
				}
				line[len] = '\0';
			}
		}
	}
	return (line);
}
