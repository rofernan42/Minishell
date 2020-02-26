/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofernan <rofernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 10:54:26 by rofernan          #+#    #+#             */
/*   Updated: 2020/02/24 16:56:28 by rofernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_free(char ***s)
{
	// int i;

	// i = 0;
	// if (s[0] == NULL)
	// 	return ;
	// while (s[0][i])
	// {
	// 	free(s[0][i]);
	// 	s[0][i] = NULL;
	// 	i++;
	// }
	// free(s[0][i]);
	// s[0][i] = NULL;
	// free(s[0]);
	// s[0] = NULL;
}

int		del_war(char ***s, int i)
{
	ft_free(s);
	return (i);
}

void	free_all(t_shell *shell)
{
	if (shell->args)
		ft_free(&shell->args);
	if (shell->next_args)
		ft_free(&shell->next_args);
	ft_envclear(shell->env, free);
}
