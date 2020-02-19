/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stdin.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofernan <rofernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 16:44:54 by rofernan          #+#    #+#             */
/*   Updated: 2020/02/19 18:05:36 by rofernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char **extract(t_shell *shell)
{
	int i;
	int j;
	char **tmp;

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

static int is_builtin(t_shell *shell)
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
		// exit(0);
	}
	else
		return (0);
	return (1);
}

static void process_exec(t_shell *shell)
{
	char **tmp;

	tmp = extract(shell);
	execve(shell->args[0], tmp, 0);
}

void h_split(t_shell *shell, char **cmd)
{
	int fin;
	char ***h = malloc(sizeof(char **) * 2);
	int p = 0;
	int part = 0;
	int last_part = 0;

	fin = ft_tablength(cmd);
	while (part <= fin && p < 1)
	{
		if (part == fin || !strcmp(cmd[part], "|"))
		{
			h[0] = (ft_tabcopy(cmd + last_part, part - last_part));
			last_part = part + 1;
			p++;
		}
		part++;
	}
	if (part < fin)
		h[1] = ft_tabcopy(cmd + last_part, fin - last_part);
	shell->args = h[0];
	if (part < fin)
		shell->next_args = h[1];
	else
		shell->next_args = NULL;
}

int execute_cmd(char **cmd, t_shell *shell)
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

void exec_pipe(t_shell *shell)
{
	int		pdes[2];
	int		status;
	pid_t	child_right;
	pid_t	child_left;

	pipe(pdes);
	if (shell->next_args == NULL && shell->args != NULL)
	{
		shell->next_args = shell->args;
		shell->args = NULL;
	}
	if (shell->args != NULL && !(child_left = fork()))
	{
		close(pdes[0]);
		dup2(pdes[1], 1);
		exit(execute_cmd(shell->args, shell));
		exit(0);
	}
	if (!(child_right = fork()))
	{
		close(pdes[1]);
		dup2(pdes[0], 0);
		if (reste_arg(shell->next_args, "|"))
		{
			h_split(shell, shell->next_args);
			exec_pipe(shell);
		}
		else if(shell->next_args != NULL)
			exit(execute_cmd(shell->next_args, shell));
		exit(0);
	}
	close(pdes[1]);
	close(pdes[0]);
	wait(NULL);
	waitpid(child_right, &status, 0);
}

void		ft_stdin(t_shell *shell, char **command)
{
	h_split(shell, command);
	exec_pipe(shell);
}
