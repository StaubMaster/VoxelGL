
#NAME = decompressor
NAME = png.a

FILE_C = _png.c _mem.c _read.c _bits.c _chunk.c _HuffCodeTree.c _block.c _filter.c _sixel.c
FILE_CPP = load.cpp \
	uint.cpp \
	BitStream.cpp \
	Chunk.cpp \
	ZLIB.cpp \
	Huffman.cpp
FILE_O = $(FILE_C:.c=.o)
FILE_O += $(FILE_CPP:.cpp=.o)

Flags = -Wall -Wextra -Werror

all:
	$(MAKE) $(FILE_O)
	ar -rcs $(NAME) $(FILE_O)
#	cc -o test main.c $(NAME)

%.o: %.cpp
	c++ $(Flags) -c $^ -o $@
%.o: %.c
	c++ $(Flags) -c $^ -o $@

clean:
	rm -f $(FILE_O)

fclean:
	rm -f $(FILE_O)
	rm -f $(NAME)

re:	fclean all

.Phony: all clean fclean re
