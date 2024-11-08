
FLAGS = -Wall -Wextra -Werror

NAME = test

FILE_C = main.c
FILE_O = $(FILE_C:.c=.o)

ARC_PATH = ./openGL
ARC = $(ARC_PATH)/openGL.a


$(NAME) : $(FILE_O) $(ARC)
	cc $(FLAGS) -lglfw $(FILE_O) $(ARC) -o $(NAME)

all:
	$(MAKE) $(FILE_O)
	$(MAKE) $(NAME)

clean:
	rm -f $(FILE_O)
	$(MAKE) -C $(ARC_PATH) fclean

fclean:
	$(MAKE) clean
	rm -f $(NAME)

re:
	$(MAKE) fclean
	$(MAKE) all

.PHONY: all clean fclean re


%.o : %.c
	cc $(FLAGS) -c $^ -o $@


$(ARC) :
	$(MAKE) -C $(ARC_PATH) all
