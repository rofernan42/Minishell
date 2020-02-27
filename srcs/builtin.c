/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofernan <rofernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 10:39:36 by augay             #+#    #+#             */
/*   Updated: 2020/02/26 15:54:32 by rofernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	is_builtin_1(char **s)
{
	char **args;

	args = extract(s);
	if (!ft_strcmp(args[0], "echo"))
		return (del_war(&args, 1));
	else if (!ft_strcmp(args[0], "cd"))
		return (del_war(&args, 1));
	else if (!ft_strcmp(args[0], "pwd"))
		return (del_war(&args, 1));
	else if (!ft_strcmp(args[0], "export"))
		return (del_war(&args, 1));
	else if (!ft_strcmp(args[0], "unset"))
		return (del_war(&args, 1));
	else if (!ft_strcmp(args[0], "env"))
		return (del_war(&args, 1));
	else if (!ft_strcmp(args[0], "exit"))
		return (del_war(&args, 1));
	return (del_war(&args, 0));
	ft_free(&args);
}

static void	builtin_exec(t_shell *shell, char **args)
{
	if (!ft_strcmp(args[0], "echo"))
		ft_echo(args);
	else if (!ft_strcmp(args[0], "cd"))
		ft_cd(shell, args[1]);
	else if (!ft_strcmp(args[0], "pwd"))
		ft_pwd();
	else if (!ft_strcmp(args[0], "export"))
		ft_export(shell, &args[1]);
	else if (!ft_strcmp(args[0], "unset"))
		ft_unset(&args[1], shell->env);
	else if (!ft_strcmp(args[0], "env"))
		ft_env(shell->env);
	else if (!ft_strcmp(args[0], "exit"))
		ft_exit(shell, args);
}

int			is_builtin(t_shell *shell, char **s)
{
	char	**args;

	if (!is_builtin_1(s))
		return (0);
	args = extract(s);
	builtin_exec(shell, args);
	ft_free(&args);
	return (42);
}
