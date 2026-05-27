/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdabbas <sdabbas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 10:27:17 by sdabbas           #+#    #+#             */
/*   Updated: 2026/05/27 14:45:45 by sdabbas          ###   ########.fr       */
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
}					t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*s;
	struct s_token	*next;
}					t_token;

typedef struct s_data
{
	char			**env;
	int				return_code;
	t_token			*tokens;
	int				pipe_nb;
}					t_data;

typedef struct s_redir
{
	t_token_type	type;
	char			*file;
	struct s_redir	*next;
}					t_redir;

typedef struct s_cmd
{
	char			**args;
	t_redir			*redirs;
	struct s_cmd	*next;
}					t_cmd;

typedef struct s_pipe
{
	int				pipefd[2];
	int				prev_fd;
}					t_pipe;

/*init*/
void				read_line(t_token **tokens, t_data *data);

/*lexer*/
void				free_tokens(t_token *list);
t_token				*new_token(t_token_type type, char *value);
void				add_token(t_token **tokens, t_token *new);
t_token				*lexer(char *line);
int					verif_line(char *str);
void				exec_command(char *str, t_data *data);
void				expand_all_tokens(t_token *token, t_data *data);
char				*expand_str(char *s, t_data *data);
void				rm_quotes_token(t_token *tokens);
int					check_syntax(t_data *data);

/*exec.c*/
int					execute(t_cmd *cmd, t_data *data);
void				status_return_code(t_data *data, int status);
/*pipe.c*/
void				verif_dup2(int old_fd, int new_fd);
void				child_write(t_pipe *p, char *path, t_cmd *cmd,
						t_data *data);
void				child_read(t_pipe *p, char *path, t_cmd *cmd, t_data *data);
void				exec_pipeline(t_cmd *cmd, t_pipe *p, t_data *data);
void				mess_execve(t_cmd *cmd);
/*redirs.c*/
void				apply_redirs(t_redir *redirs, t_data *data);

/*builtins.c*/
int					init_builtins(t_data *data, t_cmd *cmd);
int					cmp_builtins(t_cmd *cmd);
/*cd.c*/
int					cd_helper(t_data *data);
int					cd_null(t_data *data);
void				update_pwd(char *old_pwd, t_data *data);
int					many_args_mess(void);
int					cd_builtin(t_cmd *cmd, t_data *data);
void				message_cd(char *path);
/*echo.c*/
int					echo_builtin(t_cmd *cmd);
/*env.c*/
int					env_builtin(t_data *path);
/*exit.c*/
int					atol_minishell(const char *str);
int					exit_builtin(t_cmd *cmd, t_data *data);
/*pwd.c*/
int					pwd_builtin(void);
/*unset.c*/
int					find_index(char *index, char **env);
int					unset_builtin(t_cmd *cmd, t_data *data);
/*all export*/
void				print_export(char *value);
void				export_no_args(t_data *data);
void				export_helper(char *arg, t_data *data, int *n);
int					export_builtin(t_cmd *cmd, t_data *data);
int					export_no_value(char *args, t_data *data, int *n);
int					is_valid_id(char *arg);
int					export_error(char *arg, t_data *data);
int					count_env(t_data *data);
/*env_shell.c*/
void				update_env(char *key, char *value, t_data *data);
char				**dup_env(char **env);
/*free*/
void				ft_free_tab(t_data *data);
void				free_redirs(t_redir *redirs);
void				free_cmds(t_cmd *cmd);
/*signals*/
extern int			g_signal;
void				interactive_signals(void);
void				exec_signals(void);
/*heredoc*/
void				handle_redir_heredoc(t_redir *redirs, t_data *data);
void				mess_heredoc(t_redir *redirs, int count);
/*path.c*/
char				*get_env_value(char *key, char **env);
char				*find_path(char *cmd, char **env);
char				*access_path(char *cmd);
char				*path_helper(char *dir, char *cmd);

#endif
