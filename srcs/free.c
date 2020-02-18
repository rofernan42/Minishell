/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofernan <rofernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 10:54:26 by rofernan          #+#    #+#             */
/*   Updated: 2020/02/18 13:33:30 by rofernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	del_args(char **args)
{
	int i;

	i = 0;
	while (args[i])
		ft_strdel(&args[i++]);
	ft_strdel(&args[i]);
	free(args);
}

void	free_all(t_shell *shell)
{
	del_args(shell->args);
	ft_envclear(shell->env, free);
}
