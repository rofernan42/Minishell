/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofernan <rofernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 14:26:58 by rofernan          #+#    #+#             */
/*   Updated: 2020/02/25 10:30:20 by rofernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int			wrap_cmp(char *s, char c)
{
	char	*s2;
	int		i;

	s2 = inv(c);
	i = ft_strcmp(s, s2);
	free(s2);
	return (i);
}

int			wrap_cmp_2(char *s, char *c)
{
	char	*s2;
	int		i;

	s2 = malloc(sizeof(char) * 3);
	s2[0] = -1 * c[0];
	s2[1] = -1 * c[1];
	s2[2] = '\0';
	i = ft_strcmp(s, s2);
	free(s2);
	return (i);
}

int			test_syntax(t_shell *shell, char **args)
{
	int i;

	i = -1;
	if (!wrap_cmp(args[0], '|'))
	{
		return (chevron_error(shell->name_prog,
		"syntax error near unexpected token `", args[0], "'"));
	}
	while (args[++i])
	{
		if (i > 0 && is_chevron(args[i - 1]) && (is_chevron(args[i])
		|| !wrap_cmp(args[i], '|')))
		{
			chevron_error(shell->name_prog,
			"syntax error near unexpected token `", args[i], "'");
			return (258);
		}
		if (i > 0 && !ft_strcmp(args[i - 1], "|") && (is_chevron(args[i])
		|| !wrap_cmp(args[i], '|')))
		{
			chevron_error(shell->name_prog,
			"syntax error near unexpected token ", 0, "`newline'");
			return (258);
		}
	}
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
