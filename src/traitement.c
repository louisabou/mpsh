#include "traitement.h"

char* nom="abc";

void executeSimpleCommande(char** arg_list)
{
  pid_t process=fork();
  if (process==-1)
  {
    printf("echec\n");
    return;
  }
  else if(process==0)
  {
    if(execvp(arg_list[0],arg_list)<0)
      printf("impossible\n");
    exit(0);
  }
  else
  {
    wait(NULL);
    return;
  }
}

void executeCommandeAvecPipe(char** arg_list, char** arg_pipe)
{
  int pipefd[2];
  pid_t process1, process2;
  if (pipe(pipefd)<0)
  {
    printf("impossible d'initialiser le pipe\n");
    return;
  }
  process1=fork();
  if (process1<0)
  {
    printf("Erreur dans la creation du fork de la commande 1\n");
    return;
  }
  if (process1==0)
  {
    close(pipefd[0]);
    dup2(pipefd[1],STDOUT_FILENO);
//    close(pipefd[1]);
    if (execvp(arg_list[0],arg_list)<0)
    {
      printf("impossible d'executer la commande 1\n");
      exit(0);
    }
  }

  else
  {
    process2=fork();
    if (process2<0)
    {
      printf("Erreur dans la creation du fork de la commande 2\n");
      return;
    }
    if (process2==0)
    {
      close(pipefd[1]); // verifier
      dup2(pipefd[0],STDIN_FILENO);
      close(pipefd[0]); // a verifier
      if (execvp(arg_pipe[0],arg_pipe)<0)
      {
        printf("Impossible d'executer la commande 2\n");
        exit(0);
      }
    }
    else {
      wait(NULL);
      wait(NULL);
//      return;
    }
  }
}

void executeRedirectionSortante(char** arg_list, char* name)
{
  
  int pipefd[2];
  pid_t process;
  if (pipe(pipefd)<0)
  {
    printf("impossible d'initialiser le pipe\n");
    return;
  }
  process=fork();
  if (process<0)
  {
    printf("Erreur dans la creation du fork de la commande\n");
    return;
  }
  if (process==0)
  {
    
    freopen(name,"w",stdout);

    if (execvp(arg_list[0],arg_list)<0)
      printf("echec redirection\n");
    fclose(stdout);
  }
  else
    wait (&process);
}

void executeRedirectionEntrante(char** arg_list, char* name)
{
  
  int pipefd[2];
  pid_t process1;
  if (pipe(pipefd)<0)
  {
    printf("impossible d'initialiser le pipe\n");
    return;
  }
  process1=fork();
  if (process1<0)
  {
    printf("Erreur dans la creation du fork de la commande\n");
    return;
  }
  if (process1==0)
  {
    /*
    dup2(pipefd[0],STDIN_FILENO);
    int handler=(int)freopen(name,"r",fdopen(0,"r"));
    if (handler==-1)
    {
      fprintf(stderr, "%s\n", strerror(errno));
      exit(0);
    }*/
  
    freopen(name,"r",stdin);
    if (execvp(arg_list[0],arg_list)<0)
      printf("echec redirection\n");
    fclose(stdin);
  }
  else
  {
    wait(NULL);  
  }
}

void executeRedirectionErreur(char** arg_list, char* name)
{
/*  int pipefd[3];
  pid_t process1;
  if (pipe(pipefd)<0)
  {
    printf("impossible d'initialiser le pipe\n");
    return;
  }
  process1=fork();
  if (process1<0)
  {
    printf("Erreur dans la creation du fork de la commande\n");
    return;
  }
  if (process1==0)
  {
    close(pipefd[0]);
    dup2(pipefd[2],STDERR_FILENO);
    int handler=(int)freopen(name,"w+",fdopen(2,"w"));
    if (handler==-1)
    {
      fprintf(stderr, "%s\n", strerror(errno));
      exit(0);
    }
    if (execvp(arg_list[0],arg_list)<0)
      printf("echec redirection\n");
  }
  else
  {
    wait(NULL);  
  }*/
}

