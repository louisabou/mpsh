#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "history.h"
#include "alias.h"
#include "cd.h"
#include "export.h"
#include "redirection.h"
#include "exit.h"
#include "help.h"
#include "echo.h"

int traitement_ligne_de_commande(char *line);