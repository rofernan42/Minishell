/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofernan <rofernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 14:26:58 by rofernan          #+#    #+#             */
/*   Updated: 2020/02/18 13:14:26 by rofernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	fd_in_out(t_shell *shell, int i)
{
	if (ft_strcmp(shell->args[i], ">") && ft_strcmp(shell->args[i], "<") \
	&& ft_strcmp(shell->args[i], ">>"))
	{
		if (!ft_strcmp(shell->args[i - 1], ">"))
			shell->fd_in = open(shell->args[i], O_WRONLY | O_TRUNC | O_CREAT, \
			S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
		else if (!ft_strcmp(shell->args[i - 1], ">>"))
			shell->fd_in = open(shell->args[i], O_WRONLY | O_APPEND | O_CREAT, \
			S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
		else if (!ft_strcmp(shell->args[i - 1], "<"))
		{
			if ((shell->fd_out = open(shell->args[i], O_RDONLY)) == -1)
			{
				disp_err(shell->args[i], 0, ": ", strerror(errno));
				return (0);
			}
		}
	}
	else
	{
		disp_err("syntax error near unexpected token `", \
		shell->args[i], 0, "'");
		return (0);
	}
	return (1);
}

int			open_fd(t_shell *shell)
{
	int i;

	i = 0;
	shell->fd_in = -5;
	shell->fd_out = -5;
	while (shell->args[i])
	{
		if (!ft_strcmp(shell->args[i], ">") || !ft_strcmp(shell->args[i], "<") \
		|| !ft_strcmp(shell->args[i], ">>"))
		{
			if (shell->args[i + 1])
			{
				if (!fd_in_out(shell, i + 1))
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
