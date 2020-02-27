/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofernan <rofernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 11:15:51 by rofernan          #+#    #+#             */
/*   Updated: 2020/02/25 15:00:39 by rofernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char		**extract(char **args)
{
	int		i;
	int		j;
	char	**tmp;

	i = -1;
	j = 0;
	while (args[++i])
		if (!wrap_cmp(args[i], '|'))
			break ;
		else if (i == 0 || (i > 0 && !is_chevron(args[i]) \
		&& !is_chevron(args[i - 1])))
			j++;
	if (!(tmp = malloc(sizeof(char *) * (j + 1))))
		exit(EXIT_FAILURE);
	i = -1;
	j = 0;
	while (args[++i])
		if (!wrap_cmp(args[i], '|'))
			break ;
		else if (i == 0 || (i > 0 && !is_chevron(args[i]) \
		&& !is_chevron(args[i - 1])))
			tmp[j++] = ft_strdup(args[i]);
	tmp[j] = NULL;
	return (tmp);
}
