/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofernan <rofernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 11:02:18 by augay             #+#    #+#             */
/*   Updated: 2020/02/24 17:29:37 by rofernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char		*c2e(char c)
{
	char *s;

	if ((s = malloc(sizeof(char) * 2)) == NULL)
		exit(0);
	s[0] = c;
	s[1] = '\0';
	return (s);
}

static void	ft_translate_1(int *i, char **out, char **s, int *tab)
{
	(*i)++;
	if (s[0][*i] == '\'')
		out[0] = ft_strjoin_free(out[0], inv('\''), 2);
	else if (s[0][*i] == '>')
		out[0] = ft_strjoin_free(out[0], ">", 1);
	else if (s[0][*i] == '<')
		out[0] = ft_strjoin_free(out[0], "<", 1);
	else if (s[0][*i] == '|')
		out[0] = ft_strjoin_free(out[0], "|", 1);
	else if (s[0][*i] == ' ')
		out[0] = ft_strjoin_free(out[0], inv(' '), 2);
	else if (s[0][*i] == ';')
		out[0] = ft_strjoin_free(out[0], ";", 1);
	else
		out[0] = ft_strjoin_free(out[0], c2e(s[0][*i]), 2);
	tab[ft_strlen(out[0]) - 1] = 1;
}

static void	ft_translate_2(int *i, char **s, char **out)
{
	(*i)++;
	if (s[0][*i] == '"')
		out[0] = ft_strjoin_free(out[0], inv('"'), 2);
	else if (s[0][*i] == '\\')
		out[0] = ft_strjoin_free(out[0], "\\", 1);
	else if (s[0][*i] == '$')
		out[0] = ft_strjoin_free(out[0], "$", 1);
	else if (s[0][*i] == ';')
		out[0] = ft_strjoin_free(out[0], ";", 1);
}

void		ft_translate(char **s, int d, char **out, int *tab)
{
	int		i;
	char	*q;

	i = d - 1;
	while (s[0][++i] && s[0][i] != '\n')
		if (is_in_s(s[0], i) == 0 && s[0][i] == '\\' && s[0][i + 1] &&
		(s[0][i + 1] == '"' || s[0][i + 1] == '\\' || s[0][i + 1] == '$'))
			ft_translate_2(&i, s, out);
		else if (is_in_sd(s[0], i, NULL) == 0 && s[0][i] == '\\'
		&& s[0][i + 1])
			ft_translate_1(&i, out, s, tab);
		else
		{
			q = ft_substr(s[0], i, 1);
			out[0] = ft_strjoin_free(out[0], q, 1);
			free(q);
		}
	return ;
}
