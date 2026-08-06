/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdelmott <jdelmott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 10:27:17 by sdabbas           #+#    #+#             */
/*   Updated: 2026/08/06 18:26:04 by jdelmott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "Libft/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <termios.h>
# include <unistd.h>

extern int				g_flag;

typedef enum e_redir_mode
{
	DEFAULT = 0,
	OUT_OVERWRITE,
	OUT_APPEND,
	IN_HEREDOC,
	IN_FILE,
}						t_redir_mode;

typedef struct s_redirections
{
	int					infd;
	enum e_redir_mode	in_mode;
	int					outfd;
	enum e_redir_mode	out_mode;
}						t_redirections;

typedef struct s_expand
{
	int					free_value;
	char				*pre;
	char				*key;
	char				*post;
	char				*value;
	char				*tmp;
	char				*res;
}						t_expand;

typedef struct s_expand_quotes
{
	char				*new;
	int					i;
	int					len;
	char				quotes;
}						t_expand_quotes;

typedef enum e_token_type
{
	WORD,
	PIPE,
	S_QUOTE,
	D_QUOTE,
	APPEND,
	HEREDOC,
	REDIR_IN,
	REDIR_OUT
}						t_token_type;

typedef struct s_token
{
	t_token_type		type;
	char				*s;
	struct s_token		*next;
}						t_token;

typedef struct s_data
{
	char				**env;
	int					heredoc_fd[2];
	int					return_code;
	t_token				*tokens;
	int					one_built;
	int					pipe_nb;
	struct sigaction	sig_int;
	struct sigaction	sig_quit;
	struct sigaction	sig_child_int;
	int					pipe_done;
	struct sigaction	sig_child_quit;
	int					current_stdin;
	int					mode_builtin;
	char				current_dir[4096];
	pid_t				children[4096];
}						t_data;

/* * * * * * INITIALISATION * * * * * */
void					read_line(t_token **tokens, t_data *data);
void					init(t_data *data, char **env);
void					clean(char *str, t_data *data, int return_code);
t_data					*get_data(void);
void					clean_redirs(t_redirections *r);
void					change_current_stdin(t_data *data, int pipe_fd[2]);

/* * * * * * LEXER * * * * * */
void					free_tokens(t_token *tokens);
t_token					*new_token(t_token_type type, char *value);
void					add_token(t_token **tokens, t_token *new);
t_token					*lexer(char *line);
void					expand_all_tokens(t_token *token, t_data *data);
void					utils_expand(char *s, int i, int len, t_expand *ex);
void					define_ex_value(t_data *data, t_expand *ex);
void					quotes_utils(char *s, t_expand_quotes *ex, int mode);
char					*expand_str_quotes(char *s, t_data *data);
char					which_quotes(char *s, int *i);
void					rm_quotes_token(t_token *tokens);
char					*remove_quotes(char *s);
int						check_syntax(t_data *data);
int						is_redirs(int type);

/* * * * * * BUILTINS * * * * * */
int						parsing_unset(t_data *data, t_token **tokens);
int						parsing_env(t_data *data, t_token **tokens);
int						get_pwd(t_data *data);
int						parsing_pwd(t_data *data, t_token **tokens);
int						export(t_data *data, char *arg);
int						parsing_export(t_data *data, t_token **tokens);
int						print_export(t_data *data, int option);
int						verif_args_export(char *arg);
int						is_dash(char *arg);
int						parsing_exit(t_data *data, t_token **tokens);
int						parsing_echo(t_token **tokens);
int						parsing_cd(t_data *data, t_token **tokens);

/* * * * * * * PARSING * * * * * */
int						exec_pipe(t_data *data);
int						parsing_cmd(t_data *data, t_token *tokens,
							int return_code);
int						create_redirs(t_token *tokens, t_redirections *r);
int						heredoc_redir(char *eof, t_data *data);
int						apply_redir(t_redirections *r);
void					wait_all(t_data *data);
int						parsing_heredoc(t_redirections *r, char *eof);

/* * * * * * EXECUTION * * * * * */
int						exec(t_data *data, t_token **tokens, t_redirections *r);
char					*get_env_value(char *key, char **env);
char					*find_path(char *cmd, char **env);
char					*access_path(char *cmd);
char					*path_helper(char *dir, char *cmd);
void					init_sign(struct sigaction *sig_int,
							struct sigaction *sig_quit);
void					init_sign_heredoc(struct sigaction *sig_child_int,
							struct sigaction *sig_child_quit);

#endif
