
CC = gcc

SRC = exo1.c exo2.c exo3.c exo4.c exo5.c exo6.c exo7.c exo8.c exo9.c fonctions_utils.c  
EXEC = projet.a

OBJ = $(SRC:.c=.o)

all : $(EXEC)
%.o : %.c
	$(CC) -o $@ -c $<

$(EXEC) : $(OBJ)
	ar rc -o $(EXEC) $^

clean : 
	rm -f $(OBJ)

fclean : clean
	 rm -f $(EXEC)
	
re : fclean all 
