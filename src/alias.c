#include "alias.h"

int alias(char *path){

  FILE *fichier=NULL;
  if (path != NULL)
  {
    fichier=fopen(".mpsh_alias","a+");
    if (fichier!=NULL)
    {
      fprintf(fichier,"%s\n",path);
    }
    else
      printf("Erreur dans l'ouverture du fichier\n");
  }
  else
  {
    char chaine[1000]="";
    fichier=fopen(".mpsh_alias","r");
    if(fichier!=NULL)
    {
      fgets(chaine,1000,fichier);
      printf("%s\n",chaine);
    }
  }
  fclose(fichier);
  return 0;
}

int unalias(char *name)
{
  char chaine[1000]="";
  int retour=0;
  FILE *fic=fopen(".mpsh_alias","r+");
//  FILE newFic=fopen(".tmp","a");
  if (fic!=NULL){
    fgets(chaine,1000,fic);
    if (strncmp(name,chaine,strlen(name))==0)
      printf("on affiche %s\n",chaine );  
    else
      printf("pastrouve\n");
    fclose(fic);
  }
  return retour;
}

int supprimeFichierAlias(){
  remove(".mpsh_alias");
  return 0;
}