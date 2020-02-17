/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofernan <rofernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 14:11:14 by rofernan          #+#    #+#             */
/*   Updated: 2020/02/17 11:03:33 by rofernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	display_error(char *command, char *arg, char *compl, char *err)
{
	ft_putstr_fd(command, 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd(compl, 2);
	ft_putendl_fd(err, 2);
}

void	command_error(char *command, char *err)
{
	ft_putstr_fd(command, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(err, 2);
}
