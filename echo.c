/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofernan <rofernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 12:50:36 by rofernan          #+#    #+#             */
/*   Updated: 2020/02/17 15:52:30 by rofernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

void	ft_echo(int ac, char **av, t_shell *shell)
{
	int i;

	i = 1;
	shell->str = ft_strdup("");
	while (i < ac)
	{
		shell->str = ft_strjoin_free(shell->str, av[i], 1);
		if (i < ac - 1)
			shell->str = ft_strjoin_free(shell->str, " ", 1);
		i++;
	}
	ft_putendl_fd(shell->str, 1);
}

int		enter(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

int		count_args(char **args)
{
	int i;

	i = 0;
	while (args[i])
		i++;
	return (i);
}

void	del_args(t_shell *shell)
{
	int i;

	i = 0;
	while (shell->args[i])
		ft_strdel(&shell->args[i++]);
	ft_strdel(&shell->args[i]);
	free(shell->args);
	shell->args = NULL;
}

void	layout_args(t_shell *shell)
{
	int i;
	int j;

	i = 0;
	while (shell->args[i])
	{
		j = 0;
		while (shell->args[i][j])
		{
			if (shell->args[i][j] == '\n')
			{
				shell->args[i][j] = '\0';
				break ;
			}
			j++;
		}
		i++;
	}
}

void	init_env(t_env **env)
{
	char *name;
	char *data;

	*env = ft_envnew(0, 0);
	create_env(env, "HOME", "/Users/rofernan");
	create_env(env, "PWD", getcwd(NULL, 0));
	create_env(env, "OLDPWD", getcwd(NULL, 0));
}

int main(int ac, char **av, char **envp)
{
	t_shell	shell;
	char	buffer[BUF_SIZE + 1];
	int		ret;
	int		i;
	t_env	*env;

	init_env(&env);
	shell.args = NULL;
	shell.command = ft_strdup("");
	ret = 0;
	ft_putstr_fd("\033[33mminishell$\033[0m ", 1);
	while (1)
	{
		ret = read(0, buffer, BUF_SIZE);
		buffer[ret] = 0;
		shell.command = ft_strjoin_free(shell.command, buffer, 1);
		if (enter(shell.command))
		{
			shell.args = ft_split(shell.command, ' ');
			shell.args[0] = ft_strlow(shell.args[0]);
			layout_args(&shell);
			i = count_args(shell.args);
			open_fd(&shell);

			shell.stdout_cpy = dup(1);
			close(1);
			dup2(shell.fd, 1);
			if (!ft_strcmp(shell.args[0], "echo"))
				ft_echo(i, shell.args, &shell);
			else if (!ft_strncmp(shell.args[0], "cd", 2))
				ft_cd(shell.args[1], env);
			else if (!ft_strcmp(shell.args[0], "pwd"))
				ft_pwd(env);
			else if (!ft_strcmp(shell.args[0], "export"))
				ft_export(&shell.args[1], env);
			else if (!ft_strcmp(shell.args[0], "unset"))
				ft_unset(&shell.args[1], env);
			else if (!ft_strcmp(shell.args[0], "env"))
				ft_env(env);
			else if (!ft_strcmp(shell.args[0], "exit"))
				ret = 0;
			else
			{
				if (fork() == 0)
					execve(shell.args[0], shell.args, envp);
				else
					wait(NULL);
			}
			close(shell.fd);
			dup2(shell.stdout_cpy, 1);
			close(shell.stdout_cpy);
			
			free(shell.command);
			shell.command = ft_strdup("");
			del_args(&shell);
			ft_putstr_fd("\033[33mminishell$\033[0m ", 1);
		}
		if (ret == 0)
		{
			ft_putendl_fd("exit", 1);
			system("leaks a.out");
			exit(1);
		}
	}
	return (0);
}
