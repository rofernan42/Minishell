/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tabs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofernan <rofernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 16:05:59 by rofernan          #+#    #+#             */
/*   Updated: 2020/02/20 21:06:26 by rofernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		ft_tablength(char **s)
{
	int i;

	i = 0;
	if (s == NULL)
		return (0);
	while (s[i])
		i++;
	return (i);
}

char	**ft_tabcopy(char **s, int fin)
{
	int		i;
	char	**o;

	i = 0;
	while (s[i] && i < fin)
		i++;
	o = malloc(sizeof(char*) * (i + 1));
	o[i] = 0;
	i = 0;
	while (s[i] && i < fin)
	{
		o[i] = ft_strdup(s[i]);
		i++;
	}
	return (o);
}

void	del_args(char **args)
{
	int i;

	i = 0;
	while (args[i])
		ft_strdel(&args[i++]);
	ft_strdel(&args[i]);
	free(args);
	args = NULL;
}

void	h_split(t_shell *shell, char **cmd)
{
	int		fin;
	int		p;
	int		part;
	int		last_part;

	p = 0;
	part = 0;
	last_part = 0;
	fin = ft_tablength(cmd);
	while (part <= fin && p < 1)
	{
		if (part == fin || !ft_strcmp(cmd[part], "|"))
		{
			shell->args = (ft_tabcopy(cmd + last_part, part - last_part));
			last_part = part + 1;
			p++;
		}
		part++;
	}
	if (part < fin)
		shell->next_args = ft_tabcopy(cmd + last_part, fin - last_part);
	else
		shell->next_args = NULL;
}

void		ft_p(char **s)
{
	int i;

	i = 0;
	if (!s)
		return ;
	while (s[i])
	{
		printf("s[%d] = |%s|\n", i, s[i]);
		i++;
	}
}
