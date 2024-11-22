
FLAGS = -Wall -Wextra -Werror

NAME = a.exe

FILE_C = main.cpp \
	Voxel.cpp \
	VoxelRenderData.cpp \
	VoxelChunk.cpp \
	VoxelSpace.cpp \
	Box.cpp \
	MemorySize.cpp
FILE_O = $(FILE_C:.cpp=.o)

ARC_OPENGL_PATH = ./openGL
ARC_OPENGL = $(ARC_OPENGL_PATH)/openGL.a

ARC_PNG_PATH = ./png
ARC_PNG = $(ARC_PNG_PATH)/png.a


$(NAME) : $(FILE_O) $(ARC_OPENGL) $(ARC_PNG)
	c++ $(FLAGS) -o $(NAME) $(FILE_O) $(ARC_OPENGL) $(ARC_PNG) E:/Programmieren/code/glfw-3.4.bin.WIN64/lib-mingw-w64/libglfw3.a -lgdi32
#	c++ $(FLAGS) -o $(NAME) $(FILE_O) $(ARC_OPENGL) $(ARC_PNG) -lglfw

all:
	$(MAKE) -C $(ARC_OPENGL_PATH) all
	$(MAKE) -C $(ARC_PNG_PATH) all
	$(MAKE) $(FILE_O)
	$(MAKE) $(NAME)

clean:
	rm -f $(FILE_O)
	$(MAKE) -C $(ARC_OPENGL_PATH) fclean
	$(MAKE) -C $(ARC_PNG_PATH) fclean

fclean:
	$(MAKE) clean
	rm -f $(NAME)

re:
	$(MAKE) fclean
	$(MAKE) all

.PHONY: all clean fclean re


%.o : %.cpp
	c++ $(FLAGS) -c $^ -o $@


$(ARC_OPENGL) :
	$(MAKE) -C $(ARC_OPENGL_PATH) all

$(ARC_PNG) :
	$(MAKE) -C $(ARC_PNG_PATH) all

