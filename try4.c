/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   try4.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: augay <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 13:14:13 by augay             #+#    #+#             */
/*   Updated: 2020/02/20 13:15:54 by augay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int		enter(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

int		count_args(char **args)
{
	int i;

	i = 0;
	while (args[i])
		i++;
	return (i);
}

void	layout_args(t_shell *shell)
{
	int i;
	int j;

	i = 0;
	while (shell->args[i])
	{
		j = 0;
		while (shell->args[i][j])
		{
			if (shell->args[i][j] == '\n')
			{
				shell->args[i][j] = '\0';
				break ;
			}
			j++;
		}
		i++;
	}
}

void	init_env(t_env **env)
{
	char *name;
	char *data;

	*env = ft_envnew(0, 0);
	create_env(env, "HOME", "blo             blo");
	create_env(env, "PWD", getcwd(NULL, 0));
	create_env(env, "OLDPWD", getcwd(NULL, 0));
	create_env(env, "PATH", "/Users/augay/.brew/bin:/usr/local/bin:\
/usr/bin:/bin:/usr/sbin:/sbin:/Applications/VMware Fusion.app/Contents/\
Public:/usr/local/mongodb/bin:/usr/local/munki:/Library/Frameworks/\
Mono.framework/Versions/Current/Commands:/Users/augay/Desktop/minishell");
	create_env(env, "?", "0");
}

int		nb_bs(const char *s, int f)
{
	int i;

	i = f;
	while (f >= 0 && s[f] && s[f] == '\\')
	{
		f--;
	}
	return (i - f);
}

void	print_env(t_env *env)
{
	while (env != NULL)
	{
		env = env->next;
	}
}

char	*ft_concat(char *s1, char *s2)
{
	int		i1;
	int		i2;
	char	*o;
	int		i;

	i1 = ft_strlen(s1);
	i2 = ft_strlen(s2);
	o = malloc(sizeof(char) * (i1 + i2 + 2));
	i = 0;
	while (s1[i])
	{
		o[i] = s1[i];
		i++;
	}
	i2 = 0;
	while (s2[i2])
	{
		o[i + i2] = s2[i2];
		i2++;
	}
	o[i + i2] = '\0';
	free(s1);
	return (o);
}
