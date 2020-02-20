/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofernan <rofernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 11:15:51 by rofernan          #+#    #+#             */
/*   Updated: 2020/02/20 11:21:10 by rofernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	**extract(t_shell *shell)
{
	int		i;
	int		j;
	char	**tmp;

	i = 0;
	j = 0;
	while (shell->args[i])
	{
		if (i == 0 || (i > 0 && !is_chevron(shell->args[i]) \
		&& !is_chevron(shell->args[i - 1])))
			j++;
		i++;
	}
	if (!(tmp = malloc(sizeof(char *) * (j + 1))))
		exit(EXIT_FAILURE);
	i = -1;
	j = 0;
	while (shell->args[++i])
		if (i == 0 || (i > 0 && !is_chevron(shell->args[i]) \
		&& !is_chevron(shell->args[i - 1])))
			tmp[j++] = ft_strdup(shell->args[i]);
	tmp[j] = NULL;
	return (tmp);
}

static int	is_builtin(t_shell *shell)
{
	shell->args = extract(shell);
	if (!ft_strcmp(shell->args[0], "echo"))
		ft_echo(shell);
	else if (!ft_strncmp(shell->args[0], "cd", 2))
		ft_cd(shell->args[1], shell->env);
	else if (!ft_strcmp(shell->args[0], "pwd"))
		ft_pwd(shell->env);
	else if (!ft_strcmp(shell->args[0], "export"))
		ft_export(&shell->args[1], shell->env);
	else if (!ft_strcmp(shell->args[0], "unset"))
		ft_unset(&shell->args[1], shell->env);
	else if (!ft_strcmp(shell->args[0], "env"))
		ft_env(shell->env);
	else if (!ft_strcmp(shell->args[0], "exit"))
	{
		ft_putendl_fd("exit", 1);
		free_all(shell);
		exit(42);
	}
	else
		return (0);
	return (1);
}

static void	process_exec(t_shell *shell)
{
	char **tmp;

	tmp = extract(shell);
	execve(shell->args[0], tmp, 0);
}

int			execute_cmd(char **cmd, t_shell *shell)
{
	if (cmd == NULL)
		exit(0);
	shell->args = cmd;
	open_fd(shell);
	copy_stdinout(shell);
	if (!is_builtin(shell))
	{
		prep_path(shell);
		process_exec(shell);
		exit(0);
	}
	close_stdinout(shell);
	return (0);
}
