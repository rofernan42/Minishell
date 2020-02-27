/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conditions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: augay <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 11:53:20 by augay             #+#    #+#             */
/*   Updated: 2020/02/27 11:53:21 by augay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int			condition_1(char const *s, int i, int *tab)
{
	return (((s[i] && (s[i] != ' ' || nb_bs(s, i - 1) % 2 == 1)) \
		|| is_in_sd(s, i, tab) == 1));
}

int			condition_2(char const *s, int i, int *tab)
{
	return ((i == 0 || ((s[i] == ' ' && nb_bs(s, i - 1) % 2 == 0) \
		&& is_in_sd(s, i, tab) == 0)));
}

int			condition_3(char const *s, int i, int j, int *tab)
{
	return (s[i + 1 + j] && ((s[i + 1 + j] != ' ' \
				|| (nb_bs(s, i + j) % 2 == 1 && s[i + 1 + j] == ' ')) \
				|| is_in_sd(s, i + 1 + j, tab) > 0));
}
