#include "exit.h"

void my_exit(char *str)
{
  if (str != NULL)
    exit(my_atoi(str));
  else
    exit(0);
}