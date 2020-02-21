/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_close_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofernan <rofernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 18:49:19 by rofernan          #+#    #+#             */
/*   Updated: 2020/02/21 18:49:49 by rofernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		copy_stdinout(t_shell *shell)
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

void	close_stdinout(t_shell *shell)
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
