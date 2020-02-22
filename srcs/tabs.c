/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tabs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofernan <rofernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 16:05:59 by rofernan          #+#    #+#             */
/*   Updated: 2020/02/21 11:30:16 by rofernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		ft_tablength(char **s)
{
	int i;

	i = 0;
	if (s == NULL)
		return (0);
	while (s[i])
		i++;
	return (i);
}

char	**ft_tabcopy(char **s, int fin)
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

// void		del_args(char **args)
// {
// 	int i;

// 	i = 0;
// 	if (args == NULL)
// 		return ;
// 	while (args[i])
// 		ft_strdel(&args[i++]);
// 	ft_strdel(&args[i]);
// 	free(args);
// 	args = NULL;
// }

void	h_split(t_shell *shell, char ***cmd)
{
	int		fin;
	int		p;
	int		part;
	int		last_part;

	p = 0;
	part = 0;
	last_part = 0;
		//print("DEV SPLIT\n");

	fin = ft_tablength(cmd[0]);
	// ft_p(cmd);
			//print("DEV SPLIT 1 et %i\n",fin);
	//print("cmd[2] = [%s]\n",cmd[2]);
	while (part <= fin && p < 1)
	{
		//print("WHILE SPLT et part=%i, fin=%i, p=%i\n",part,fin,p);
		if (part == fin || !ft_strcmp(cmd[0][part], "|"))
		{
			ft_free(&shell->args);
			//print("AV CPY\n");
			shell->args = (ft_tabcopy(cmd[0] + last_part, part - last_part));
						//print("AP CPY\n");s
			last_part = part + 1;
			p++;
		}
		part++;
	}
	//print("MID SPLIT\n");
	if (part < fin)
	{
		ft_free(&shell->next_args);
		shell->next_args = ft_tabcopy(cmd[0] + last_part, fin - last_part);
	}
	else
	{
		ft_free(&shell->next_args);
		shell->next_args = NULL;
	}
	ft_free(cmd);
}
