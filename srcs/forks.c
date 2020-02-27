/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: augay <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 12:29:22 by augay             #+#    #+#             */
/*   Updated: 2020/02/27 12:29:25 by augay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	fork_right(t_shell *shell, int i, int *pdes)
{
	if (shell->args)
	{
		close(pdes[1]);
		dup2(pdes[0], STDIN_FILENO);
	}
	if (still(shell) == 1)
	{
		h_split(shell, &shell->next_args);
		exec_pipe(shell, i + 1);
	}
	else if (shell->next_args != NULL)
		exit(execute_cmd(shell->next_args, shell));
}

int		first(t_shell *shell)
{
	int ret;

	shell->next_args = shell->args;
	shell->args = NULL;
	if (!open_fd(shell, shell->next_args))
		return (1);
	copy_stdinout(shell);
	if (is_builtin(shell->next_args))
	{
		ret = builtin_exec(shell, shell->next_args);
		close_stdinout(shell);
		return (ret);
	}
	else
	{
		close_stdinout(shell);
		return (-1);
	}
}

void	fork_left(int *pdes, t_shell *shell)
{
	close(pdes[0]);
	dup2(pdes[1], STDOUT_FILENO);
	exit(execute_cmd(shell->args, shell));
}
