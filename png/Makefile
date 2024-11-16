
#NAME = decompressor
NAME = png.a

FILE_C = png.c mem.c read.c bits.c chunk.c HuffCodeTree.c block.c filter.c sixel.c
FILE_O = $(FILE_C:.c=.o)

Flags = -Wall -Wextra -Werror

all:
	$(MAKE) $(FILE_O)
	ar -rcs $(NAME) $(FILE_O)
#	cc -o test main.c $(NAME)

%.o: %.c
	c++ $(Flags) -c $^ -o $@

clean:
	rm -f $(FILE_O)

fclean:
	rm -f $(FILE_O)
	rm -f $(NAME)

re:	fclean all

.Phony: all clean fclean re
