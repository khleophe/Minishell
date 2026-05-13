/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdabbas <sdabbas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 19:43:38 by nolwenng          #+#    #+#             */
/*   Updated: 2026/04/29 17:27:53 by sdabbas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*int	main(int ac, char **av, char **envp)
{
	t_data	data;
	t_token	*tokens;
	t_cmd	*cmds;
	t_pipe	p;
	char	*line;

	data.env = dup_env(envp);
	data.return_code = 0;
	p.prev_fd = -1;
	interactive_signals();
	while (1)
	{
		line = readline("minishell$ ");
		if (line == NULL)
		{
			free(line);
			break ;
		}
		if (g_signal == 130)
		{
			data.return_code = 130;
			g_signal = 0;
		}
		if (verif_line(line))
			add_history(line);
		tokens = lexer(line);
		//cmds = parser(tokens, &data); // voir avec soraya pour  le parser
		if (cmds)
		{
			if (cmds->next == NULL)
				execute(cmds, &data);
			else if (cmds->next != NULL)
			{
				p.prev_fd = -1;
				exec_pipeline(cmds, &p, &data);
			}
		}
		free(line);
		free_tokens(tokens);
		free_cmds(cmds);
	}
	ft_free_tab(&data);
	rl_clear_history();
	return (0);
}

static void	run(char **args, t_data *data)
{
	t_cmd	cmd;

	cmd.args = args;
	cmd.redirs = NULL;
	cmd.next = NULL;
	execute(&cmd, data);
}

int	main(int ac, char **av, char **env)
{
	t_data	data;
	char	*echo_n[] = {"echo", "-n", "hello", NULL};
	char	*pwd[] = {"pwd", NULL};
	char	*cd_tmp[] = {"cd", "/tmp", NULL};
	char	*cd_back[] = {"cd", "-", NULL};
	char	*export_var[] = {"export", "TEST=42", NULL};
	char	*env_cmd[] = {"env", NULL};
	char	*unset_var[] = {"unset", "TEST", NULL};
	char	*invalid_export[] = {"export", "1foo=x", NULL};
	char	*not_found[] = {"commande_inexistante", NULL};

	(void)ac;
	(void)av;
	data.env = dup_env(env);
	data.return_code = 0;
	write(1, "--- echo -n hello ---\n", 22);
	run(echo_n, &data);
	write(1, "\n--- pwd ---\n", 13);
	run(pwd, &data);
	write(1, "--- cd /tmp ---\n", 16);
	run(cd_tmp, &data);
	write(1, "--- pwd apres cd /tmp ---\n", 26);
	run(pwd, &data);
	write(1, "--- cd - ---\n", 13);
	run(cd_back, &data);
	write(1, "--- export TEST=42 ---\n", 23);
	run(export_var, &data);
	write(1, "--- env (cherche TEST) ---\n", 27);
	run(env_cmd, &data);
	write(1, "--- unset TEST ---\n", 19);
	run(unset_var, &data);
	write(1, "--- export 1foo=x ---\n", 22);
	run(invalid_export, &data);
	write(1, "--- commande inexistante ---\n", 29);
	run(not_found, &data);
	ft_free_tab(&data);
	return (0);
}

int	main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	t_cmd	cmd;
	t_cmd	cmd2;
	t_cmd	cmd3;
	t_data	data;
	t_pipe	p;
	char	*args[] = {"ls", NULL};
	char	*args2[] = {"grep", ".c", NULL};
	char	*args3[] = {"wc", "-l", NULL};
	data.env = dup_env(env);
	data.return_code = 0;
	p.prev_fd = -1;
	cmd.args = args;
	cmd2.args = args2;
	cmd3.args = args3;
	cmd.redirs = NULL;
	cmd.next = &cmd2;
	cmd2.redirs = NULL;
	cmd2.next = &cmd3;
	cmd3.redirs = NULL;
	cmd3.next = NULL;
	exec_pipeline(&cmd, &p, &data);
	ft_free_tab(&data);
	return (0);
}


int	main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	t_redir	redir;
	t_cmd	cmd;
	t_data data;
	char	*arg[] = {"cat", NULL};
	data.env = dup_env(env);
	data.return_code = 0;
	cmd.args = arg;
	cmd.redirs = &redir;
	cmd.next = NULL;
	redir.type = HEREDOC;
	redir.file = "la";
	redir.next = NULL;
	execute(&cmd, &data);
	ft_free_tab(&data);
	return (0);
}
*/
