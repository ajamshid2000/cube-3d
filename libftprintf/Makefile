NAME = libftprintf.a
SOURCE = ft_strcpy.c ft_printf.c ft_put_unsigned_decimal.c ft_putchar.c ft_puthexa.c ft_putnumber.c ft_putptr.c ft_putstr.c
OBJ = $(SOURCE:.c=.o)
FLAGS = -Wall -Wextra -Werror

all: $(NAME)


$(NAME): $(OBJ) ft_printf.h
	ar -rcs $(NAME) $(OBJ) ft_printf.h
	

%.o: %.c
	cc -o $@ -c $< $(FLAGS)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)
	
re: clean all