int executeCommandeInterne(char** arg_list)
{
  
  int nbCmd=10, i=0, switchArg=0;
  char* ListArg[nbCmd];
  ListArg[0]="exit";
  ListArg[1]="cd";
  ListArg[2]="export";
  ListArg[3]="history";
  ListArg[4]="echo";
  ListArg[5]="alias";
  ListArg[6]="unexport";
  ListArg[7]="umask";
  ListArg[8]="?";
  ListArg[9]="help";
  for (;i<nbCmd;i++)
  {
    if(strcmp(arg_list[0],ListArg[i])==0)
    {
      switchArg=i+1;
      break;
    }
  }
  if (switchArg==1){
    exit(0);
  }
  else if (switchArg==2){
    cd(arg_list[1]);
    return 1;
  }
  else if (switchArg==3){
    ajouteVariable(arg_list[1]);
  }
  else if (switchArg==4){
    if (arg_list[1]==NULL)
      readHistory();
    else
    {
      int n = atoi(arg_list[1]);
      if (n<0)
        nombreDeCommandes(abs(n));
    }
    return 1;
  }
  else if (switchArg==5){
    if (arg_list[1]==NULL)
      printf("\n");
    else
      my_echo(arg_list[1]);
    return 1;
  }
  else if (switchArg==6){
    alias(arg_list[1]);
    return 1;
  }
  else if (switchArg==7){
    retireVariable(arg_list[1]);
    return 1;
  }
  else if (switchArg==8)
  {
    return 1;
  }
  else if (switchArg==9)
  {
    return 1;
  }
  else if (switchArg==10)
  {
    my_help();
  }
  else
    return 0;
  return 1;
}

void separeEspace(char* line, char** arg_list)
{
  int i;
  int taille=strlen(line);
  for (i=0;i<100;i++)
  {
    arg_list[i]=strsep(&line," ");
    if (arg_list[i]==NULL)
      break;
    if (strlen(arg_list[i])==0)
      i--;
  }
}

void separeEspaceBis(char* line, char* name)
{
  int i;
  int taille=strlen(line);
  for (i=0;i<100;i++)
  {
    name=strsep(&line," ");
    if (name==NULL)
      break;
    if (strlen(name)==0)
      i--;
  }
}

int process(char* line, char** arg_list, char** arg)
{
  char *strout[2], *strin[2], *strerr[2], *strpipe[2];
  int pipe=0, in=0, out=0, err=0,flag=0;
  pipe=parsePipe(line,strpipe);
  in=parseRedirectionEntrante(line,strin);
  out=parseRedirectionSortante(line,strout);
  err=parseRedirectionErreur(line,strerr);
  if (pipe)
  {
    separeEspace(strpipe[0],arg_list);
    separeEspace(strpipe[1],arg);
    flag=1;
  }
  if (in)
  {
    separeEspace(strin[0],arg_list);
    separeEspace(strin[1],arg);
    flag=2;
  }
//  
  if (out)
  {
    separeEspace(strout[0],arg_list);
    separeEspace(strout[1],arg);
    flag=3;
  }
//  
/*  if (err)
  {
    separeEspace(strerr[0],arg_list);
    separeEspace(strerr[1],arg);
    flag=4;
  }*/
  else
  {
    separeEspace(line,arg_list);
    if (executeCommandeInterne(arg_list))
      flag=0;
    else
      flag=5;
  }
  return flag;
}



int traitement_ligne_de_commande(char *line)
{
  printf("commande à exécuter: %s\n", line);
  using_history();
  int taille=strlen(line);
  int flag=0;
  if (taille!=0)
  {
    add_history(line);
    char* arg_list[100], *arg[100], *name=NULL;
    flag=process(line,arg_list,arg);
    /* 0 si c est une commande interne
      1 si c est un pipe
      2 si c est une redirection entrante
      3 si c est une redirection sortante
      4 si c est une redirection d erreur
      5 si c est une simple commande
    */
    int incr=0;
    if (flag==0)
      executeCommandeInterne(arg_list);

    if (flag==1)
      executeCommandeAvecPipe(arg_list,arg);
    if (flag==2)
      executeRedirectionEntrante(arg_list,arg[0]);
    if (flag==3){
      executeRedirectionSortante(arg_list,arg[0]);
    }
    if (flag==4)
      executeRedirectionErreur(arg_list,arg[0]);
    if (flag==5)
      executeSimpleCommande(arg_list);
  }

  return 0;
  
}