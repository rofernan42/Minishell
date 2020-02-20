/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofernan <rofernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 10:49:46 by rofernan          #+#    #+#             */
/*   Updated: 2020/02/20 15:47:42 by rofernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	create_env(t_env **env, char *name, char *data)
{
	t_env *new_env;

	if (!env)
		return ;
	new_env = ft_envnew(name, data);
	ft_envadd_back(env, new_env);
}

void	init_env(t_env **env)
{
	*env = ft_envnew(0, 0);
	create_env(env, "HOME", "/Users/");
	create_env(env, "PWD", getcwd(NULL, 0));
	create_env(env, "OLDPWD", getcwd(NULL, 0));
	create_env(env, "PATH", "/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin");
	create_env(env, "?", "0");
}
