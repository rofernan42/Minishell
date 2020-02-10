/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofernan <rofernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 16:21:50 by rofernan          #+#    #+#             */
/*   Updated: 2019/11/26 17:24:03 by rofernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	check_base(char *base)
{
	int i;
	int j;

	i = 0;
	j = 0;
	if (ft_strlen(base) < 2)
		return (0);
	while (base[i])
	{
		if (base[i] == ' ' || base[i] == '\f' || base[i] == '\t'
				|| base[i] == '\n' || base[i] == '\r' || base[i] == '\v'
				|| base[i] == '+' || base[i] == '-')
			return (0);
		while (base[j])
		{
			if (base[i] == base[j] && i != j)
				return (0);
			j++;
		}
		j = 0;
		i++;
	}
	return (1);
}

char		*ft_itoa_base(unsigned int nbr, char *base)
{
	char			*str_nbr;
	int				size_dest;
	unsigned int	tmp;
	size_t			size_base;

	size_dest = 1;
	tmp = nbr;
	size_base = ft_strlen(base);
	if (!check_base(base))
		return (NULL);
	while ((tmp / size_base) > 0)
	{
		tmp = tmp / size_base;
		size_dest++;
	}
	if (!(str_nbr = malloc(sizeof(char) * (size_dest + 1))))
		return (NULL);
	str_nbr[size_dest] = '\0';
	while (size_dest > 0)
	{
		str_nbr[size_dest - 1] = base[nbr % size_base];
		nbr = nbr / size_base;
		size_dest--;
	}
	return (str_nbr);
}
