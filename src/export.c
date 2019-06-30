#include "export.h"

int ajouteVariable(char *line)
{
	char *var, *word, *p;
	p=strdup(line);
    var = strtok(p,"=");
    word = strtok(NULL, "=");
	setenv(var,word,1);
	return 0;
}

int retireVariable(char *var)
{
	unsetenv(var);
	return 0;
}