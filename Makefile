NAME = cube
CC = cc
RM = rm -f
HEADER = render_map.h
CFLAGS =   -lmlx -framework OpenGL -framework AppKit -w -w -w #-fsanitize=address -g 
SRC =  render_map.c init_data.c render_player.c move.c cast_rays.c  vertical.c  horizantal.c help.c
OBJ = $(SRC:%.c=%.o)
all : $(NAME)
$(NAME) : $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)
%.o : %.c $(HEADER)
	$(CC) $(CFLAGS)  -c $< -o $@
clean :
	$(RM) $(OBJ)
fclean : clean
	$(RM) $(NAME)
re : fclean all
.phony : all clean fclean $(NAME)