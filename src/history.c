#include "history.h"

int readHistory(){
	register HIST_ENTRY **list;
    register int i;
    list = history_list ();
    if (list)
    for (i = 0; list[i]; i++)
    	printf ("%d: %s\n", i + history_base, list[i]->line);
	return 0;
}

int nombreDeCommandes(int n){
	stifle_history(n);
	return 0;
}
/*
int relanceCommande(int n){
	HIST_ENTRY *historique;
	char *cmd;
	historique=history_get(n);
	strcpy(cmd,historique->line);
	remove_history(history_length-1);
	add_history(cmd);
}*/