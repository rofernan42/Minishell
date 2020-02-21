/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofernan <rofernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 11:15:51 by rofernan          #+#    #+#             */
/*   Updated: 2020/02/21 18:53:09 by rofernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	**extract(char **args)
{
	int		i;
	int		j;
	char	**tmp;

	i = -1;
	j = 0;
	while (args[++i])
	{
		if (!ft_strcmp(args[i], "|"))
			break ;
		else if (i == 0 || (i > 0 && !is_chevron(args[i]) \
		&& !is_chevron(args[i - 1])))
			j++;
	}
	if (!(tmp = malloc(sizeof(char *) * (j + 1))))
		exit(EXIT_FAILURE);
	i = -1;
	j = 0;
	while (args[++i])
	{
		if (!ft_strcmp(args[i], "|"))
			break ;
		else if (i == 0 || (i > 0 && !is_chevron(args[i]) \
		&& !is_chevron(args[i - 1])))
			tmp[j++] = ft_strdup(args[i]);
	}
	tmp[j] = NULL;
	return (tmp);
}

int			del_war(char ***s, int i)
{
	del_args(s[0]);
	return (i);
}

int			is_builtin_1(t_shell *shell)
{
	char **args;

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
}

void		builtin_exec(t_shell *shell, char **args)
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
		del_args(args);
		h_split(shell, shell->next_args);
		exec_pipe(shell, i + 1);
	}
	// del_args(args); // <- fait segfaulter dans certains cas
	return (-42);
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
