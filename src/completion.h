#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <readline/readline.h>
#include <readline/history.h>

int initialize_readline();
char *command_generator(const char *, int);
char **fileman_completion(const char *, int, int);
char *dupstr(char *s);
char *command_generator (const char *com, int num);