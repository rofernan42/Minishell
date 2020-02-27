/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pop_word.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofernan <rofernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 13:16:02 by augay             #+#    #+#             */
/*   Updated: 2020/02/24 17:21:17 by rofernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char		**wrap(int **tt, char **oo, char **out)
{
	tt[0] = cp_add(tt[0], ft_strlen(oo[0]));
	out = split_cmd(oo[0], tt[0]);
	free(oo[0]);
	free(tt[0]);
	return (out);
}

static void	wrap_finish(char **oo, char ***out, int **tt)
{
	out[0] = NULL;
	oo[0] = malloc(sizeof(char) * 1);
	oo[0][0] = '\0';
	tt[0] = malloc(sizeof(int) * 1);
	tt[0][0] = -8;
}

char		**finish_p(char **cmd, int **tab)
{
	int		*i;
	char	**out;
	char	*oo;
	int		*tt;

	if (cmd == NULL)
		return (NULL);
	i = finish_p_i();
	// printf("FIMISH P\n");
	// ft_p(cmd);
	wrap_finish(&oo, &out, &tt);
	while (cmd[++i[0]] && (i[1] = -1))
	{
		while (cmd[i[0]][++i[1]])
			if ((tab[i[0]][i[1]] == 1 || (p(cmd, i) && cd(cmd, i) && cg(cmd, i)
			&& v(cmd, i)) || is_in_sd(cmd[i[0]], i[1], tab[i[0]]) == 1)
			&& (oo = ft_strjoin_free(oo, ft_substr(cmd[i[0]], i[1], 1), 2)))
			{
				// printf("JYVAIS 1 c=%c avec %i, %i, %i\n", re(cmd, i), tab[i[0]][i[1]] == 1, p(cmd, i) && cd(cmd, i) && cg(cmd, i)
			// && v(cmd, i), is_in_sd(cmd[i[0]], i[1], tab[i[0]]) == 1);
				cmd[i[0]][i[1]] = re(cmd, i);
			}
			else
			{
				// printf("ELSE\n");
				// printf("ELSE 1 c=%c avec %i, %i, %i\n", re(cmd, i), tab[i[0]][i[1]] == 1, p(cmd, i) && cd(cmd, i) && cg(cmd, i)
			// && v(cmd, i), is_in_sd(cmd[i[0]], i[1], tab[i[0]]) == 1);
				finish_p_1(&oo, &tt, i, cmd);
			}
		oo = ft_strjoin_free(oo, " ", 1);
	}
	ft_free(&cmd);
	free(i);
	return (wrap(&tt, &oo, out));
}

void		pop_char(char **s, int i, int c1, int c2)
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
			j++;
	}
	free(s[i]);
	s[i] = out;
}

void		init_pop_word(int *i, char *c, int *c1, int *c2)
{
	*i = -1;
	*c = 0;
	*c1 = 0;
	*c2 = 0;
}
