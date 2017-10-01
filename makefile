# A Makefile to build our 'calcmarks' project

PROJECT = lattice 
HEADERS = $(PROJECT).h
OBJ     = stack.o depthFirstSearch.o lattice.o depthFirstSearch2.o


C99     =  gcc -std=c99
CFLAGS  =  -Wall -pedantic -g 


$(PROJECT) : $(OBJ)
	$(C99) $(CFLAGS) -o $(PROJECT) $(OBJ) -lm

%.o : %.c 
	$(C99) $(CFLAGS) -c $<

clean:
	        rm -f $(PROJECT) $(OBJ)

