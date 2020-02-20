/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofernan <rofernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 11:15:51 by rofernan          #+#    #+#             */
/*   Updated: 2020/02/20 13:14:06 by rofernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	**extract(char **args)
{
	int		i;
	int		j;
	char	**tmp;

	i = 0;
	j = 0;
	while (args[i])
	{
		if (i == 0 || (i > 0 && !is_chevron(args[i]) \
		&& !is_chevron(args[i - 1])))
			j++;
		i++;
	}
	if (!(tmp = malloc(sizeof(char *) * (j + 1))))
		exit(EXIT_FAILURE);
	i = -1;
	j = 0;
	while (args[++i])
		if (i == 0 || (i > 0 && !is_chevron(args[i]) \
		&& !is_chevron(args[i - 1])))
			tmp[j++] = ft_strdup(args[i]);
	tmp[j] = NULL;
	return (tmp);
}

int	is_builtin(t_shell *shell)
{
	char **args;

	if (shell->args)
		args = extract(shell->args);
	else if (!shell->args && shell->next_args)
		args = extract(shell->next_args);
	if (!ft_strcmp(args[0], "echo"))
		ft_echo(args);
	else if (!ft_strncmp(args[0], "cd", 2))
		ft_cd(shell->next_args[1], shell->env);
	else if (!ft_strcmp(args[0], "pwd"))
		ft_pwd(shell->env);
	else if (!ft_strcmp(args[0], "export"))
		ft_export(&args[1], shell->env);
	else if (!ft_strcmp(args[0], "unset"))
		ft_unset(&args[1], shell->env);
	else if (!ft_strcmp(args[0], "env"))
		ft_env(shell->env);
	else if (!ft_strcmp(args[0], "exit"))
	{
		ft_putendl_fd("exit", 1);
		free_all(shell);
		exit(0);
	}
	else
		return (0);
	return (1);
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
	open_fd(shell, shell->args);
	copy_stdinout(shell);
	prep_path(shell);
	process_exec(shell);
	close_stdinout(shell);
	exit(0);
	return (0);
}
