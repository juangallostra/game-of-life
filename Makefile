# coder: #define true rand()&1
CC = gcc
LIBS = -lncurses
DEPS = draw.h evolve.h
OBJ = main.o draw.o evolve.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $<

game_of_life: $(OBJ)
	$(CC) -o $@ $^ $(LIBS)
