
Name = decompressor

File_C = png.c mem.c read.c bits.c chunk.c HuffCodeTree.c block.c filter.c sixel.c
File_O = $(File_C:.c=.o)

#Flags = -Wall -Wextra -Werror

$(Name) : $(File_O)
	cc $(Flags) $(File_O) -o $(Name)

all:
	$(MAKE) $(File_O)
	$(MAKE) $(Name)

%.o: %.cpp
	cc $(Flags) -c $^ -o $@

clean:
	rm -f $(File_O)

fclean:
	rm -f $(File_O)
	rm -f $(Name)

re:	fclean all

.Phony: all clean fclean re
