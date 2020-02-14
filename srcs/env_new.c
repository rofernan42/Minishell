/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_new.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofernan <rofernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/11 15:05:58 by rofernan          #+#    #+#             */
/*   Updated: 2020/02/14 11:26:26 by rofernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_env	*ft_envnew(char *name, char *data)
{
	t_env *env;

	if (!(env = malloc(sizeof(t_env))))
		return (NULL);
	if (name)
		env->name = ft_strdup(name);
	else
		env->name = NULL;
	if (data)
		env->data = ft_strdup(data);
	else
		env->data = NULL;
	env->next = NULL;
	return (env);
}
