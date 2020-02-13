/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofernan <rofernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 13:06:51 by rofernan          #+#    #+#             */
/*   Updated: 2020/02/13 13:14:27 by rofernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_env(t_env *env)
{
	t_env *tmp;

	tmp = env;
	while (tmp)
	{
		ft_putstr_fd(tmp->name, 1);
		ft_putstr_fd("=", 1);
		ft_putendl_fd(tmp->data, 1);
		tmp = tmp->next;
	}
}
