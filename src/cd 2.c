#include "cd.h"

int cd(char *path){
    char *tmp = NULL;
    int retour = 0;
    
    if ((path==NULL || strcmp("~",path)==0) 
    	&& (tmp=getenv("HOME"))!=NULL)
        path=strdup(tmp);
    retour = chdir(path);
    if (retour!=0)
    {
    	printf("\nErreur dans le changement de repertoire : %s\n",strerror(errno));
    }
    else
    {	
    	char* oldpwd=getenv("PWD");
    	char cwd[1024];
    	getcwd(cwd,sizeof(cwd));
    	setenv("PWD",cwd,1);
    	setenv("OLDPWD",oldpwd,1);
    }
    if (tmp!=NULL)
        free(path);
    return 0;
}