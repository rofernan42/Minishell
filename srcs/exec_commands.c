/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofernan <rofernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 11:15:51 by rofernan          #+#    #+#             */
/*   Updated: 2020/02/21 13:24:37 by rofernan         ###   ########.fr       */
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
		if (!ft_strcmp(args[i], "|"))
			break ;
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
	{
		if (!ft_strcmp(args[i], "|"))
			break ;
		if (i == 0 || (i > 0 && !is_chevron(args[i]) \
		&& !is_chevron(args[i - 1])))
			tmp[j++] = ft_strdup(args[i]);
	}
	tmp[j] = NULL;
	return (tmp);
}

int			is_builtin_1(t_shell *shell)
{
	char **args;

	if (shell->args)
		args = extract(shell->args);
	else if (!shell->args && shell->next_args)
		args = extract(shell->next_args);
	if (!ft_strcmp(args[0], "echo"))
		return (1);
	else if (!ft_strncmp(args[0], "cd", 2))
		return (1);
	else if (!ft_strcmp(args[0], "pwd"))
		return (1);
	else if (!ft_strcmp(args[0], "export"))
		return (1);
	else if (!ft_strcmp(args[0], "unset"))
		return (1);
	else if (!ft_strcmp(args[0], "env"))
		return (1);
	else if (!ft_strcmp(args[0], "exit"))
		return (1);
	return (0);
}

int			is_builtin(t_shell *shell, int i)
{
	char	**args;
	int		file;

	if (!is_builtin_1(shell))
		return (0);
	if (!open_file(shell))
		return (1);
	file = copy_stdinout(shell);
	if (shell->args)
		args = extract(shell->args);
	else if (!shell->args && shell->next_args)
		args = extract(shell->next_args);
	if ((!file && !shell->args) || file)
	{
		if (!ft_strcmp(args[0], "echo"))
			ft_echo(args);
		else if (!ft_strcmp(args[0], "cd"))
			ft_cd(shell, shell->next_args[1]);
		else if (!ft_strcmp(args[0], "pwd"))
			ft_pwd(shell->env);
		else if (!ft_strcmp(args[0], "export"))
			ft_export(shell, &args[1]);
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
			return (1);
		if (file)
			close_stdinout(shell);
	}
	if ((shell->args && shell->next_args))
	{
		h_split(shell, shell->next_args);
		exec_pipe(shell, i + 1);
	}
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
	if (!open_fd(shell, shell->args))
		exit(0);
	copy_stdinout(shell);
	prep_path(shell);
	process_exec(shell);
	close_stdinout(shell);
	exit(0);
	return (0);
}
