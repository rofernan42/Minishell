/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofernan <rofernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 12:50:36 by rofernan          #+#    #+#             */
/*   Updated: 2020/02/10 19:06:37 by rofernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

void	ft_pwd(t_env *list)
{
	ft_putstr_fd(getcwd(NULL, 0), 1);
}

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
	ft_putstr_fd(shell->str, 1);
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

int main(int ac, char **av)
{
	t_shell	shell;
	char	buffer[BUF_SIZE + 1];
	int		ret;
	int		i;

	shell.args = NULL;
	shell.command = ft_strdup("");
	ret = 0;
	ft_putstr_fd("minishell$ ", 1);
	while (1)
	{
		ret = read(0, buffer, BUF_SIZE);
		buffer[ret] = 0;
		shell.command = ft_strjoin_free(shell.command, buffer, 1);
		if (enter(shell.command))
		{
			shell.args = ft_split(shell.command, ' ');
			i = count_args(shell.args);
			if (!ft_strcmp(shell.args[0], "echo"))
				ft_echo(i, shell.args, &shell);
			if (!ft_strcmp(shell.args[0], "exit\n"))
				ret = 0;
			free(shell.command);
			shell.command = ft_strdup("");
			del_args(&shell);
			ft_putstr_fd("minishell$ ", 1);
		}
		if (ret == 0)
		{
			ft_putstr_fd("exit\n", 1);
			exit(1);
		}
	}

	return (0);
}
