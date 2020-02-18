/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stdin.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofernan <rofernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 16:44:54 by rofernan          #+#    #+#             */
/*   Updated: 2020/02/18 18:41:14 by rofernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	**extract(t_shell *shell)
{
	int		i;
	int		j;
	char	**tmp;

	i = 0;
	j = 0;
	while (shell->args[i])
	{
		if (i == 0 || (i > 0 && !is_chevron(shell->args[i]) \
		&& !is_chevron(shell->args[i - 1])))
			j++;
		i++;
	}
	if (!(tmp = malloc(sizeof(char*) * (j + 1))))
		exit(EXIT_FAILURE);
	i = 0;
	j = 0;
	while (shell->args[i])
	{
		if (i == 0 || (i > 0 && !is_chevron(shell->args[i]) \
		&& !is_chevron(shell->args[i - 1])))
			tmp[j++] = ft_strdup(shell->args[i]);
		i++;
	}
	tmp[j] = NULL;
	return (tmp);
}

static int	is_builtin(t_shell *shell)
{
	shell->args = extract(shell);
	if (!ft_strcmp(shell->args[0], "echo"))
		ft_echo(shell);
	else if (!ft_strncmp(shell->args[0], "cd", 2))
		ft_cd(shell->args[1], shell->env);
	else if (!ft_strcmp(shell->args[0], "pwd"))
		ft_pwd(shell->env);
	else if (!ft_strcmp(shell->args[0], "export"))
		ft_export(&shell->args[1], shell->env);
	else if (!ft_strcmp(shell->args[0], "unset"))
		ft_unset(&shell->args[1], shell->env);
	else if (!ft_strcmp(shell->args[0], "env"))
		ft_env(shell->env);
	else if (!ft_strcmp(shell->args[0], "exit"))
	{
		ft_putendl_fd("exit", 1);
		free_all(shell);
		exit(0);
	}
	else
		return (0);
	return (1);
}

static void	process_exec(t_shell *shell)
{
	char **tmp;

	tmp = extract(shell);
	execve(shell->args[0], tmp, 0);
}

static void	copy_stdinout(t_shell *shell)
{
	if (shell->fd_in >= 0)
	{
		shell->stdout_cpy = dup(1);
		close(1);
		dup2(shell->fd_in, 1);
	}
	if (shell->fd_out >= 0)
	{
		shell->stdin_cpy = dup(0);
		close(0);
		dup2(shell->fd_out, 0);
	}
}

static void	close_stdinout(t_shell *shell)
{
	if (shell->fd_in >= 0)
	{
		dup2(shell->stdout_cpy, 1);
		close(shell->stdout_cpy);
	}
	if (shell->fd_out >= 0)
	{
		dup2(shell->stdin_cpy, 0);
		close(shell->stdin_cpy);
	}
}

void		ft_stdin(t_shell *shell, char **command)
{
	int end;
	int part;
	int last_part;
	int pipe_fd[2];

	pipe(pipe_fd);
	part = 0;
	last_part = 0;
	end = ft_tablength(command);
	while (part <= end)
	{
		if (part == end || !ft_strcmp(command[part], "|"))
		{
			shell->args = ft_tabcopy(command + last_part, part - last_part);
			if (shell->args[0])
			{
				if (open_fd(shell))
				{
					copy_stdinout(shell);
					if (!is_builtin(shell))
					{
						if (fork() == 0)
						{
							prep_path(shell);
							process_exec(shell);
							exit(0);
						}
						else
							wait(NULL);
					}
					close_stdinout(shell);
				}
			}
			last_part = part + 1;
			del_args(shell->args);
		}
		part++;
		
		// free(shell->command);
		// shell->command = ft_strdup("");
	}
	del_args(command);
}
