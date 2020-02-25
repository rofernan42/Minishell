/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofernan <rofernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 16:04:12 by rofernan          #+#    #+#             */
/*   Updated: 2020/02/25 16:07:23 by rofernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void ft_p(char **s)
{
	int i;

	i = 0;
	while (s[i])
	{
		dprintf(2, "s[%d] = [%s]\n", i, s[i]);
		i++;
	}
}

static void	recursive(t_shell *shell, int i)
{
	h_split(shell, &shell->next_args);
	exec_pipe(shell, i);
}

void		fork_left(t_shell *shell, int *pdes)
{
	int status;

	signal(SIGINT, NULL);
	signal(SIGQUIT, NULL);
	close(pdes[0]);
	dup2(pdes[1], 1);
	if (!(status = is_builtin(shell)))
	{
		exit(execute_cmd(shell->args, shell));
	}
	exit(0);
}

void		fork_right(t_shell *shell, int *pdes, int i)
{
	int status;

	signal(SIGINT, NULL);
	signal(SIGQUIT, NULL);
	if (!(shell->args == NULL && shell->next_args != NULL))
	{
		close(pdes[1]);
		dup2(pdes[0], 0);
	}
	if ((shell->args && shell->next_args))
			recursive(shell, i + 1);
	else if (!(status = is_builtin(shell)))
	{
		if (reste_arg(shell->next_args, inv('|')))
			recursive(shell, i + 1);
		else if (shell->next_args != NULL)
			exit(execute_cmd(shell->next_args, shell));
	}
	exit(0);
}
