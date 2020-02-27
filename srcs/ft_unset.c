/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofernan <rofernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 14:27:45 by rofernan          #+#    #+#             */
/*   Updated: 2020/02/27 11:35:23 by rofernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		ft_unset(char **vars, t_env *env)
{
	int		i;
	t_env	*tmp;
	t_env	*tmp2;

	i = 0;
	while (vars[i])
	{
		tmp = env;
		while (tmp->next)
		{
			tmp2 = tmp->next;
			if (!ft_strcmp(vars[i], tmp2->name) && ft_strcmp(tmp2->name, "?"))
			{
				tmp->next = tmp2->next;
				ft_envdelone(tmp2);
				break ;
			}
			tmp = tmp->next;
		}
		i++;
	}
	return (0);
}
