/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofernan <rofernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 11:12:31 by rofernan          #+#    #+#             */
/*   Updated: 2020/02/26 13:36:37 by rofernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	prep2path(char **s, t_shell *shell, char **args)
{
	struct stat	a;
	int			i;
	int			f;
	char		*tmp;

	i = -1;
	while (!(f = 0) && s[++i])
	{
		tmp = ft_strjoin_free(ft_strjoin(s[i], "/"), args[0], 1);
		if (!(stat(tmp, &a)) && (f = 1))
			break ;
		free(tmp);
		tmp = NULL;
	}
	if (f == 1)
	{
		if (contain_c(args[0], '/'))
			disp_err(shell->name_prog, 0, args[0], \
			"is a directory");
		free(args[0]);
		args[0] = ft_strdup(tmp);
		free(tmp);
	}
	else if (contain_c(args[0], '/'))
	{
		disp_err(shell->name_prog, 0, args[0], \
		"No such file or directory");
		// exit(127);
	}
	else if (wrap_cmp(args[0], '>') && wrap_cmp(args[0], '<') && wrap_cmp_2(args[0], ">>"))
	{
		disp_err(shell->name_prog, 0, args[0], "command not found");
		// exit(127);
	}
}

void		prep_path(t_shell *shell, char **args)
{
	char		**s;
	t_env		*e1;
	struct stat	a;

	if (!(e1 = ft_envfind(shell->env, "PATH", ft_strcmp)))
	{
		ft_putendl_fd("PATH not found", 2);
		return ;
	}
	// if (stat(args[0], &a) == 0)
	// 	return ;
	s = ft_split(e1->data, ':');
	prep2path(s, shell, args);
	ft_free(&s);
}
