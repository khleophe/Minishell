NAME	= libft.a
CC		= gcc
CFLAGS	+= -Wall -Werror -Wextra

SOURCES	= ./ft_isalpha.c\
		./ft_isdigit.c\
		./ft_isalnum.c\
		./ft_isascii.c\
		./ft_isprint.c\
		./ft_strlen.c\
		./ft_memset.c\
		./ft_bzero.c\
		./ft_memcpy.c\
		./ft_memmove.c\
		./ft_strlcpy.c\
		./ft_strlcat.c\
		./ft_toupper.c\
		./ft_tolower.c\
		./ft_strchr.c\
		./ft_strrchr.c\
		./ft_strncmp.c\
		./ft_memchr.c\
		./ft_memcmp.c\
		./ft_strnstr.c\
		./ft_atoi.c\
		./ft_calloc.c\
		./ft_strdup.c\
		./ft_substr.c\
		./ft_strjoin.c\
		./ft_strtrim.c\
		./ft_split.c\
		./ft_itoa.c\
		./ft_putstr.c\
		./ft_strmapi.c\
		./ft_striteri.c\
		./ft_putchar_fd.c\
		./ft_putstr_fd.c\
		./ft_putendl_fd.c\
		./ft_putnbr_fd.c\
		./ft_lstiter.c\
		./ft_lstmap.c\
		./get_next_line.c\
		./utils_printf.c\
		./ft_putnbr_u.c\
		./ft_putnbr_hexa.c\
		./ft_printf.c\
		./ft_freetab.c\
		./ft_atol.c\
		./ft_strcmp.c

bonus = ./ft_lstnew.c\
        ./ft_lstadd_front.c\
        ./ft_lstsize.c\
        ./ft_lstlast.c\
        ./ft_lstadd_back.c\
		./ft_lstdelone.c\
		./ft_lstclear.c

OBJECTS	= $(SOURCES:.c=.o)
OBJECTSBONUS = $(bonus:.c=.o)

all: $(NAME) 

$(NAME): $(OBJECTS)
	@echo "Building library $(NAME)"
	ar rcs $(NAME) $(OBJECTS)

bonus: $(OBJECTS) $(OBJECTSBONUS)
	@echo "Buildinge library + bonus $(NAME)"
	ar rcs $(NAME) $(OBJECTS) $(OBJECTSBONUS)

%.o: %.c 
	@echo "Creating '$@' objects"
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@echo "Removing all objects"
	rm -f $(OBJECTS) $(OBJECTSBONUS)

fclean: clean 
	@echo "Removing library"
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
