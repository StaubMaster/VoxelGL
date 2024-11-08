
FLAGS = -Wall -Wextra -Werror

NAME = test

FILE_C = main.cpp
FILE_O = $(FILE_C:.cpp=.o)

ARC_PATH = ./openGL
ARC = $(ARC_PATH)/openGL.a


$(NAME) : $(FILE_O) $(ARC)
	c++ $(FLAGS) -lglfw $(FILE_O) $(ARC) -o $(NAME)

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


%.o : %.cpp
	c++ $(FLAGS) -c $^ -o $@


$(ARC) :
	$(MAKE) -C $(ARC_PATH) all
