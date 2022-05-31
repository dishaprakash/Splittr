// To check the command given by user
#include"header_file.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int check_syn(char *command)
{
	int i;
	char check[10]="delgroup";
	for(i=0;i<8;i++)
	{
		if(command[i] != check[i])
			return(-1);
	}
	if(command[i] != '\0')
		return(-1);
	return(1);
}