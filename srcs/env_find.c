/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_find.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofernan <rofernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/11 15:20:36 by rofernan          #+#    #+#             */
/*   Updated: 2020/02/13 10:38:26 by rofernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_env	*ft_envfind(t_env *begin_list, void *name_ref, int (*cmp)())
{
	t_env *env;

	env = begin_list;
	while (env != 0)
	{
		if ((*cmp)(env->name, name_ref) == 0)
			return (env);
		env = env->next;
	}
	return (NULL);
}
