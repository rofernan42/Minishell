/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofernan <rofernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 13:14:04 by augay             #+#    #+#             */
/*   Updated: 2020/02/24 11:31:46 by rofernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int			quote(char *s, char **out, int *tab)
{
	int i;
	int std;
	int sts;

	i = 0;
	std = 0;
	sts = 0;
	sts = is_in_sd(s, ft_strlen(s), tab);
	ft_translate(&s, i, out, tab);
	return (0);
}

void		parsing(char *s, char **out, int *tab)
{
	quote(s, out, tab);
}

char		**splitbody(int nbc, char const *s, char **out, int *tab)
{
	int i;
	int j;
	int k;

	i = 0;
	if (!(k = 0) && s[0] != ' ')
	{
		while (((s[i] && (s[i] != ' ' || nb_bs(s, i-1) % 2 == 1)) || is_in_sd(s, i, tab) == 1))
			i++;
		out[k++] = ft_substr(s, 0, i);
	}
	while (s[i] && k < nbc && !(j = 0))
	{
		if ((i == 0 || ((s[i] == ' ' && nb_bs(s, i - 1) % 2 == 0) && is_in_sd(s, i, tab) == 0)))
			if (s[i + 1] != s[i])
			{
				while (s[i + 1 + j] && ((s[i + 1 + j] != ' ' || (nb_bs(s, i+j) %2 == 1 && s[i+1+j] == ' ') ) ||
				is_in_sd(s, i + 1 + j, tab) > 0))
					j++;
				out[k] = ft_substr(s, i + 1, j);
				k++;
			}
		i++;
	}
	return (out);
}

char		**split_cmd(char *s, int *tab)
{
	int		i;
	int		nbc;
	char	**out;

	if (s == NULL)
		return (NULL);
	i = 0;
	nbc = 0;
	if (s[0] && s[0] != ' ')
		nbc++;
	while (s[i] && s[i + 1])
	{
		if ((s[i] == ' ' && s[i + 1] != ' ') && is_in_sd(s, i, tab) == 0 && nb_bs(s, i-1) % 2 != 1)
			nbc++;
		i++;
	}
	out = malloc(sizeof(char *) * (nbc + 1));
	out[nbc] = 0;
	i = 0;
	out = splitbody(nbc, s, out, tab);
	return (out);
}

int			end_name(char c, int i)
{
	if (i == 0)
	{
		if (ft_isalpha(c) || c == '?')
			return (1);
	}
	if (ft_isalnum(c) || c == '_' || c == '?')
		return (1);
	return (0);
}
