
FLAGS = -Wall -Wextra -Werror

NAME = test

FILE_C = inst_main.cpp VoxelChunk.cpp VoxelSpace.cpp Box.cpp MemorySize.cpp
FILE_O = $(FILE_C:.cpp=.o)

ARC_PATH = ./openGL
ARC = $(ARC_PATH)/openGL.a


$(NAME) : $(FILE_O) $(ARC)
	c++ $(FLAGS) $(FILE_O) $(ARC) -o $(NAME) E:/Programmieren/code/glfw-3.4.bin.WIN64/lib-mingw-w64/libglfw3.a -lgdi32
#	c++ $(FLAGS) $(FILE_O) $(ARC) -o $(NAME) -lglfw

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
