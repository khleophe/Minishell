NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror -g

SRCS = lexer/init_tokens.c main.c lexer/lexer.c lexer/tokens.c lexer/utils_tokens.c \
		parsing/pipe.c parsing/redirs.c lexer/expand.c \
		builtins/builtins.c builtins/cd.c builtins/echo.c builtins/env.c \
		builtins/exit.c builtins/export.c builtins/export_helper.c builtins/print_export.c \
		builtins/pwd.c builtins/unset.c exec/free.c exec/signals.c exec/heredoc_delete.c parsing/heredoc.c \
		exec/path.c lexer/quotes.c lexer/syntax.c env_shell.c exec/exec.c parsing/parsing.c
		

OBJS = $(SRCS:.c=.o)

LIBFT_DIR = Libft
LIBFT = $(LIBFT_DIR)/libft.a

INCLUDES = -I. -I$(LIBFT_DIR)

all: $(NAME)

$(LIBFT):
	@make -C $(LIBFT_DIR)

%.o: %.c minishell.h
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -Iinclude -lreadline -g3 -o $(NAME)

clean:
	rm -f $(OBJS)
	@make -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	@make -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
