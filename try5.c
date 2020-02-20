/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   try5.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: augay <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 13:15:57 by augay             #+#    #+#             */
/*   Updated: 2020/02/20 13:15:58 by augay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"
#include "libft/libft.h"

int		replace(char **s, int d, t_env *env)
{
	int		i;
	t_env	*e1;
	char	*n;
	char	*out;
	int		j;
	int		k;

	i = d;
	while ((j = -1) && end_name(s[0][i], i) == 1)
		i++;
	out = ft_substr(s[0], d, i - d);
	e1 = (ft_envfind(env, out, ft_strcmp) == NULL) ? ft_envnew(out, "") : ft_envfind(env, out, ft_strcmp);
	k = ft_strlen(s[0]) + ft_strlen(e1->data) - ft_strlen(e1->name);
	free(out);
	out = malloc(sizeof(char) * k);
	out[k - 1] = '\0';
	while (++j < d - 1)
		out[j] = s[0][j];
	k = -1;
	while (e1->data[++k])
	{
		out[j] = e1->data[k];
		if (out[j] == '"' || out[j] == '\'' || out[j] == '>' || out[j] == '<' || out[j] == '|')
			out[j] = -e1->data[k];
		j++;
	}
	while (s[0][i])
		out[j++] = s[0][i++];
	if (s[0] != NULL)
		free(s[0]);
	s[0] = out;
	return ((int)(d + (int)ft_strlen(e1->data)) - 1);
}

int		*finish_p_i(void)
{
	int *i;

	i = malloc(sizeof(int) * 2);
	i[0] = -1;
	i[1] = 0;
	return (i);
}

void	finish_p_1(char **oo, int **tt, int *i, char **cmd)
{
	oo[0] = ft_strjoin_free(ft_strjoin_free(oo[0], " ", 1),
	ft_substr(cmd[i[0]], i[1], 1), 2);
	if (cmd[i[0]][i[1] + 1] == '>')
	{
		(oo[0])[ft_strlen(oo[0]) - 1] = (oo[0])[ft_strlen(oo[0]) - 1] * -1;
		tt[0] = cp_add(tt[0], ft_strlen(oo[0]));
		(tt[0])[ft_strlen(oo[0]) - 1] = -1;
		oo[0] = ft_concat(oo[0], ">");
		i[1]++;
	}
	(oo[0])[ft_strlen(oo[0]) - 1] = oo[0][ft_strlen(oo[0]) - 1] * -1;
	(tt[0]) = cp_add(tt[0], ft_strlen(oo[0]));
	(tt[0])[ft_strlen(oo[0]) - 1] = -1;
	oo[0] = ft_concat(oo[0], " ");
}

int		p(char **cmd, int *i)
{
	if (cmd[i[0]][i[1]] != '|')
		return (1);
	return (0);
}
