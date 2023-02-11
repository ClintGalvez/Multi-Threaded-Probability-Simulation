OPT = -Wall
OBJ = main.o deque.o pirates.o scenarios.o statistics.o

final:			$(OBJ)
				gcc $(OPT) -o final $(OBJ) -lpthread

main.o:			defs.h main.c deque.c pirates.c scenarios.c statistics.c
				gcc $(OPT) -c main.c

deque.o:		defs.h deque.c
				gcc $(OPT) -c deque.c

pirates.o:		defs.h pirates.c
				gcc $(OPT) -c pirates.c

scenarios.o:	defs.h scenarios.c
				gcc $(OPT) -c scenarios.c

statistics.o:	defs.h statistics.c
				gcc $(OPT) -c statistics.c

clean:
				rm -f $(OBJ) final