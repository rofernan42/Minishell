/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofernan <rofernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 14:47:49 by rofernan          #+#    #+#             */
/*   Updated: 2020/02/21 19:09:13 by rofernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	is_number(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if ((i == 0 && (str[i] != '-' && !ft_isdigit(str[i]))) \
		|| (i > 0 && !ft_isdigit(str[i])))
			return (0);
		i++;
	}
	return (1);
}

void		ft_exit(t_shell *shell, char **args)
{
	unsigned char n;

	ft_putendl_fd("exit", 1);
	if (!args[1])
	{
		free_all(shell);
		exit(0);
	}
	else if (args[1])
	{
		if (is_number(args[1]) && args[2])
		{
			disp_err(shell->name_prog, "exit: ", 0, "too many arguments");
			return ;
		}
		n = (is_number(args[1])) ? ft_atoi(args[1]) : 255;
		if (!is_number(args[1]))
			disp_err(shell->name_prog, \
			"exit: ", args[1], "numeric argument required");
		free_all(shell);
		exit(n);
	}
}
