
FLAGS = -Wall -Wextra -Werror
FLAGS += -lglfw

NAME = test

FILE_C = glad.c programLoader.c windowLoader.c textureLoadSave.c view.c main.c
FILE_O = $(FILE_C:.c=.o)

$(NAME) : $(FILE_O)
	cc $(FILE_O) $(FLAGS) -o $(NAME)

all:
	$(MAKE) $(FILE_O)
	$(MAKE) $(NAME)

clean:
	rm -f $(FILE_O)

fclean:
	$(MAKE) clean
	rm -f $(NAME)

re:
	$(MAKE) fclean
	$(MAKE) all

.PHONY: all clean fclean re


%.o : %.c
	cc -c $^ -o $@
