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

void	init_env(t_env **env, char **s)
{
	int		i;
	int		j;
	int		k;
	char	*n;
	char	*d;

	*env = ft_envnew(0, 0);
	create_env(env, "?", "0");
	if (!(i = 0) && s == NULL)
		return ;
	while (s[i] && s[i + 1])
	{
		k = 0;
		j = 0;
		while (s[i][j] && s[i][j] != '=')
			j++;
		while (s[i][j + k])
			k++;
		d = ft_substr(s[i], j + 1, k);
		n = ft_substr(s[i], 0, j);
		create_env(env, n, d);
		free(d);
		free(n);
		i++;
	}
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
