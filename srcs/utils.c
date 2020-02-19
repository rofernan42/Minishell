/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofernan <rofernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 18:15:32 by rofernan          #+#    #+#             */
/*   Updated: 2020/02/19 17:23:49 by rofernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
