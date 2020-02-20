/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   try3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofernan <rofernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 13:14:09 by augay             #+#    #+#             */
/*   Updated: 2020/02/20 15:25:05 by rofernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int		is_in_s(char *s, int m)
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

void	is_in_sd_1(int *i, int *std, int *sts, int *state)
{
	*i = -1;
	*std = 0;
	*sts = 0;
	*state = 0;
}

int		is_in_sd_out(int state, int sts, int std, int **tab)
{
	if (state == 1)
		free(*tab);
	return (sts + std);
}

int		is_in_sd(const char *s, int m, int *tab)
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

char	*inv(char c)
{
	char *o;

	o = malloc(sizeof(char) * 2);
	o[0] = -c;
	o[1] = '\0';
	return (o);
}

void	ft_translate_1(int *i, char **out, char **s, int *tab)
{
	(*i)++;
	if (s[0][*i] == '\'')
		out[0] = ft_strjoin_free(out[0], inv('\''), 2);
	if (s[0][*i] == '>')
		out[0] = ft_strjoin_free(out[0], ">", 1);
	if (s[0][*i] == '<')
		out[0] = ft_strjoin_free(out[0], "<", 1);
	if (s[0][*i] == '|')
		out[0] = ft_strjoin_free(out[0], "|", 1);
	tab[ft_strlen(out[0]) - 1] = 1;
}

void	ft_translate_2(int *i, char **s, char **out)
{
	(*i)++;
	if (s[0][*i] == '"')
		out[0] = ft_strjoin_free(out[0], inv('"'), 2);
	else if (s[0][*i] == '\\')
		out[0] = ft_strjoin_free(out[0], "\\", 1);
	else if (s[0][*i] == '$')
		out[0] = ft_strjoin_free(out[0], "$", 1);
}

void	ft_translate(char **s, int d, char **out, int *tab)
{
	int		i;
	char	*q;

	i = d - 1;
	while (s[0][++i] && s[0][i] != '\n')
		if (is_in_s(s[0], i) == 0 && s[0][i] == '\\' && s[0][i + 1] &&
		(s[0][i + 1] == '"' || s[0][i + 1] == '\\' || s[0][i + 1] == '$'))
			ft_translate_2(&i, s, out);
		else if (is_in_sd(s[0], i, NULL) == 0 && s[0][i] == '\\' &&
		s[0][i + 1] && (s[0][i + 1] == '\'' || s[0][i + 1] == '>' ||
		s[0][i + 1] == '<' || s[0][i + 1] == '|'))
			ft_translate_1(&i, out, s, tab);
		else
		{
			q = ft_substr(s[0], i, 1);
			out[0] = ft_strjoin_free(out[0], q, 1);
			free(q);
		}
	return ;
}
