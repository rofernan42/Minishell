/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofernan <rofernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 17:01:28 by rofernan          #+#    #+#             */
/*   Updated: 2019/10/11 12:06:34 by rofernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char *temp1;
	unsigned char *temp2;

	temp1 = (unsigned char *)s1;
	temp2 = (unsigned char *)s2;
	if (!n)
		return (0);
	while (*temp1 == *temp2 && n > 1)
	{
		temp1++;
		temp2++;
		n--;
	}
	return (*temp1 - *temp2);
}
