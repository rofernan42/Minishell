/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofernan <rofernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 10:54:26 by rofernan          #+#    #+#             */
/*   Updated: 2020/02/20 15:41:48 by rofernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_all(t_shell *shell)
{
	if (shell->args)
		del_args(shell->args);
	if (shell->next_args)
		del_args(shell->next_args);
	ft_envclear(shell->env, free);
}
