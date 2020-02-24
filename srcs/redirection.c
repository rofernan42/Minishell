/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofernan <rofernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 14:26:58 by rofernan          #+#    #+#             */
/*   Updated: 2020/02/21 18:49:52 by rofernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int wrap_cmp(char *s, char c)
{
	char *s2 = inv(c);
	int i= ft_strcmp(s, s2);
	free(s2);
	return (i);
}

int			test_syntax(t_shell *shell, char **args)
{
	int i;

	i = -1;
	if (!wrap_cmp(args[0], '|'))
		return (chevron_error(shell->name_prog,
	"syntax error near unexpected token `", args[0], "'"));
	while (args[++i])
	{
		if (i > 0 && is_chevron(args[i - 1]) && (is_chevron(args[i])
		|| !wrap_cmp(args[i], '|')))
		{
			chevron_error(shell->name_prog,
					"syntax error near unexpected token `", args[i], "'");
			return (0);
		}
		if (i > 0 && !ft_strcmp(args[i - 1], "|") && (is_chevron(args[i])
		|| !wrap_cmp(args[i], '|')))
		{
			chevron_error(shell->name_prog,
					"syntax error near unexpected token ", 0, "`newline'");
			return (0);
		}
	}
	return (1);
}

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
