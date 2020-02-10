/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_factorial.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofernan <rofernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/08 17:35:26 by rofernan          #+#    #+#             */
/*   Updated: 2020/01/02 11:47:54 by rofernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_factorial(int nb)
{
	int fact;

	if (nb < 0)
		return (0);
	if (nb == 0)
		return (1);
	fact = nb * ft_factorial(nb - 1);
	return (fact);
}
