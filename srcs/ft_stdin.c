/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stdin.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofernan <rofernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 16:44:54 by rofernan          #+#    #+#             */
/*   Updated: 2020/02/18 14:42:07 by rofernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	is_builtin(t_shell *shell)
{
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
	int		i;
	char	**tmp;

	i = 0;
	while (shell->args[i])
	{
		if (!ft_strcmp(shell->args[i], ">") || !ft_strcmp(shell->args[i], "<") \
		|| !ft_strcmp(shell->args[i], ">>"))
			break ;
		i++;
	}
	if (!(tmp = malloc(sizeof(char*) * (i + 1))))
		exit(EXIT_FAILURE);
	i = 0;
	while (shell->args[i])
	{
		if (ft_strcmp(shell->args[i], ">") && ft_strcmp(shell->args[i], "<") \
		&& ft_strcmp(shell->args[i], ">>"))
			tmp[i] = ft_strdup(shell->args[i]);
		else
			break ;
		i++;
	}
	tmp[i] = NULL;
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

void		ft_stdin(t_shell *shell)
{
	if (open_fd(shell))
	{
		copy_stdinout(shell);
		if (!is_builtin(shell))
		{
			if (fork() == 0)
			{
				process_exec(shell);
				exit(0);
			}
			else
				wait(NULL);
		}
		close_stdinout(shell);
	}
	free(shell->command);
	shell->command = ft_strdup("");
	del_args(shell->args);
}
