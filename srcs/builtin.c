/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofernan <rofernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 10:39:36 by augay             #+#    #+#             */
/*   Updated: 2020/02/27 11:51:13 by rofernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		is_builtin(t_shell *shell, char **s)
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
}

int		builtin_exec(t_shell *shell, char **s)
{
	int		ret;
	char	**args;

	args = extract(s);
	if (!ft_strcmp(args[0], "echo"))
		ret = ft_echo(args);
	else if (!ft_strcmp(args[0], "cd"))
		ret = ft_cd(shell, args[1]);
	else if (!ft_strcmp(args[0], "pwd"))
		ret = ft_pwd();
	else if (!ft_strcmp(args[0], "export"))
		ret = ft_export(shell, &args[1]);
	else if (!ft_strcmp(args[0], "unset"))
		ret = ft_unset(&args[1], shell->env);
	else if (!ft_strcmp(args[0], "env"))
		ret = ft_env(shell->env);
	else if (!ft_strcmp(args[0], "exit"))
		ret = ft_exit(shell, args);
	ft_free(&args);
	return (ret);
}

// int			execute_builtin(t_shell *shell, char **s)
// {
// 	char	**args;
// 	int		ret;

// 	args = extract(s);
// 	ret = builtin_exec(shell, args);
// 	ft_free(&args);
// 	return (ret);
// }
