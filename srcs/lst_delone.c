/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_delone.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofernan <rofernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/11 15:08:07 by rofernan          #+#    #+#             */
/*   Updated: 2020/02/11 15:28:05 by rofernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_lstdelone(t_env *env, void (*del)(void *))
{
    if (!del)
        return ;
    if (env)
    {
        del(env->name);
		del(env->data);
    }
}
