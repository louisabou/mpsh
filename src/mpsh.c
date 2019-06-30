#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "completion.h"
#include "traitement.h"

int main(){

  char *s;
  initialize_readline ();   /* pour fabriquer les complétions */
  printf("(Ctrl+C ou exit pour quitter...)\n\
  help pour voir la liste des options disponibles\n");
  while(1){
      s = readline ("mpsh$ ");
      traitement_ligne_de_commande(s);
      free(s);
    }
  exit(0);
}