/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofernan <rofernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 16:58:29 by rofernan          #+#    #+#             */
/*   Updated: 2020/02/18 17:14:55 by rofernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_echo(t_shell *shell)
{
	int i;
	int o;

	o = 0;
	i = 1;
	if (!ft_strcmp(shell->args[1], "-n"))
	{
		i++;
		o = 1;
	}
	while (shell->args[i])
	{
		if (!((o == 0 && i == 1) || (o == 1 && i == 2)))
			write(1, " ", 1);
		ft_putstr_fd(shell->args[i], 1);
		i++;
	}
	if (o == 0)
	{
		write(1, "\n", 1);
	}
}
