/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   match.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: augay <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/14 10:12:04 by augay             #+#    #+#             */
/*   Updated: 2018/07/14 10:17:00 by augay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int		len(char *str)
{
	int i;

	i = 0;
	while (str[i] != '\0')
	{
		i++;
	}
	return (i);
}

void	recur(char *s1, char *s2, int *nb, int i)
{
	int k;
	int y;

	y = i / 1000000;
	i = i % 1000000;
	k = 0;
	if (s2[y] == '\0' && s1[i] == '\0')
		*nb = *nb + 1;
	if (s2[y] == '*')
		while (k <= len(s1 + i))
		{
			recur(s1, s2, nb, i + k + (y + 1) * 1000000);
			k++;
		}
	if (s1[i] == '\0')
		return ;
	if (s1[i] == s2[y])
		recur(s1, s2, nb, i + 1 + (y + 1) * 1000000);
	if (s1[i] != s2[y])
		return ;
}

int		match(char *s1, char *s2)
{
	int a;
	int *nb;

	nb = &a;
	a = 0;
	recur(s1, s2, nb, 0);
	if (a > 0)
	{
		return (1);
	}
	return (0);
}
