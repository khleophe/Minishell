/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdabbas <sdabbas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 10:27:17 by sdabbas           #+#    #+#             */
/*   Updated: 2026/07/13 14:09:26 by sdabbas          ###   ########.fr       */
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
# include <unistd.h>

extern int			flag;

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
}					t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*s;
	struct s_token	*next;
}					t_token;

typedef struct s_data // cree une fonction free all / exit
{
	char **env; // free dans tt les cas
	int return_code;
	t_token *tokens; //  free dans tt les cas
	int pipe_nb;
	struct sigaction sig_int;
	struct sigaction sig_quit;
	struct sigaction sig_child_int;
	struct sigaction sig_child_quit;
	int old_stdin;  // close dans tt les cas
	int old_stdout; // close dans tt les cas
	char current_dir[4096];
}					t_data;

/* * * * * * INITIALISATION * * * * * */
void				read_line(t_token **tokens, t_data *data);

/* * * * * * LEXER * * * * * */
void				free_tokens(t_token *list);
t_token				*new_token(t_token_type type, char *value);
void				add_token(t_token **tokens, t_token *new);
t_token				*lexer(char *line);
int					verif_line(char *str);
void				expand_all_tokens(t_token *token, t_data *data);
char				*expand_str(char *s, t_data *data);
void				rm_quotes_token(t_token *tokens);
int					check_syntax(t_data *data);
int					is_redirs(int type);

/* * * * * * BUILTINS * * * * * */
int					parsing_unset(t_data *data, t_token **tokens);
int					parsing_env(t_data *data, t_token **tokens);
int					get_pwd(t_data *data);
int					parsing_pwd(t_data *data, t_token **tokens);
int 				export(t_data *data, char *arg);
int					parsing_export(t_data *data, t_token **tokens);
int					print_export(t_data *data, int option);
int					verif_args_export(char *arg);
int 				is_dash(char *arg);\
int					parsing_exit(t_token **tokens);
int					parsing_echo(t_token **tokens);
int					parsing_cd(t_data *data, t_token **tokens);

/* * * * * * * PARSING * * * * * */
int					exec_pipe(t_data *data);
int					parsing_cmd(t_data *data, t_token *tokens);
int					apply_redirs(t_token *tokens, int *return_code,
						t_data *data);
int					heredoc_redir(char *eof, t_data *data);

/* * * * * * EXECUTION * * * * * */
int					exec(t_data *data, t_token *tokens);
char				*get_env_value(char *key, char **env);
char				*find_path(char *cmd, char **env);
char				*access_path(char *cmd);
char				*path_helper(char *dir, char *cmd);
void				init_sign(struct sigaction *sig_int,
						struct sigaction *sig_quit);
void				init_sign_heredoc(struct sigaction *sig_child_int,
						struct sigaction *sig_child_quit);

/*cd.c*/
int					cd_helper(t_data *data);
int					cd_null(t_data *data);
void				update_pwd(char *old_pwd, t_data *data);
int					many_args_mess(void);
// int						cd_builtin(t_cmd *cmd, t_data *data);
void				message_cd(char *path);

/*env_shell.c*/
char				**dup_env(char **env);
/*free*/
void				ft_free_tab(t_data *data);

#endif
