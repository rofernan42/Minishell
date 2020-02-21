/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofernan <rofernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 11:39:11 by rofernan          #+#    #+#             */
/*   Updated: 2020/02/21 12:36:09 by rofernan         ###   ########.fr       */
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

void		ft_cd(t_shell *shell, char *arg)
{
	t_env	*tmp;

	if (!arg)
	{
		if (!(tmp = ft_envfind(shell->env, "HOME", ft_strcmp)))
		{
			disp_err(shell->name_prog, "cd: ", 0, "HOME not set");
			return ;
		}
		else
			arg = ft_strdup(tmp->data);
	}
	if (chdir(arg) == -1)
		disp_err(shell->name_prog, "cd: ", arg, strerror(errno));
	else
		env_pwd(shell->env);
}
