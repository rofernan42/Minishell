/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tabs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofernan <rofernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 16:05:59 by rofernan          #+#    #+#             */
/*   Updated: 2020/02/18 16:52:21 by rofernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		ft_tablength(char **s)
{
	int i;

	i = 0;
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
}
