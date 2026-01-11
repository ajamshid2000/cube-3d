NAME = cub3D
BONUS = cub3D_bonus
CFLAGS = -Wall -Wextra -Werror -g3
MLXFLAGS = -L ./minilibx-linux -lmlx -lXext -lX11 -O3
INCLUDES = -I ./minilibx-linux -I ./libftprintf -I ./libft
LIB = ./libftprintf/libftprintf.a ./libft/libft.a
SRCS = ./srcs/main.c ./srcs/movements.c ./srcs/initialization.c ./srcs/parsing_cub_file.c ./srcs/ray_casting_one.c ./srcs/ray_casting_two.c ./srcs/parsing_colors.c ./srcs/map_parsing_and_checking.c ./srcs/ft_and_clean.c ./gnl/get_next_line.c ./gnl/get_next_line_utils.c
BSRCS = ./srcs_bonus/main.c ./srcs_bonus/initialization.c ./srcs_bonus/movement.c ./srcs_bonus/keys_and_mouse.c ./srcs_bonus/raycasting_one.c ./srcs_bonus/raycasting_two.c ./srcs_bonus/parsing_cub_file.c ./srcs_bonus/parsing_colors.c ./srcs_bonus/map_parsing_and_checking.c ./srcs_bonus/ft_and_clean.c ./gnl/get_next_line.c ./gnl/get_next_line_utils.c
OBJS = $(SRCS:.c=.o)
BOBJS = $(BSRCS:.c=.o)

all: minilibx-linux $(NAME)
bonus: minilibx-linux $(BONUS)

minilibx-linux:
	git clone https://github.com/42paris/minilibx-linux.git
	@make -s -C ./minilibx-linux

$(NAME): $(OBJS)
	@make -s -C ./minilibx-linux
	@make -s -C ./libftprintf
	@make -s -C ./libft
	cc $(CFLAGS) $(OBJS) $(LIB) $(MLXFLAGS) -lm -o $(NAME)

$(BONUS): $(BOBJS)
	@make -s -C ./minilibx-linux
	@make -s -C ./libftprintf
	@make -s -C ./libft
	cc $(CFLAGS) $(BOBJS) $(LIB) $(MLXFLAGS) -lm -o $(BONUS)

%.o: %.c
	cc $(CFLAGS) $(INCLUDES) -c $< -o $@ 

clean:
	rm -f $(OBJS)
	rm -f $(BOBJS)
	@make -s -C ./minilibx-linux clean
	@make -s -C ./libftprintf clean
	@make -s -C ./libft clean

fclean: clean
	rm -f $(NAME)
	rm -f $(BONUS)
	@make -s -C ./libftprintf fclean
	@make -s -C ./libft fclean

re: fclean all

.PHONY: all bonus clean fclean re
