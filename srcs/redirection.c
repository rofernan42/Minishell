/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofernan <rofernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 14:26:58 by rofernan          #+#    #+#             */
/*   Updated: 2020/02/26 13:36:49 by rofernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int			test_syntax(t_shell *shell, char **args)
{
	int i;

	i = -1;
	if (!wrap_cmp(args[0], '|'))
		return (chevron_error(shell->name_prog, ERR_CHEV, args[0], "'"));
	while (args[++i])
	{
		if (i > 0 && is_chevron(args[i - 1]) \
		&& (is_chevron(args[i]) || !wrap_cmp(args[i], '|')))
			return (chevron_error(shell->name_prog, ERR_CHEV, args[i], "'"));
		if (i > 0 && !wrap_cmp(args[i - 1], '|') \
		&& (is_chevron(args[i]) || !wrap_cmp(args[i], '|')))
			return (chevron_error(shell->name_prog, ERR_CHEV, 0, "newline'"));
	}
	if (!args[i] && is_chevron(args[i - 1]))
		return (chevron_error(shell->name_prog, ERR_CHEV, 0, "newline'"));
	return (1);
}

static int	fd_in_out(t_shell *shell, char **args, int i)
{
	if (!is_chevron(args[i]))
	{
		if (!wrap_cmp(args[i - 1], '>'))
			shell->fd_in = open(args[i], O_WRONLY | O_TRUNC | O_CREAT, \
			S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
		else if (!wrap_cmp_2(args[i - 1], ">>"))
			shell->fd_in = open(args[i], O_WRONLY | O_APPEND | O_CREAT, \
			S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
		else if (!wrap_cmp(args[i - 1], '<'))
		{
			if ((shell->fd_out = open(args[i], O_RDONLY)) == -1)
			{
				disp_err(shell->name_prog, 0, args[i], strerror(errno));
				return (0);
			}
		}
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
		}
		i++;
	}
	return (1);
}
