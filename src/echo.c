#include "echo.h"

void my_echo(char *line)
{	
	if (line[0]=='$')
	{	
		extern char **environ;
		char *p=strdup(line);
		char *var=strtok(p,"$");
		for (int i=0;environ[i];i++)
		{
			if (strncmp(var,environ[i],strlen(var))==0)
				printf("%s\n",environ[i]);	
		}
	}
	
	else
		printf("%s\n", line);
	
}