
NAME = a.exe

FILES_CPP = \
	main.cpp \
	AxisBox.cpp \
	EntityBox.cpp \
	MemorySize.cpp

FILES_VOXEL_CPP = \
	Voxel/Voxel.cpp \
	Voxel/VoxelRenderData.cpp \
	Voxel/VoxelChunk.cpp \
	Voxel/VoxelSpace.cpp \
	Voxel/VoxelDataTable.cpp

FILES_O = $(FILES_CPP:.cpp=.o)
FILES_O += $(FILES_VOXEL_CPP:.cpp=.o)

FLAGS = -Wall -Wextra -Werror

ARC_OPENGL_PATH = ./openGL
ARC_OPENGL = $(ARC_OPENGL_PATH)/openGL.a

ARC_FILES_PATH = ./FileParse
ARC_FILES = $(ARC_FILES_PATH)/fileParser.a


$(NAME) : $(FILES_O) $(ARC_OPENGL) $(ARC_FILES)
	c++ $(FLAGS) -o $(NAME) $(FILES_O) $(ARC_OPENGL) $(ARC_FILES) E:/Programmieren/code/glfw-3.4.bin.WIN64/lib-mingw-w64/libglfw3.a -lgdi32
#	c++ $(FLAGS) -o $(NAME) $(FILES_O) $(ARC_OPENGL) $(ARC_FILES) -lglfw

all:
	$(MAKE) -C $(ARC_OPENGL_PATH) all
	$(MAKE) -C $(ARC_FILES_PATH) all
	$(MAKE) $(FILES_O)
	$(MAKE) $(NAME)

clean:
	rm -f $(FILES_O)
	$(MAKE) -C $(ARC_OPENGL_PATH) fclean
	$(MAKE) -C $(ARC_FILES_PATH) fclean

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

$(ARC_FILES) :
	$(MAKE) -C $(ARC_FILES_PATH) all

