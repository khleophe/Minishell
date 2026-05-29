/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdabbas <sdabbas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 05:13:29 by nolwenng          #+#    #+#             */
/*   Updated: 2026/05/29 15:03:22 by sdabbas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// protege les verif_dup2
void	verif_dup2(int old_fd, int new_fd)
{
	if (dup2(old_fd, new_fd) == -1)
	{
		perror("dup2_error");
		exit(EXIT_FAILURE);
	}
}

void	mess_pipe(void)
{
	perror("pipe");
	exit(EXIT_FAILURE);
}

// gere la chaine de commande
void	exec_pipeline(t_cmd *cmd, t_pipe *p, t_data *data)
{
	char	*path;

//	exec_signals();
	while (cmd != NULL)
	{
		path = find_path(cmd->args[0], data->env);
		if (cmd->next != NULL)
		{
			if (pipe(p->pipefd) == -1)
				mess_pipe();
			child_write(p, path, cmd, data);
			if (p->prev_fd != -1)
				close(p->prev_fd);
			free(path);
			p->prev_fd = p->pipefd[0];
			cmd = cmd->next;
		}
		else
		{
			child_read(p, path, cmd, data);
			free(path);
			cmd = cmd->next;
		}
	}
}

/*int main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	t_cmd cmd1;
	t_cmd cmd2;
	t_cmd cmd3;
	t_pipe p;
	char *args1[] = {"ls", "-la", NULL};
	char *args2[] = {"grep", ".c", NULL};
	char *args3[] = {"wc", "-l", NULL};
	cmd1.args = args1;
	cmd2.args = args2;
	cmd3.args = args3;
	cmd1.redirs = NULL;
	cmd2.redirs = NULL;
	cmd3.redirs = NULL;
	cmd1.next = &cmd2;
	cmd2.next = &cmd3;
	cmd3.next = NULL;
	p.prev_fd = -1;
	exec_pipeline(&cmd1, &p, env);
	return (0);
}*/
