/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofernan <rofernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 16:58:29 by rofernan          #+#    #+#             */
/*   Updated: 2020/02/17 17:02:10 by rofernan         ###   ########.fr       */
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
		shell->str_echo = ft_strjoin_free(shell->str_echo, shell->args[1], 1);
		if (shell->args[i + 1])
			shell->str_echo = ft_strjoin_free(shell->str_echo, " ", 1);
		i++;
	}
	ft_putendl_fd(shell->str_echo, 1);
}
