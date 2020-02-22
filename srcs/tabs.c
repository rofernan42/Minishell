/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tabs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofernan <rofernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 16:05:59 by rofernan          #+#    #+#             */
/*   Updated: 2020/02/21 11:30:16 by rofernan         ###   ########.fr       */
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

int		init_split(int *p, int *part, int *last_part, char ***cmd)
{
	*p = 0;
	*part = -1;
	*last_part = 0;
	return (ft_tablength(cmd[0]));
}

void	h_split(t_shell *shell, char ***cmd)
{
	int		fin;
	int		p;
	int		part;
	int		last_part;

	fin = init_split(&p, &part, &last_part, cmd);
	while (++part <= fin && p < 1)
		if (part == fin || !ft_strcmp(cmd[0][part], "|"))
		{
			ft_free(&shell->args);
			shell->args = (ft_tabcopy(cmd[0] + last_part, part - last_part));
			last_part = part + 1;
			p++;
		}
	if (part < fin)
	{
		ft_free(&shell->next_args);
		shell->next_args = ft_tabcopy(cmd[0] + last_part, fin - last_part);
	}
	else
	{
		ft_free(&shell->next_args);
		shell->next_args = NULL;
	}
	ft_free(cmd);
}
