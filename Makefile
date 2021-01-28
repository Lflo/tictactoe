# Makefile Variables
CC		 = gcc
EXEC	 = tictactoe
CFLAGS   = -Wall -ansi -pedantic -std=c89 -g
OBJ 	 = main.o tictactoe.o fileIO.o linked_list.o userInterface.o

# Add SECRET to the CFLAGS & recompile
ifdef SECRET
CFLAGS += -D SECRET
SECRET : clean $(EXEC)
endif

# Add EDITOR to the CFLAGS $ recompile
ifdef EDITOR
CFLAGS += -D EDITOR
EDITOR : clean $(EXEC)
endif

$(EXEC) : $(OBJ)
	$(CC) $(OBJ) -o $(EXEC)

main.o : main.c fileIO.h tictactoe.h linked_list.h userInterface.h
	$(CC) $(CFLAGS) main.c -c

userInterface.o : userInterface.c userInterface.h tictactoe.h fileIO.h
	$(CC) $(CFLAGS) userInterface.c -c

tictactoe.o : tictactoe.c tictactoe.h fileIO.h linked_list.h userInterface.h
	$(CC) $(CFLAGS) tictactoe.c -c 

fileIO.o : fileIO.c fileIO.h tictactoe.h linked_list.h userInterface.h
	$(CC) $(CFLAGS) fileIO.c -c 

linked_list.o : linked_list.c linked_list.h
	$(CC) $(CFLAGS) linked_list.c -c 

clean :
	rm -f $(EXEC) $(OBJ)

runVal :
	valgrind --leak-check=full ./$(EXEC)