/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofernan <rofernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 11:12:31 by rofernan          #+#    #+#             */
/*   Updated: 2020/02/21 13:18:03 by rofernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	prep2path(char **s, t_shell *shell)
{
	struct stat	a;
	int			i;
	int			f;
	char		*tmp;

	i = 0;
	f = 0;
	while (s[i])
	{
		tmp = ft_strjoin(s[i], "/");
		tmp = ft_strjoin_free(tmp, shell->args[0], 1);
		if (!(stat(tmp, &a)) && (f = 1))
			break ;
		i++;
	}
	if (f == 1)
	{
		free(shell->args[0]);
		shell->args[0] = ft_strdup(tmp);
		free(tmp);
	}
	else
		disp_err(shell->name_prog, 0, shell->args[0], "command not found");
}

void	prep_path(t_shell *shell)
{
	char		**s;
	t_env		*e1;
	struct stat	a;

	if (!(e1 = ft_envfind(shell->env, "PATH", ft_strcmp)))
	{
		ft_putendl_fd("PATH not found", 2);
		return ;
	}
	if (stat(shell->args[0], &a) == 0)
		return ;
	s = ft_split(e1->data, ':');
	prep2path(s, shell);
	del_args(s);
}
