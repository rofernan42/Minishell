/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stdin.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofernan <rofernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 16:44:54 by rofernan          #+#    #+#             */
/*   Updated: 2020/02/20 11:22:05 by rofernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	h_split(t_shell *shell, char **cmd)
{
	int		fin;
	int		p;
	int		part;
	int		last_part;

	p = 0;
	part = 0;
	last_part = 0;
	fin = ft_tablength(cmd);
	while (part <= fin && p < 1)
	{
		if (part == fin || !strcmp(cmd[part], "|"))
		{
			shell->args = (ft_tabcopy(cmd + last_part, part - last_part));
			last_part = part + 1;
			p++;
		}
		part++;
	}
	if (part < fin)
		shell->next_args = ft_tabcopy(cmd + last_part, fin - last_part);
	else
		shell->next_args = NULL;
}

static void	fork_left(t_shell *shell, int *pdes)
{
	signal(SIGINT, NULL);
	close(pdes[0]);
	dup2(pdes[1], 1);
	exit(execute_cmd(shell->args, shell));
	exit(0);
}

static void	fork_right(t_shell *shell, int *pdes)
{
	signal(SIGINT, NULL);
	if (!(shell->args == NULL && shell->next_args != NULL))
	{
		close(pdes[1]);
		dup2(pdes[0], 0);
	}
	if (reste_arg(shell->next_args, "|"))
	{
		h_split(shell, shell->next_args);
		exec_pipe(shell);
	}
	else if (shell->next_args != NULL)
		exit(execute_cmd(shell->next_args, shell));
	exit(0);
}

void		exec_pipe(t_shell *shell)
{
	int		pdes[2];
	int		status;
	pid_t	child_right;
	pid_t	child_left;

	pipe(pdes);
	if (shell->next_args == NULL && shell->args != NULL)
	{
		shell->next_args = shell->args;
		shell->args = NULL;
	}
	if (shell->args != NULL && !(child_left = fork()))
		fork_left(shell, pdes);
	if (!(child_right = fork()))
		fork_right(shell, pdes);
	close(pdes[1]);
	close(pdes[0]);
	waitpid(child_left, NULL, 0);
	waitpid(child_right, &status, 0);
	if (WIFEXITED(status) == 1 && WEXITSTATUS(status) == 42)
		exit(0);
	if (WIFEXITED(status) != 0)
		ft_putstr_fd("\033[33mminishell$\033[0m ", 1);
}

void		ft_stdin(t_shell *shell, char **command)
{
	h_split(shell, command);
	exec_pipe(shell);
}
