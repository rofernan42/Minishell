/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: augay <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 11:40:51 by augay             #+#    #+#             */
/*   Updated: 2020/02/20 11:40:53 by augay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <dirent.h>
#include "includes/minishell.h"
#include "libft/libft.h"
#include <signal.h>

char	**finish_p(char **cmd, int **tab)
{
	int		*i;
	char	**out;
	char	*oo;
	int		*tt;

	if (cmd == NULL)
		return (NULL);
	i = finish_p_i();
	oo = malloc(sizeof(char) * 1);
	oo[0] = '\0';
	tt = malloc(sizeof(int) * 1);
	tt[0] = -8;
	while (cmd[++i[0]] && (i[1] = -1))
	{
		while (cmd[i[0]][++i[1]])
			if ((tab[i[0]][i[1]] == 1 || (p(cmd, i) && cd(cmd, i) && cg(cmd, i)
			&& v(cmd, i)) || is_in_sd(cmd[i[0]], i[1], tab[i[0]]) == 1) &&
(oo = ft_strjoin_free(oo, ft_substr(cmd[i[0]], i[1], 1), 2)))
				cmd[i[0]][i[1]] = re(cmd, i);
			else
				finish_p_1(&oo, &tt, i, cmd);
		oo = ft_concat(oo, " ");
	}
	return (wrap(tt, oo, out));
}

void	pop_char(char **s, int i, int c1, int c2)
{
	int		j;
	char	*out;
	int		k;

	k = 0;
	j = 0;
	out = malloc(sizeof(char) * (ft_strlen(s[i]) - 1));
	out[ft_strlen(s[i]) - 2] = '\0';
	while (s[i][j])
	{
		if (j != c1 && j != c2)
		{
			out[k] = s[i][j];
			k++;
			j++;
		}
		else
		{
			j++;
		}
	}
	free(s[i]);
	s[i] = out;
}

void	init_pop_word(int *i, char *c, int *c1, int *c2)
{
	*i = -1;
	*c = 0;
	*c1 = 0;
	*c2 = 0;
}

void	pop_word(char **s)
{
	int		j;
	int		i;
	char	c;
	int		c1;
	int		c2;

	init_pop_word(&i, &c, &c1, &c2);
	while (s[++i] && (j = -1))
		while (s[i][++j])
			if (c == 0 && s[i][j] == '"' && (c = '"'))
				c1 = j;
			else if (c == '"' && s[i][j] == '"' && !(c = 0))
			{
				c2 = j;
				pop_char(s, i, c1, c2);
				j = j - 2;
			}
			else if (c == 0 && s[i][j] == '\'' && (c = '\''))
				c1 = j;
			else if (c == '\'' && s[i][j] == '\'' && !(c = 0))
			{
				c2 = j;
				pop_char(s, i, c1, c2);
				j = j - 2;
			}
}

char	**ft_reverse(char **s)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (s[i])
	{
		while (s[i][j])
		{
			if (s[i][j] < 0)
				s[i][j] = -1 * s[i][j];
			j++;
		}
		i++;
		j = 0;
	}
	return (s);
}
