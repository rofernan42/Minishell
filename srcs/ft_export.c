/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofernan <rofernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 11:56:37 by rofernan          #+#    #+#             */
/*   Updated: 2020/02/18 13:20:56 by rofernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	error_name(char *var, char **name)
{
	if (!check_env_name(*name))
	{
		disp_err("export: ", var, ": ", " not a valid identifier");
		ft_strdel(name);
		return (1);
	}
	return (0);
}

static int	assign_env(char **vars, t_env *env, int i, int j)
{
	char	*name;
	char	*data;
	t_env	*tmp;

	name = ft_strndup(vars[i], j);
	if (error_name(vars[i], &name))
		return (0);
	data = ft_strdup(&vars[i][j + 1]);
	if (!(tmp = ft_envfind(env, name, ft_strcmp)))
		create_env(&env, name, data);
	else
	{
		ft_strdel(&tmp->data);
		tmp->data = ft_strdup(data);
	}
	ft_strdel(&name);
	ft_strdel(&data);
	return (1);
}

void		ft_export(char **vars, t_env *env)
{
	int		i;
	int		j;
	char	*name;
	char	*data;
	t_env	*tmp;

	i = 0;
	while (vars[i])
	{
		j = 0;
		while (vars[i][j])
		{
			if (vars[i][j] == '=')
			{
				if (!assign_env(vars, env, i, j))
					return ;
			}
			j++;
		}
		i++;
	}
}
