NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror -g

SRCS = lexer/init_tokens.c lexer/main.c lexer/lexer.c lexer/tokens.c lexer/utils_tokens.c \
		exec/exec.c exec/pipe.c exec/redirs.c lexer/expand.c \
		exec/builtins/builtins.c exec/builtins/cd.c exec/builtins/echo.c exec/builtins/env.c \
		exec/builtins/exit.c exec/builtins/export.c exec/builtins/export_helper.c exec/builtins/print_export.c \
		exec/builtins/pwd.c exec/builtins/unset.c exec/free.c exec/signals.c exec/childs.c exec/heredoc.c \
		exec/path.c lexer/quotes.c lexer/syntax.c env_shell.c
		

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
