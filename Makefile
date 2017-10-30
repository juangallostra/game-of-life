# coder: #define true rand()&1

# Define some constants
CC = gcc
LIBS = -lncurses
DEPS = draw.h evolve.h
OBJ = main.o draw.o evolve.o

# build object files 
%.o: %.c $(DEPS)
	$(CC) -c -o $@ $<

# compile the actual executable
game_of_life: $(OBJ)
	$(CC) -o $@ $^ $(LIBS)
# remove executable and object files
clean:
	rm -f $(OBJ) game_of_life
