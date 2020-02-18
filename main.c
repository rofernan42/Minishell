/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofernan <rofernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 12:50:36 by rofernan          #+#    #+#             */
/*   Updated: 2020/02/18 11:02:42 by rofernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

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

	init_env(&shell.env);
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
			ft_stdin(&shell);
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
