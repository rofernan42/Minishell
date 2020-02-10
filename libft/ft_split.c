/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofernan <rofernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 17:55:58 by rofernan          #+#    #+#             */
/*   Updated: 2019/11/22 14:32:56 by rofernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int		check_c(char to_check, char c)
{
	if (to_check == c)
		return (1);
	return (0);
}

static	int		nb_blocks(char const *s, char c)
{
	int nb;
	int i;

	nb = 0;
	i = 0;
	while (s[i])
	{
		if ((i == 0 && !check_c(s[0], c))
		|| (i > 0 && check_c(s[i - 1], c) && !check_c(s[i], c)))
			nb++;
		i++;
	}
	return (nb);
}

static	int		*size_blocks(char const *s, char c)
{
	int *tab;
	int i;
	int j;

	i = 0;
	j = 0;
	if (!(tab = malloc(sizeof(*tab) * (nb_blocks(s, c)))))
		return (NULL);
	while (i < nb_blocks(s, c))
		tab[i++] = 0;
	i = 0;
	while (s[i])
	{
		if (!check_c(s[i], c))
			tab[j]++;
		else if (i > 0 && !check_c(s[i - 1], c))
			j++;
		i++;
	}
	return (tab);
}

char			**ft_split(char const *s, char c)
{
	int		i;
	int		j;
	int		k;
	int		*tab;
	char	**dest;

	i = 0;
	j = 0;
	if (!s || !(dest = malloc(sizeof(dest) * (nb_blocks(s, c) + 1))) \
	|| !(tab = size_blocks(s, c)))
		return (NULL);
	while (j < nb_blocks(s, c))
	{
		k = 0;
		while (check_c(s[i], c))
			i++;
		if (!(dest[j] = malloc(sizeof(*dest) * (tab[j] + 1))))
			return (NULL);
		while (k < tab[j])
			dest[j][k++] = s[i++];
		dest[j++][k] = '\0';
	}
	dest[j] = NULL;
	free(tab);
	return (dest);
}
