/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofernan <rofernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 10:39:36 by augay             #+#    #+#             */
/*   Updated: 2020/02/25 15:42:51 by rofernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	is_builtin_1(t_shell *shell, char **s)
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
	int		file;

	// dprintf(2, "test7\n");
	if (!is_builtin_1(shell, s))
		return (0);
	// dprintf(2, "test8\n");
	//open_file(shell);
	args = extract(s);
	dprintf(2, "SEND BUILTIN \n");
	ft_p(args);
	builtin_exec(shell, args);
	ft_free(&args);
	return (42);
}
