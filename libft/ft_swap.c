/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_swap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofernan <rofernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/02 12:19:51 by rofernan          #+#    #+#             */
/*   Updated: 2020/01/02 12:29:33 by rofernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	ft_swap_int(int *a, int *b)
{
	int temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

void	ft_swap_dbl(double *a, double *b)
{
	double temp;

	temp = *a;
	*a = *b;
	*b = temp;
}
