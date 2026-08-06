NAME = minishell

CC = clang
CFLAGS = -Wall -Wextra -Werror -g3 --std=gnu89

SRCS = lexer/init_tokens.c main.c builtins/unset.c read_line.c lexer/tokens.c lexer/utils_tokens.c \
		parsing/pipe.c parsing/redirs.c lexer/expand.c clean.c lexer/expand_utils.c\
		builtins/echo.c builtins/env.c builtins/cd.c exec/exec_utils.c\
		builtins/exit.c builtins/export.c builtins/utils_export.c\
		builtins/pwd.c exec/free.c exec/signals.c parsing/heredoc.c parsing/parsing_builtin.c\
		exec/path.c lexer/quotes.c lexer/syntax.c init.c exec/exec.c parsing/parsing.c parsing/apply_redir.c
		

OBJS = $(SRCS:.c=.o)

LIBFT_DIR = Libft
LIBFT = $(LIBFT_DIR)/libft.a

INCLUDES = -I. -I$(LIBFT_DIR)

all: $(NAME)

$(LIBFT):
	@make -C $(LIBFT_DIR)

%.o: %.c minishell.h
	$(CC) -I/opt/homebrew/opt/readline/include -D_DEFAULT_SOURCE -c -g3 $(CFLAGS) $(INCLUDES) -c $< -o $@

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) -L/opt/homebrew/opt/readline/lib $(OBJS) $(LIBFT) -D_DEFAULT_SOURCE -Iinclude -lreadline -g3 -o $(NAME)

jo: re
	make clean
	@echo
	@echo
	@echo JOJO IS IN THE HOUSE

so: jo
	@echo AND SOSO IS HOOOOT

clean:
	rm -f $(OBJS)
	@make -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	@make -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
