/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofernan <rofernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 11:15:51 by rofernan          #+#    #+#             */
/*   Updated: 2020/02/24 16:56:13 by rofernan         ###   ########.fr       */
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
		if (!ft_strcmp(args[i], "|"))
			break ;
		else if (i == 0 || (i > 0 && !is_chevron(args[i]) \
		&& !is_chevron(args[i - 1])))
			j++;
	if (!(tmp = malloc(sizeof(char *) * (j + 1))))
		exit(EXIT_FAILURE);
	i = -1;
	j = 0;
	while (args[++i])
		if (!ft_strcmp(args[i], "|"))
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
	execve(shell->args[0], tmp, 0);
}

int			execute_cmd(char **cmd, t_shell *shell)
{
	if (cmd == NULL)
		exit(0);
	shell->args = cmd;
	if (!open_fd(shell, shell->args))
		exit(1);
	copy_stdinout(shell);
	prep_path(shell);
	process_exec(shell);
	close_stdinout(shell);
	exit(0);
	return (1);
}
