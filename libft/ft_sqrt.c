/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sqrt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofernan <rofernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/08 19:56:22 by rofernan          #+#    #+#             */
/*   Updated: 2020/01/02 11:41:34 by rofernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

double	ft_sqrt(double nb)
{
	int sqrt;

	sqrt = 0;
	if (nb > 2147395600)
		return (0);
	while (sqrt * sqrt <= nb)
	{
		if (sqrt * sqrt == nb)
			return (sqrt);
		sqrt++;
	}
	return (0);
}
