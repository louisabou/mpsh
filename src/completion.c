#include "completion.h"

char *dupstr(char *s){
  char *r = malloc(strlen(s)+1);
  strcpy (r, s);
  return r;
}

int initialize_readline(){
  rl_readline_name = "mpsh";
  /* explicite la complétion souhaitée */
  rl_attempted_completion_function = fileman_completion;

  return 0;
}

/* com : tout ce que l'utilisateur a déjà écrit sur la ligne de commande
   start, end : les indices de début et de fin du mot sur lequel TAB a été lancé */
char ** fileman_completion (const char *com, int start, int end){
  char **matches;

  matches = (char **)NULL; /* assure la complétion par défaut */

  /* si c'est le premier mot de la ligne de commande, on l'analyse;
     sinon on utilise l'analyse par défaut */
  if (start == 0)
    matches = rl_completion_matches (com, command_generator);

  return (matches);
}

/* liste des complétions possibles pour les mots commencant par t 
   et en début de ligne */
char *completions[] = {"cd", "exit","export","help",
"history","echo","alias","unexport","umask" };
int nb_completions = 9;

/* fonction qui engendre les complétions possibles :
   à chaque num >= 0 correspond une complétion;
   la fin de la liste des complétions est donnée par NULL
   
   ici on complète si c'est un préfixe de "toto" ou de "turlututu",
   sinon c'est la complétion par défaut */
char *command_generator (const char *com, int num){
  /* à l'entrée de cette fonction : com est le début déjà écrit de la commande,
   on est en train de chercher la complétion numéro num */
  static int indice, len;
  char *completion;

  /* si c'est la première complétion qu'on cherche, on dit qu'on va chercher à partir
     de la premiere case du tableau completion et on garde en mémoire la longueur
     du texte tapé */
  if (num == 0){
      indice = 0;
      len = strlen(com);
    }

  /* on renvoie une complétion de préfixe le début de la commande écrite */
  while (indice < nb_completions)
    {
      completion = completions[indice++];

      if (strncmp (completion, com, len) == 0)
        return dupstr(completion);
    }
  
  /* est renvoyé quand num est > au numéro de la dernière complétion
     automatique */
  return NULL;
}