/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofernan <rofernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 10:44:25 by augay             #+#    #+#             */
/*   Updated: 2020/02/26 13:00:46 by rofernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		p(char **cmd, int *i)
{
	if (cmd[i[0]][i[1]] != '|')
		return (1);
	return (0);
}

void	sig_handle_b(int s)
{
	(void)s;
}

int		nb_bs(const char *s, int f)
{
	int i;

	i = f;
	while (f >= 0 && s[f] && s[f] == '\\')
		f--;
	return (i - f);
}
