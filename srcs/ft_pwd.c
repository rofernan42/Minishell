/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofernan <rofernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 11:40:09 by rofernan          #+#    #+#             */
/*   Updated: 2020/02/13 11:40:23 by rofernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_pwd(t_env *env)
{
	t_env *tmp;

	tmp = ft_envfind(env, "PWD", ft_strcmp);
	ft_putendl_fd(tmp->data, 1);
}
