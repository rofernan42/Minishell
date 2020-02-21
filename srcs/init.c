/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofernan <rofernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 12:24:02 by rofernan          #+#    #+#             */
/*   Updated: 2020/02/21 12:27:52 by rofernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	init_env(t_env **env)
{
	*env = ft_envnew(0, 0);
	create_env(env, "HOME", "/Users/");
	create_env(env, "PWD", getcwd(NULL, 0));
	create_env(env, "OLDPWD", getcwd(NULL, 0));
	create_env(env, "PATH", "/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin");
	create_env(env, "?", "0");
}

void	init_name_prog(t_shell *shell, char *av)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (av[i])
	{
		if (av[i] == '/')
			j = i;
		i++;
	}
	shell->name_prog = ft_strdup(&av[j + 1]);
}
