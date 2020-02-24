/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   try8.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofernan <rofernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 13:17:27 by augay             #+#    #+#             */
/*   Updated: 2020/02/20 15:24:59 by rofernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int		*fill_tab(const char *s)
{
	int l;
	int *o;
	int i;

	l = ft_strlen(s);
	o = malloc(sizeof(int) * (l));
	i = 0;
	while (i < l)
	{
		o[i] = 0;
		if (s[i] < 0)
			o[i] = 1;
		i++;
	}
	return (o);
}

int		**fill_tabf(char **s)
{
	int i;
	int j;
	int **o;

	i = 0;
	j = 0;
	while (s[i])
		i++;
	o = malloc(sizeof(int*) * (i + 1));
	o[i] = NULL;
	i = 0;
	while (s[i])
	{
		while (s[i][j])
			j++;
		o[i] = malloc(sizeof(int) * j);
		ft_memset(o[i], 0, sizeof(int) * j);
		i++;
		j = 0;
	}
	return (o);
}
