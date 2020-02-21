/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofernan <rofernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 11:56:37 by rofernan          #+#    #+#             */
/*   Updated: 2020/02/21 12:19:44 by rofernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	check_env_name(char *name)
{
	int i;

	i = 0;
	while (name[i])
	{
		if (!ft_isalnum(name[i]) && name[i] != '_' && name[i] != '=')
			return (0);
		i++;
	}
	if (!ft_isalpha(name[0]) && name[0] != '_')
		return (0);
	return (1);
}

static int	error_name(t_shell *shell, char *var)
{
	if (!check_env_name(var))
	{
		disp_err(shell->name_prog, \
		"export: `", var, "': ", " not a valid identifier");
		return (1);
	}
	return (0);
}

static int	assign_env(t_shell *shell, char **vars, int i, int j)
{
	char	*name;
	char	*data;
	t_env	*tmp;

	name = ft_strndup(vars[i], j);
	data = ft_strdup(&vars[i][j + 1]);
	if (!(tmp = ft_envfind(shell->env, name, ft_strcmp)))
		create_env(&shell->env, name, data);
	else
	{
		ft_strdel(&tmp->data);
		tmp->data = ft_strdup(data);
	}
	ft_strdel(&name);
	ft_strdel(&data);
	return (1);
}

void		ft_export(t_shell *shell, char **vars)
{
	int		i;
	int		j;

	i = 0;
	while (vars[i])
	{
		if (!error_name(shell, vars[i]))
		{
			j = 0;
			while (vars[i][j])
			{
				if (vars[i][j] == '=')
				{
					if (!assign_env(shell, vars, i, j))
						return ;
				}
				j++;
			}
		}
		i++;
	}
}
