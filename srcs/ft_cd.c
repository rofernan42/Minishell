/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofernan <rofernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 11:39:11 by rofernan          #+#    #+#             */
/*   Updated: 2020/02/13 11:40:43 by rofernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	env_pwd(t_env *env)
{
	t_env *new_tmp;
	t_env *old_tmp;

	new_tmp = ft_envfind(env, "PWD", ft_strcmp);
	old_tmp = ft_envfind(env, "OLDPWD", ft_strcmp);
	free(old_tmp->data);
	old_tmp->data = ft_strdup(new_tmp->data);
	free(new_tmp->data);
	new_tmp->data = getcwd(NULL, 0);
}

void		ft_cd(char *arg, t_env *env)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (arg[i] == '\n')
		{
			arg[i] = '\0';
			break ;
		}
		i++;
	}
	if (chdir(arg) == -1)
	{
		ft_putstr_fd("cd: ", 2);
		ft_putstr_fd(arg, 2);
		ft_putstr_fd(": ", 2);
		ft_putendl_fd(strerror(errno), 2);
	}
	else
		env_pwd(env);
}
