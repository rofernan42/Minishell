/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wrap_cmp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofernan <rofernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 10:42:31 by rofernan          #+#    #+#             */
/*   Updated: 2020/02/25 10:42:45 by rofernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int			wrap_cmp(char *s, char c)
{
	char	*s2;
	int		i;

	s2 = inv(c);
	i = ft_strcmp(s, s2);
	free(s2);
	return (i);
}

int			wrap_cmp_2(char *s, char *c)
{
	char	*s2;
	int		i;

	s2 = malloc(sizeof(char) * 3);
	s2[0] = -1 * c[0];
	s2[1] = -1 * c[1];
	s2[2] = '\0';
	i = ft_strcmp(s, s2);
	free(s2);
	return (i);
}
