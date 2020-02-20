/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofernan <rofernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 14:26:58 by rofernan          #+#    #+#             */
/*   Updated: 2020/02/20 21:14:39 by rofernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	fd_in_out(t_shell *shell, char **args, int i)
{
	if (!is_chevron(args[i]))
	{
		if (!ft_strcmp(args[i - 1], ">"))
			shell->fd_in = open(args[i], O_WRONLY | O_TRUNC | O_CREAT, \
			S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
		else if (!ft_strcmp(args[i - 1], ">>"))
			shell->fd_in = open(args[i], O_WRONLY | O_APPEND | O_CREAT, \
			S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
		else if (!ft_strcmp(args[i - 1], "<"))
		{
			if ((shell->fd_out = open(args[i], O_RDONLY)) == -1)
			{
				disp_err(args[i], 0, ": ", strerror(errno));
				return (0);
			}
		}
	}
	else
	{
		disp_err("syntax error near unexpected token `", args[i], 0, "'");
		return (0);
	}
	return (1);
}

int			open_fd(t_shell *shell, char **args)
{
	int i;

	i = 0;
	shell->fd_in = -5;
	shell->fd_out = -5;
	while (args[i])
	{
		if (is_chevron(args[i]))
		{
			if (args[i + 1])
			{
				if (!fd_in_out(shell, args, i + 1))
					return (0);
			}
			else
			{
				disp_err(0, 0, 0, \
				"syntax error near unexpected token `newline'");
				return (0);
			}
		}
		i++;
	}
	return (1);
}

int			copy_stdinout(t_shell *shell)
{
	if (shell->fd_in >= 0 || shell->fd_out >= 0)
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
		return (1);
	}
	return (0);
}

void		close_stdinout(t_shell *shell)
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

int			open_file(t_shell *shell)
{
	if (shell->args)
	{
		if (!open_fd(shell, shell->args))
			return (0);
	}
	else if (!shell->args && shell->next_args)
	{
		if (!open_fd(shell, shell->next_args))
			return (0);
	}
	return (1);
}
