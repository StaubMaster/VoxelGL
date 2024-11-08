
NAME = openGL.a

FLAGS = -Wall -Wextra -Werror
FLAGS += -lglfw

FILE_C = glad.c stringHelp.c programLoader.c windowLoader.c textureLoadSave.c view.c math3D.c
FILE_O = $(FILE_C:.c=.o)


all: $(FILE_O)
	ar -rcs $(NAME) $(FILE_O)

clean:
	rm -f $(FILE_O)

fclean:
	$(MAKE) clean
	rm -f $(NAME)

re:
	$(MAKE) fclean
	$(MAKE) all

%.o : %.c
	cc -c $^ -o $@

.PHONY: all clean fclean re
