/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofernan <rofernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 11:12:31 by rofernan          #+#    #+#             */
/*   Updated: 2020/02/26 16:20:04 by rofernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	prep2path(char **s, t_shell *shell, char **args)
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
		free(args[0]);
		args[0] = ft_strdup(tmp);
		free(tmp);
	}
	else if (contain_c(args[0], '/'))
	{
		disp_err(shell->name_prog, 0, args[0], "No such file or directory");
		return (127);
	}
	else if (wrap_cmp(args[0], '>') && wrap_cmp(args[0], '<') \
	&& wrap_cmp_2(args[0], ">>"))
	{
		disp_err(shell->name_prog, 0, args[0], "command not found");
		return (127);
	}
	return (0);
}

int			prep_path(t_shell *shell, char **args)
{
	int			ret;
	char		**s;
	t_env		*e1;
	struct stat	a;

	if (!(e1 = ft_envfind(shell->env, "PATH", ft_strcmp)))
	{
		disp_err(shell->name_prog, 0, args[0], "No such file or directory");
		return (127);
	}
	if (stat(args[0], &a) == 0)
	{
		if (contain_c(args[0], '/') && a.st_mode & S_IFDIR)
		{
			disp_err(shell->name_prog, 0, args[0], "is a directory");
			return (126);
		}
		else if (!(a.st_mode & S_IXUSR || a.st_mode & S_IXGRP \
		|| a.st_mode & S_IXOTH))
		{
			disp_err(shell->name_prog, 0, args[0], "Permission denied");
			return (126);
		}
		else
			return (0);
	}
	s = ft_split(e1->data, ':');
	ret = prep2path(s, shell, args);
	ft_free(&s);
	return (ret);
}
