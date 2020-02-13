/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_find.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofernan <rofernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/11 15:20:36 by rofernan          #+#    #+#             */
/*   Updated: 2020/02/13 17:24:59 by rofernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_env	*ft_envfind(t_env *env, void *name_ref, int (*cmp)())
{
	t_env *tmp;

	tmp = env;
	while (tmp != 0)
	{
		if (tmp->name)
		{
			if ((*cmp)(tmp->name, name_ref) == 0)
				return (tmp);
		}
		tmp = tmp->next;
	}
	return (NULL);
}
