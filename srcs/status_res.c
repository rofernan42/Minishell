/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status_res.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofernan <rofernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 10:22:34 by rofernan          #+#    #+#             */
/*   Updated: 2020/02/27 10:23:29 by rofernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	status_res(t_shell *shell, int status)
{
	t_env *tmp;

	tmp = ft_envfind(shell->env, "?", ft_strcmp);
	ft_strdel(&tmp->data);
	if (status == -42)
		status = 0;
	tmp->data = ft_itoa(status);
}
