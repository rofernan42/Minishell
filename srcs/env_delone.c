/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_delone.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofernan <rofernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/11 15:08:07 by rofernan          #+#    #+#             */
/*   Updated: 2020/02/13 10:38:10 by rofernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_envdelone(t_env *env, void (*del)(void *))
{
    if (!del)
        return ;
    if (env)
    {
        del(env->name);
		del(env->data);
    }
}
