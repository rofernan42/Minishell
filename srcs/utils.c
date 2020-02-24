/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: augay <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 10:43:46 by augay             #+#    #+#             */
/*   Updated: 2020/02/24 10:44:05 by augay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	count_char(char *s, char c)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] == c)
			count++;
		i++;
	}
	return (count);
}

int	contain_c(char *s, char c)
{
	int i;

	i = 0;
	while (s[i])
	{
		if (c == s[i])
			return (1);
		i++;
	}
	return (0);
}

int	is_chevron(char *str)
{
	if (!ft_strcmp(str, ">") || !ft_strcmp(str, "<") || !ft_strcmp(str, ">>"))
		return (1);
	return (0);
}

int	reste_arg(char **args, char *reste)
{
	int i;

	i = 0;
	if (args == NULL)
		return (0);
	while (args[i])
	{
		if (!ft_strcmp(args[i], reste))
			return (1);
		i++;
	}
	return (0);
}

int	nb_arg(char **args, char *to_count)
{
	int i;
	int nb;

	i = 0;
	nb = 0;
	while (args[i])
	{
		if (!ft_strcmp(args[i], to_count))
			nb++;
		i++;
	}
	return (nb);
}
