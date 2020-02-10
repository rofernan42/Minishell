/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofernan <rofernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/08 11:54:30 by rofernan          #+#    #+#             */
/*   Updated: 2020/01/21 12:26:58 by rofernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		check_whitespace(char c)
{
	if (c == ' ' || c == '\f' || c == '\t' || c == '\n' \
		|| c == '\r' || c == '\v')
		return (1);
	return (0);
}

static int		check_base(char *base)
{
	int i;
	int j;

	i = 0;
	j = 0;
	if (ft_strlen(base) < 2)
		return (0);
	while (base[i])
	{
		if (check_whitespace(base[i]) || base[i] == '+' || base[i] == '-')
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

static int		sign_number(char *str)
{
	int i;
	int sign;

	i = 0;
	sign = 1;
	while (str[i] && check_whitespace(str[i]))
		i++;
	if (str[i] == '-')
		sign = -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (check_whitespace(str[i]))
		return (0);
	return (sign);
}

static int		compare_base(char c, char *base)
{
	int i;

	i = 0;
	while (base[i])
	{
		if (c != base[i])
			i++;
		else
			return (i);
	}
	return (-1);
}

int				ft_atoi_base(char *str, char *base)
{
	int		i;
	int		nb;
	int		size_base;

	i = 0;
	nb = 0;
	size_base = (int)ft_strlen(base);
	if (!check_base(base))
		return (0);
	while (check_whitespace(str[i]) || str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (compare_base(str[i], base) != -1)
			nb = nb * size_base + compare_base(str[i], base);
		else
			return (sign_number(str) * nb);
		i++;
	}
	return (sign_number(str) * nb);
}
