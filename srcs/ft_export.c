/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofernan <rofernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 11:56:37 by rofernan          #+#    #+#             */
/*   Updated: 2020/02/13 14:26:45 by rofernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	check_env_name(char *name)
{
	int i;

	i = 0;
	while (name[i])
	{
		if (!ft_isalnum(name[i]) && name[i] != '_')
			return (0);
		i++;
	}
	if (!ft_isalpha(name[0]) && name[0] != '_')
		return (0);
	return (1);
}

void		ft_export(char **vars, t_env *env)
{
	int		i;
	int		j;
	char	*name;
	char	*data;

	i = 0;
	while (vars[i])
	{
		j = 0;
		while (vars[i][j])
		{
			if (vars[i][j] == '=')
			{
				name = ft_strndup(vars[i], j);
				if (!check_env_name(name))
				{
					display_error("export: ", vars[i], \
								" not a valid identifier");
					ft_strdel(&name);
					return ;
				}
				data = ft_strdup(&vars[i][j + 1]);
				create_env(&env, name, data);
			}
			j++;
		}
		i++;
	}
}
