
NAME = fileParser.a

FILES_CPP = \
	DebugManager.cpp \
	uint.cpp \
	BitStream.cpp \
	DataStream.cpp

FILES_PNG_CPP = \
	PNG/Chunk.cpp \
	PNG/ZLIB.cpp \
	PNG/Huffman.cpp \
	PNG/DEFLATE.cpp \
	PNG/PNG_Filter.cpp \
	PNG/PNG_Image.cpp

FILES_O = $(FILES_CPP:.cpp=.o)
FILES_O += $(FILES_PNG_CPP:.cpp=.o)

Flags = -Wall -Wextra -Werror

all:
	$(MAKE) $(FILES_O)
	ar -rcs $(NAME) $(FILES_O)

%.o: %.cpp
	c++ $(Flags) -c $^ -o $@

clean:
	rm -f $(FILES_O)

fclean:
	rm -f $(FILES_O)
	rm -f $(NAME)

re:	fclean all

.Phony: all clean fclean re
