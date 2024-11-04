NAME = libft.a

SOURCE = ft_putnbr_fd.c ft_putendl_fd.c ft_putstr_fd.c ft_putchar_fd.c ft_striteri.c ft_strmapi.c ft_itoa.c ft_split.c ft_strtrim.c ft_strjoin.c ft_substr.c ft_strdup.c ft_calloc.c ft_atoi.c ft_strlcat.c ft_strlcpy.c ft_strncmp.c ft_isdigit.c ft_isalpha.c ft_strlen.c ft_memmove.c ft_bzero.c ft_isalnum.c ft_isascii.c ft_isprint.c ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memset.c ft_strchr.c ft_strnstr.c ft_strrchr.c ft_tolower.c ft_toupper.c
BSOURCE = ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c
OBJ = $(SOURCE:.c=.o)
BOBJ = $(BSOURCE:.c=.o)
CFLAGS = -Wall -Wextra -Werror


all: $(NAME)

bonus: $(OBJ) $(BOBJ)
	ar -rcs $(NAME) $(OBJ) $(BOBJ)

	
$(NAME): $(OBJ)
	ar -rcs $(NAME) $(OBJ)
	

%.o: %.c
	cc -o $@ -c $< $(CFLAGS)

clean:
	rm -f $(OBJ) $(BOBJ)

fclean: clean
	rm -f $(NAME)

re: clean all

#ft_bzero.o: ft_bzero.c
#	gcc -o ft_bzero.o -c ft_bzero.c

#ft_isalnum.o: ft_isalnum.c
#	gcc -o ft_isalnum.o ft_isalnum.c

#ft_isascii.o: ft_isascii.c
#	gcc -o ft_isascii.o -c ft_isascii.c

#ft_isprint.o: ft_isprint.c
#	gcc -o ft_isprint.o -c ft_isprint.c

#ft_memchr.o: ft_memchr.c
#	gcc -o ft_memchr.o -c 
