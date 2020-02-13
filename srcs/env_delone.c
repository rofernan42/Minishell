/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_delone.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofernan <rofernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/11 15:08:07 by rofernan          #+#    #+#             */
/*   Updated: 2020/02/13 15:03:27 by rofernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_envdelone(t_env *env)
{
    if (env)
    {
        ft_strdel(&env->name);
		ft_strdel(&env->data);
        free(env);
    }
}
