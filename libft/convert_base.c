/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofernan <rofernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 18:11:35 by rofernan          #+#    #+#             */
/*   Updated: 2019/11/26 18:15:34 by rofernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*convert_base(char *nbr, char *base_from, char *base_to)
{
	int		nb_int;
	char	*dest;

	nb_int = ft_atoi_base(nbr, base_from);
	dest = ft_itoa_base(nb_int, base_to);
	return (dest);
}
