NAME = cube3D_bonus
CFLAGS = -Wall -Wextra -Werror -g3
MLXFLAGS = -L ./minilibx-linux -lmlx -lXext -lX11 -O3
INCLUDES = -I ./minilibx-linux -I ./libftprintf -I ./libft
LIB = ./libftprintf/libftprintf.a ./libft/libft.a
SRCS = main.c parsing_cub_file.c parsing_colors.c map_parsing_and_checking.c initialize_free_and_ft.c ./gnl/get_next_line.c ./gnl/get_next_line_utils.c
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	@make -s -C ./minilibx-linux
	@make -s -C ./libftprintf
	@make -s -C ./libft
	cc $(CFLAGS) $(OBJS) $(LIB) $(MLXFLAGS) -lm -o $(NAME)

%.o: %.c
	cc $(CFLAGS) $(INCLUDES) -c $< -o $@ 

clean:
	rm -f $(OBJS)
	@make -s -C ./minilibx-linux clean
	@make -s -C ./libftprintf clean
	@make -s -C ./libft clean

fclean: clean
	rm -f $(NAME)
	@make -s -C ./libftprintf fclean
	@make -s -C ./libft fclean

re: fclean all

.PHONY: all bonus clean fclean re
