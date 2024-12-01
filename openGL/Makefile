
NAME = openGL.a

FLAGS = -Wall -Wextra -Werror

FILES_CPP = stringHelp.cpp \
	Shader.cpp \
	View.cpp \
\
	Forms/Window.cpp \
	Forms/KeyCheck.cpp \
	Forms/ItemVoxel.cpp \
\
	Forms/Help.cpp \
	Forms/Controls/Control.cpp \
	Forms/Controls/Button.cpp \
	Forms/Controls/Slot.cpp \
	Forms/Controls/Toggle.cpp \
	Forms/Controls/Form.cpp \
\
	Forms/Inventory.cpp \
	Forms/HotBar.cpp \
	Forms/Debug.cpp \
\
	Abstract/math3D.cpp \
	Abstract/Point.cpp \
	Abstract/Angle.cpp \
	Abstract/Index3D.cpp \
	Abstract/Undex3D.cpp \
\
	textureLoadSave.cpp
FILES_O = glad.o $(FILES_CPP:.cpp=.o)


all: $(FILES_O)
	ar -rcs $(NAME) $(FILES_O)

clean:
	rm -f $(FILES_O)

fclean:
	$(MAKE) clean
	rm -f $(NAME)

re:
	$(MAKE) fclean
	$(MAKE) all

%.o : %.cpp
	c++ $(FLAGS) -c $^ -o $@

.PHONY: all clean fclean re
