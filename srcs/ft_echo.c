/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofernan <rofernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 16:58:29 by rofernan          #+#    #+#             */
/*   Updated: 2020/02/20 12:46:04 by rofernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_echo(char **args)
{
	int i;
	int o;

	o = 0;
	i = 1;
	if (!ft_strcmp(args[1], "-n"))
	{
		i++;
		o = 1;
	}
	while (args[i])
	{
		if (!((o == 0 && i == 1) || (o == 1 && i == 2)))
			write(1, " ", 1);
		ft_putstr_fd(args[i], 1);
		i++;
	}
	if (o == 0)
		write(1, "\n", 1);
}
