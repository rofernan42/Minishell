/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofernan <rofernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 14:47:49 by rofernan          #+#    #+#             */
/*   Updated: 2020/02/21 15:47:56 by rofernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	is_number(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

void		ft_exit(t_shell *shell, char **args)
{
	int n;

	if (!args[1])
	{
		ft_putendl_fd("exit", 1);
		free_all(shell);
		exit(0);
	}
	if (args[1] && !args[2])
	{
		if (is_number(args[1]))
			n = ft_atoi(args[1]);
		else
			n = 255;
		ft_putendl_fd("exit", 1);
		if (n == 255)
			disp_err(shell->name_prog, \
			"exit: ", args[1], "numeric argument required");
		free_all(shell);
		exit(n);
	}
	if (args[1] && args[2])
	{
		ft_putendl_fd("exit", 1);
		disp_err(shell->name_prog, "exit: ", 0, "too many arguments");
	}
}
