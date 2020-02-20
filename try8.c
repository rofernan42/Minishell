/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   try8.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: augay <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 13:17:27 by augay             #+#    #+#             */
/*   Updated: 2020/02/20 13:17:29 by augay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"
#include "libft/libft.h"

int		count_p(char *s)
{
	int i;
	int so;

	i = 0;
	so = 0;
	while (s[i])
	{
		if (s[i] == ':')
			so += 1;
		i++;
	}
	return (so);
}

char	**prep_0_1(t_shell *shell)
{
	t_env	*e1;
	char	**s;

	e1 = ft_envfind(shell->env, "PATH", ft_strcmp);
	if (e1 == NULL)
	{
		write(1, "not found\n", 10);
		return (NULL);
	}
	s = ft_split(e1->data, ':');
	return (s);
}

void	prep_0(t_shell *shell)
{
	char		**s;
	int			i;
	char		*tmp;
	struct stat	a;
	int			f;

	i = -1;
	f = 0;
	s = prep_0_1(shell);
	if (stat(shell->args[0], &a) == 0)
	{
		return ;
	}
	while (s[++i] && (tmp = ft_concat(ft_concat(s[i], "/"),
	shell->args[0])) != NULL)
		if ((stat(tmp, &a)) == 0 && (f = 1))
			break ;
	if (f == 1)
	{
		free(shell->args[0]);
		shell->args[0] = ft_strdup(tmp);
		free(tmp);
	}
}

char	**ft_copy(char **s, int fin)
{
	int		i;
	char	**o;

	i = 0;
	while (s[i] && i < fin)
		i++;
	o = malloc(sizeof(char*) * (i + 1));
	o[i] = 0;
	i = 0;
	while (s[i] && i < fin)
	{
		o[i] = ft_strdup(s[i]);
		i++;
	}
	return (o);
}

int		ft_long(char **s)
{
	int i;

	i = 0;
	if (s == NULL)
		return (0);
	while (s[i])
		i++;
	return (i);
}

int		*fill_tab(const char *s)
{
	int l;
	int *o;
	int i;

	l = ft_strlen(s);
	o = malloc(sizeof(int) * (l));
	i = 0;
	while (i < l)
	{
		o[i] = 0;
		if (s[i] < 0)
			o[i] = 1;
		i++;
	}
	return (o);
}

int		**fill_tabf(char **s)
{
	int i;
	int j;
	int **o;

	i = 0;
	j = 0;
	while (s[i])
	{
		i++;
	}
	o = malloc(sizeof(int*) * i);
	i = 0;
	while (s[i])
	{
		while (s[i][j])
		{
			j++;
		}
		o[i] = malloc(sizeof(int) * j);
		memset(o[i], 0, sizeof(int) * j);
		i++;
		j = 0;
	}
	return (o);
}
