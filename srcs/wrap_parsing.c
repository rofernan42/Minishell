/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wrap_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: augay <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 11:07:29 by augay             #+#    #+#             */
/*   Updated: 2020/02/24 11:07:30 by augay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
