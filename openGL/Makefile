
NAME = openGL.a

FLAGS = -Wall -Wextra -Werror

FILE_C = stringHelp.cpp Shader.cpp \
	Forms/Window.cpp \
	Forms/KeyCheck.cpp \
	Forms/FormControl.cpp \
	textureLoadSave.cpp \
	Abstract/math3D.cpp \
	Abstract/Point.cpp \
	Abstract/Angle.cpp \
	Abstract/Index3D.cpp \
	Abstract/Undex3D.cpp \
	View.cpp
FILE_O = glad.o $(FILE_C:.cpp=.o)


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

%.o : %.cpp
	c++ $(FLAGS) -c $^ -o $@

.PHONY: all clean fclean re
