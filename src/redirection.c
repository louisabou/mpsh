#include "redirection.h"

int parsePipe(char* line, char** str)
{
  int i;
  for (i=0;i<2;i++)
  {
    str[i]=strsep(&line,"|");
    if (str[i]==NULL)
      break;
  }
  if (str[1]==NULL)
    return 0;
  else
    return 1;
}

int parseRedirectionSortante(char* line, char** strred)
{
  int i;
  for(i=0;i<2;i++)
  {
    strred[i]=strsep(&line,">");
    if (strred[i]==NULL)
      break;
  }
  if (strred[1]==NULL)
    return 0;
  else
    return 1;
}

int parseRedirectionEntrante(char* line, char** str)
{
  int i;
  for(i=0;i<2;i++)
  {
    str[i]=strsep(&line,"<");
    if (str[i]==NULL)
      break;
  }
  if (str[1]==NULL)
    return 0;
  else
    return 1;
}


int parseRedirectionErreur(char* line, char** str)
{
  int i =0, k=0;
  while (line[i])
  {
    if (line[i]=='2' && line[i+1]=='>')
    {
      str[0]=strndup(line,i);
      k=i;
    }
    ++i;
  }

  if (str[0]==NULL)
      return 0;
  
  else{
    char *dest=malloc(strlen(line));
    dest[0]='\0';
    k=k+2;
    while(k<strlen(line)){
      strcat(dest,line+k);
      break;
    }
    str[1]=strdup(dest);
    free(dest);
    return 1;
  }
}


