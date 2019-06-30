CC=gcc 

CFLAGS= -Wall

LDLIBS = -lreadline

SRC = src/mpsh.c src/completion.c src/cd.c \
		src/alias.c src/traitement.c src/history.c \
		src/export.c src/redirection.c src/echo.c \
		src/help.c

OBJ = $(SRC:.c=.o)

EXEC = mpsh

all: $(EXEC)

mpsh : $(OBJ) src/mpsh.o
	$(CC) $(CFLAGS) -o $@ $^ $(LDLIBS)

.c.o:
	$(CC) $(FLAGS) -c $< -o $@

clean:
	find . -name '*.o' -delete

mrproper: clean
	-rm -rf $(EXEC)