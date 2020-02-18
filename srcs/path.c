/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofernan <rofernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 11:12:31 by rofernan          #+#    #+#             */
/*   Updated: 2020/02/18 13:22:52 by rofernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	prep_path(t_shell *shell)
{
	char **s;
	t_env *e1;

	if (!(e1 = ft_envfind(shell->env, "PATH", ft_strcmp)))
	{
		ft_putendl_fd("PATH not found", 2);
		return ;
	}
	s = ft_split(e1->data, ':');
	int			i;
	char		*tmp;
	struct stat	a;
	int			f;
	int			k;

	i = 0;
	f = 0;
	k = 0;
	while(s[i])
	{
		tmp = ft_strjoin_free(s[i], "/", 1);
		tmp = ft_strjoin_free(tmp, shell->args[0], 1);
		if ((k = stat(tmp, &a)) == 0)
		{
			f = 1;
			break ;
		}
		i++;
	}
	if (f == 1)
	{
		free(shell->args[0]);
		shell->args[0] = ft_strdup(tmp);
		free(tmp);
	}
	else
		ft_putendl_fd("PATH not found", 2);
}
