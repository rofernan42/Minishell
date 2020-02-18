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

	i = 1;
	shell->str_echo = ft_strdup("");
	while (shell->args[i])
	{
		shell->str_echo = ft_strjoin_free(shell->str_echo, shell->args[i], 1);
		if (shell->args[i + 1])
			shell->str_echo = ft_strjoin_free(shell->str_echo, " ", 1);
		i++;
	}
	ft_putendl_fd(shell->str_echo, 1);
	ft_strdel(&shell->str_echo);
}
