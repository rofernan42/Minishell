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
	exec_pipe(shell, i+1);
}

void		fork_left(t_shell *shell, int *pdes)
{
	int status;

	signal(SIGINT, NULL);
	signal(SIGQUIT, NULL);
	dprintf(2, "CLOSE LEFT PDES0, DUP PDES1, 1\n");
	close(pdes[0]);
	dup2(pdes[1], 1);
	if (!(status = is_builtin(shell, NULL)))
	{
		execute_cmd(shell->args, shell);
		// printf("FORK LEFT GSIG=%i\n", g_sig);
		exit(g_sig);
	}
	// exit(0);
}

void		fork_right(t_shell *shell, int *pdes, int i)
{
	int status;
	// dprintf(2,"JE EXEC RIGHT=%i\n", g_sig);

	signal(SIGINT, NULL);
	signal(SIGQUIT, NULL);
	// if (shell->args != NULL)
	// {
		// dprintf(2, "CLOSE RIGHT PDES1, DUP PDES0, 0\n");
		close(pdes[1]);
		dup2(pdes[0], 0);
	// }
	// if ((shell->args && shell->next_args))
	// 		recursive(shell, i + 1);
	// else if (!(status = is_builtin(shell)))
	// {
	// 	if (shell->next_args != NULL)
	// 		{
	// 					execute_cmd(shell->next_args, shell);
	// 											// printf("JE RETURN gsg=%i\n", g_sig);

	// 			exit(g_sig);
	// 			}
	// }
		// close_stdinout(shell);

	if (!is_builtin(shell, NULL))
	{
		execute_cmd(shell->args, shell);
	}
	// exit(0);
}
