/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofernan <rofernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 10:49:46 by rofernan          #+#    #+#             */
/*   Updated: 2020/02/13 10:50:42 by rofernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	create_env(t_env **env, char *name, char *data)
{
	t_env *new_env;

    if (!env)
        return ;
	new_env = ft_envnew(name , data);
	ft_envaddback(env, new_env);
}
