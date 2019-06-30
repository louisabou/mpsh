#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

/*


char* redirection_entrante(char* str);
char* redirection_sortante(char* str);
char* scan(char* str,char symbole);
char *scan_redirection_sortante(char *arguments[32]);
*/

int parseRedirectionErreur(char* line, char** str);
int parseRedirectionEntrante(char* line, char** str);
int parseRedirectionSortante(char* line, char** strred);
int parsePipe(char* line, char** str);