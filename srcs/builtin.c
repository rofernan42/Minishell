/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofernan <rofernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 10:39:36 by augay             #+#    #+#             */
/*   Updated: 2020/02/24 11:51:15 by rofernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void ft_p(char **s)
{
	int i = 0;
	while(s[i])
	{
		printf("s[%i]=[%s]\n",i,s[i]);
		i++;
	}
}

int			is_builtin_1(t_shell *shell)
{
	char **args;

	args = NULL;
	if (shell->args)
		args = extract(shell->args);
	else if (!shell->args && shell->next_args)
		args = extract(shell->next_args);
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

void		builtin_exec(t_shell *shell, char **args)
{
	if (!ft_strcmp(args[0], "echo"))
		ft_echo(args);
	else if (!ft_strcmp(args[0], "cd"))
		ft_cd(shell, shell->next_args[1]);
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

int			is_builtin(t_shell *shell, int i)
{
	char	**args;
	int		file;

	if (!is_builtin_1(shell))
		return (0);
	open_file(shell);
	file = copy_stdinout(shell);
	if (shell->args)
		args = extract(shell->args);
	else if (!shell->args && shell->next_args)
		args = extract(shell->next_args);
	if ((!file && !shell->args) || file)
	{
		builtin_exec(shell, args);
		if (file)
			close_stdinout(shell);
	}
	if ((shell->args && shell->next_args))
	{
		ft_free(&args);
		h_split(shell, &shell->next_args);
		exec_pipe(shell, i + 1);
	}
	ft_free(&args);
	return (-42);
}
