/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofernan <rofernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 17:42:24 by rofernan          #+#    #+#             */
/*   Updated: 2019/10/09 16:33:33 by rofernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void			ft_putnbr_fd(int n, int fd)
{
	unsigned int temp;

	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		temp = -n;
	}
	else
		temp = n;
	if (temp < 10)
		ft_putchar_fd(temp + '0', fd);
	else
	{
		ft_putnbr_fd(temp / 10, fd);
		ft_putchar_fd(temp % 10 + '0', fd);
	}
}
