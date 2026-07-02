/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdabbas <sdabbas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 10:27:17 by sdabbas           #+#    #+#             */
/*   Updated: 2026/06/29 17:02:49 by sdabbas          ###   ########.fr       */
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
	int					return_code;
	t_token				*tokens;
	int					pipe_nb;
	struct sigaction	sig_int;
	struct sigaction	sig_quit;
}						t_data;

/* * * * * * INITIALISATION * * * * * */
void					read_line(t_token **tokens, t_data *data);

/* * * * * * LEXER * * * * * */
void					free_tokens(t_token *list);
t_token					*new_token(t_token_type type, char *value);
void					add_token(t_token **tokens, t_token *new);
t_token					*lexer(char *line);
int						verif_line(char *str);
void					expand_all_tokens(t_token *token, t_data *data);
char					*expand_str(char *s, t_data *data);
void					rm_quotes_token(t_token *tokens);
int						check_syntax(t_data *data);
int						is_redirs(int type);

/* * * * * * * PARSING * * * * * */
int						exec_pipe(t_data *data);
int						parsing_cmd(t_data *data, t_token *tokens);
int						apply_redirs(t_token *tokens, int *return_code,
							t_data *data);
int						heredoc_redir(char *eof, t_data *data);

/* * * * * * EXECUTION * * * * * */
int						exec(t_data *data, t_token *tokens);
char					*get_env_value(char *key, char **env);
char					*find_path(char *cmd, char **env);
char					*access_path(char *cmd);
char					*path_helper(char *dir, char *cmd);
void					init_sign(struct sigaction *sig_int,
							struct sigaction *sig_quit);

/* * * * * * BUILTINS * * * * * */
int parsing_env(t_data *data, t_token **token);
//int						init_builtins(t_data *data, t_cmd *cmd);
//int						cmp_builtins(t_cmd *cmd);

/*cd.c*/
int						cd_helper(t_data *data);
int						cd_null(t_data *data);
void					update_pwd(char *old_pwd, t_data *data);
int						many_args_mess(void);
//int						cd_builtin(t_cmd *cmd, t_data *data);
void					message_cd(char *path);
/*echo.c*/
//int						echo_builtin(t_cmd *cmd);
/*env.c*/
/*exit.c*/
int						atol_minishell(const char *str);
//int						exit_builtin(t_cmd *cmd, t_data *data);
/*pwd.c*/
int						pwd_builtin(void);
/*unset.c*/
int						find_index(char *index, char **env);
//int						unset_builtin(t_cmd *cmd, t_data *data);
/*all export*/
void					print_export(char *value);
void					export_no_args(t_data *data);
void					export_helper(char *arg, t_data *data, int *n);
//int						export_builtin(t_cmd *cmd, t_data *data);
int						export_no_value(char *args, t_data *data, int *n);
int						is_valid_id(char *arg);
int						export_error(char *arg, t_data *data);
int						count_env(t_data *data);
/*env_shell.c*/
void					update_env(char *key, char *value, t_data *data);
char					**dup_env(char **env);
/*free*/
void					ft_free_tab(t_data *data);

#endif
