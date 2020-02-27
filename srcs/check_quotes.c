/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofernan <rofernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 13:14:09 by augay             #+#    #+#             */
/*   Updated: 2020/02/24 16:36:47 by rofernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int			is_in_s(char *s, int m)
{
	int i;
	int std;
	int deb;
	int sts;

	i = -1;
	std = 0;
	sts = 0;
	while (s[++i] && i < m)
		if (!sts && !std && s[i] == '"' && nb_bs(s, i - 1) % 2 == 0)
		{
			std = 1;
			deb = i;
		}
		else if (!sts && std && s[i] == '"' && nb_bs(s, i - 1) % 2 == 0)
			std = 0;
		else if (!std && !sts && s[i] == '\'' && nb_bs(s, i - 1) % 2 == 0)
		{
			deb = i;
			sts = 1;
		}
		else if (!std && sts && s[i] == '\'' && nb_bs(s, i - 1) % 2 == 0)
			sts = 0;
	return (sts);
}

static void	is_in_sd_1(int *i, int *std, int *sts, int *state)
{
	*i = -1;
	*std = 0;
	*sts = 0;
	*state = 0;
}

static int	is_in_sd_out(int state, int sts, int std, int **tab)
{
	if (state == 1)
		free(*tab);
	return (sts + std);
}

int			is_in_sd(const char *s, int m, int *tab)
{
	int i;
	int std;
	int deb;
	int sts;
	int state;

	is_in_sd_1(&i, &std, &sts, &state);
	if (tab == NULL && (state = 1))
		tab = fill_tab(s);
	while (s[++i] && i < m)
		if ((tab[i] == 0 && !sts && !std && s[i] == '"' &&
			nb_bs(s, i - 1) % 2 == 0) &&
			(std = 1))
			deb = i;
		else if (tab[i] == 0 && !sts && std && s[i] == '"' &&
				nb_bs(s, i - 1) % 2 == 0)
			std = 0;
		else if ((tab[i] == 0 && !std && !sts && s[i] == '\'' &&
				nb_bs(s, i - 1) % 2 == 0) &&
				(sts = 1))
			deb = i;
		else if (tab[i] == 0 && !std && sts && s[i] == '\'' &&
				nb_bs(s, i - 1) % 2 == 0)
			sts = 0;
	return (is_in_sd_out(state, sts, std, &tab));
}

char		*inv(char c)
{
	char *o;

	o = malloc(sizeof(char) * 2);
	if (o == NULL)
		exit(1);
	o[0] = -c;
	o[1] = '\0';
	return (o);
}
