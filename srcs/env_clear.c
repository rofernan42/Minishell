/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_clear.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofernan <rofernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 16:02:51 by rofernan          #+#    #+#             */
/*   Updated: 2020/02/13 17:38:06 by rofernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_env_clear(t_env *begin_env, void (*free_fct)(void *))
{
	t_env *env;
	t_env *tmp;

	env = begin_env;
	while (env != NULL)
	{
		tmp = env->next;
		free_fct(env->name);
		free_fct(env->data);
		free(env);
		env = tmp;
	}
}
