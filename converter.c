#include "shell.h"
/*
*Author: Chillexy Steven     
*Program: WinMingle Community C Training
*Description: this a function that converts an integer to a string
*/
void str(long int n, char *s)
{
	long int i = 0, len;
	long int digit;
	char form;
	char c;
	while (n > 0) /* for every int we convert each to a char*/
	{
		digit = n % 10;
		form = '0' + digit; /* converts an int to a char */
		s[i] = form;
		n /= 10;
		i++;
	}
	s[i] = '\0';
	i = 0;
	len = _strlen(s) - 1;
	/* because evry int was converted to a char in a reversed format we get them back into its original form by printing them back from the reversed form again*/
	while(i < len)
	{
		c = s[i];
		s[i] = s[len];
		s[len] = c;
		i++;
		len--;
	}
}
