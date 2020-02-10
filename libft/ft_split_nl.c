/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_nl.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofernan <rofernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 17:55:58 by rofernan          #+#    #+#             */
/*   Updated: 2020/01/07 16:28:35 by rofernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	check_c(char to_check)
{
	if (to_check == '\n')
		return (1);
	return (0);
}

static int	nb_blocks(char const *s)
{
	int nb;
	int i;

	nb = 0;
	i = 0;
	while (s[i])
	{
		if ((i == 0 && !check_c(s[0]))
		|| (i > 0 && check_c(s[i - 1]) && !check_c(s[i]))
		|| (i > 0 && check_c(s[i - 1]) && check_c(s[i])))
			nb++;
		i++;
	}
	return (nb);
}

static int	*size_blocks(char const *s, int nb)
{
	int *tab;
	int i;
	int j;

	i = 0;
	j = 0;
	if (!(tab = malloc(sizeof(*tab) * nb)))
		return (NULL);
	while (i < nb)
		tab[i++] = 0;
	i = 0;
	while (s[i])
	{
		if (!check_c(s[i]))
			tab[j]++;
		else if (i > 0 \
			&& (!check_c(s[i - 1]) || (check_c(s[i - 1]) && check_c(s[i]))))
			j++;
		i++;
	}
	return (tab);
}

static char	**fill_dest(char const *s, int nb, int *tab)
{
	int		i;
	int		j;
	int		k;
	char	**dest;

	if (!(dest = malloc(sizeof(dest) * (nb + 1))))
		return (NULL);
	i = 0;
	j = 0;
	while (j < nb)
	{
		k = 0;
		while (check_c(s[i]))
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

char		**ft_split_nl(char const *s)
{
	int		nb;
	int		*tab;

	nb = nb_blocks(s);
	if (!s || !(tab = size_blocks(s, nb)))
		return (NULL);
	return (fill_dest(s, nb, tab));
}
