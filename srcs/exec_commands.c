/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofernan <rofernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 11:15:51 by rofernan          #+#    #+#             */
/*   Updated: 2020/02/25 15:00:39 by rofernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char		**extract(char **args)
{
	int		i;
	int		j;
	char	**tmp;

	i = -1;
	j = 0;
	while (args[++i])
		if (!wrap_cmp(args[i], '|'))
			break ;
		else if (i == 0 || (i > 0 && !is_chevron(args[i]) \
		&& !is_chevron(args[i - 1])))
			j++;
	if (!(tmp = malloc(sizeof(char *) * (j + 1))))
		exit(EXIT_FAILURE);
	i = -1;
	j = 0;
	while (args[++i])
		if (!wrap_cmp(args[i], '|'))
			break ;
		else if (i == 0 || (i > 0 && !is_chevron(args[i]) \
		&& !is_chevron(args[i - 1])))
			tmp[j++] = ft_strdup(args[i]);
	tmp[j] = NULL;
	return (tmp);
}

static void	process_exec(t_shell *shell)
{
	char **tmp;

	tmp = extract(shell->args);
	// if (shell->next_args != NULL)
	// {
	// 	h_split(shell, &shell->next_args);
	// 	exec_pipe(shell, 8);
	// }
	dprintf(2,"EXECV de \n");
	ft_p(shell->args);
	execve(shell->args[0], tmp, 0);
}

void			execute_cmd(char **cmd, t_shell *shell)
{
	// if (cmd == NULL)
	// 	exit(0);
	dprintf(2, "EXEC CMD DATA in PID=%i et\n", getpid());
	if (shell->args != NULL)
	{
		ft_p(shell->args);
	}
	else
	{
		dprintf(2, "SHELL->ARGS=NULL\n");
	}
	if (shell->next_args != NULL)
	{
		ft_p(shell->next_args);
	}
	else
	{
		dprintf(2, "SHELL->NEXT_ARGS=NULL\n");
	}
if (cmd != NULL)
	{
		ft_p(cmd);
	}
	else
	{
		dprintf(2, "CMD=NULL\n");
	}
	shell->args = cmd;
	// if (!open_fd(shell, shell->args))
	// 	exit(1);
	// copy_stdinout(shell);
	// prep_path(shell);
	// dup2(2, 1);
	process_exec(shell);
	// close_stdinout(shell);
}
