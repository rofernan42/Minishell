/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   try3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: augay <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 13:14:09 by augay             #+#    #+#             */
/*   Updated: 2020/02/20 13:14:10 by augay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int		contain(char *s)
{
	int i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

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

int		is_in_sd(const char *s, int m, int *tab)
{
	int i;
	int std;
	int deb;
	int sts;
	int state;

	i = 0;
	std = 0;
	sts = 0;
	state = 0;
	if (tab == NULL && (state = 1))
		tab = fill_tab(s);
	while (s[i] && i < m)
	{
		if (tab[i] == 0 && !sts && !std && s[i] == '"' &&
		nb_bs(s, i - 1) % 2 == 0)
		{
			std = 1;
			deb = i;
		}
		else if (tab[i] == 0 && !sts && std && s[i] == '"' &&
		nb_bs(s, i - 1) % 2 == 0)
			std = 0;
		else if (tab[i] == 0 && !std && !sts && s[i] == '\'' &&
		nb_bs(s, i - 1) % 2 == 0)
		{
			deb = i;
			sts = 1;
		}
		else if (tab[i] == 0 && !std && sts && s[i] == '\'' &&
		nb_bs(s, i - 1) % 2 == 0)
			sts = 0;
		i++;
	}
	if (state == 1)
		free(tab);
	return (sts + std);
}

void	ft_translate(char **s, int d, int f, char **out, int *tab)
{
	int		i;
	char	*q;
	char	*tmp;
	tmp = malloc(sizeof(char) * 2);
	i = d;
	tmp[1] = '\0';
	while (s[0][i] && s[0][i] != '\n')
	{
		if (is_in_s(s[0], i) == 0 && s[0][i] == '\\' && s[0][i + 1] && (s[0][i + 1] == '"' || s[0][i + 1] == '\\' || s[0][i + 1] == '$'))
		{
			i++;
			if (s[0][i] == '"')
			{
				tmp[0] = -1 * '"';
				out[0] = ft_concat(out[0], tmp);
			}
			else if (s[0][i] == '\\')
				out[0] = ft_concat(out[0], "\\");
			else if (s[0][i] == '$')
				out[0] = ft_concat(out[0], "$");
		}
		else if (is_in_sd(s[0], i, NULL) == 0 && s[0][i] == '\\' && s[0][i + 1] && (s[0][i + 1] == '\'' || s[0][i + 1] == '>' || s[0][i + 1] == '<' || s[0][i + 1] == '|'))
		{
			i++;
			if (s[0][i] == '\'')
			{
				tmp[0] = -1 * '\'';
				out[0] = ft_concat(out[0], tmp);
			}
			if (s[0][i] == '>')
				out[0] = ft_concat(out[0], ">");
			if (s[0][i] == '<')
				out[0] = ft_concat(out[0], "<");
			if (s[0][i] == '|')
				out[0] = ft_concat(out[0], "|");
			tab[ft_strlen(out[0]) - 1] = 1;
		}
		else
		{
			q = ft_substr(s[0], i, 1);
			out[0] = ft_concat(out[0], q);
			free(q);
		}
		i++;
	}
	free(tmp);
	return ;
}
