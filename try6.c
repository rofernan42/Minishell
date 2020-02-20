/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   try6.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: augay <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 13:16:02 by augay             #+#    #+#             */
/*   Updated: 2020/02/20 13:16:03 by augay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"
#include "libft/libft.h"

int		cd(char **cmd, int *i)
{
	if (cmd[i[0]][i[1]] != '>')
		return (1);
	return (0);
}

int		cg(char **cmd, int *i)
{
	if (cmd[i[0]][i[1]] != '<')
		return (1);
	return (0);
}

int		v(char **cmd, int *i)
{
	if (cmd[i[0]][i[1]] != ';')
		return (1);
	return (0);
}

char	re(char **cmd, int *i)
{
	return (cmd[i[0]][i[1]] * ((cmd[i[0]][i[1]] < 0 && cmd[i[0]][i[1]] != -1
	* '"' && cmd[i[0]][i[1]] != -1 * '\'') ? -1 : 1));
}

char	**wrap(int *tt, char *oo, char **out)
{
	tt = cp_add(tt, ft_strlen(oo));
	out = split_cmd(oo, tt);
	free(oo);
	free(tt);
	return (out);
}

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
