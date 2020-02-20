/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofernan <rofernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 11:39:11 by rofernan          #+#    #+#             */
/*   Updated: 2020/02/18 12:57:30 by rofernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	env_pwd(t_env *env)
{
	t_env *new_tmp;
	t_env *old_tmp;

	if (!(new_tmp = ft_envfind(env, "PWD", ft_strcmp)))
		return ;
	if (!(old_tmp = ft_envfind(env, "OLDPWD", ft_strcmp)))
		return ;
	free(old_tmp->data);
	old_tmp->data = ft_strdup(new_tmp->data);
	free(new_tmp->data);
	new_tmp->data = getcwd(NULL, 0);
}

void		ft_cd(char *arg, t_env *env)
{
	t_env	*tmp;

	if (!arg)
	{
		if (!(tmp = ft_envfind(env, "HOME", ft_strcmp)))
		{
			ft_putendl_fd("cd: HOME not set", 2);
			return ;
		}
		else
			arg = ft_strdup(tmp->data);
	}
	if (chdir(arg) == -1)
		disp_err("cd: ", arg, ": ", strerror(errno));
	else
		env_pwd(env);
}
