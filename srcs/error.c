/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofernan <rofernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 14:11:14 by rofernan          #+#    #+#             */
/*   Updated: 2020/02/25 10:26:42 by rofernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	disp_err(char *prog, char *cmd, char *arg, char *err)
{
	ft_putstr_fd(prog, 2);
	if (prog)
		ft_putstr_fd(": ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(arg, 2);
	if (arg)
		ft_putstr_fd(": ", 2);
	ft_putendl_fd(err, 2);
}

int		chevron_error(char *prog, char *arg, char *cmd, char *end)
{
	ft_putstr_fd(prog, 2);
	if (prog)
		ft_putstr_fd(": ", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd(cmd, 2);
	ft_putendl_fd(end, 2);
	return (258);
}

void	command_error(char *command, char *err)
{
	ft_putstr_fd(command, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(err, 2);
}
