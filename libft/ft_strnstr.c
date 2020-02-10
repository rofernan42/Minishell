/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofernan <rofernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/05 14:40:33 by rofernan          #+#    #+#             */
/*   Updated: 2019/10/11 16:13:03 by rofernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str, const char *to_find, size_t len)
{
	size_t i;
	size_t j;

	i = 0;
	j = 0;
	if (*to_find == '\0')
		return ((char *)str);
	while (str[i] && i < len)
	{
		while (to_find[j] && to_find[j] == str[i + j] && (i + j) < len)
			j++;
		if (!to_find[j])
			return ((char *)&str[i]);
		i++;
		j = 0;
	}
	return (0);
}
