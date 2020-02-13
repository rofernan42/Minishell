/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofernan <rofernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 10:40:51 by rofernan          #+#    #+#             */
/*   Updated: 2020/02/13 14:15:11 by rofernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <signal.h>
# include <sys/stat.h>
# include <dirent.h>
# include <stdio.h>
# include <sys/errno.h>

# define BUF_SIZE 32

typedef struct		s_env
{
	char			*name;
	char			*data;
	struct s_env	*next;
}					t_env;

typedef struct		s_shell
{
	char			*command;
	char			**args;
	char			*str;
}					t_shell;

t_env				*ft_envnew(char *name, char *data);
void				ft_envadd_back(t_env **alst, t_env *new);
t_env				*ft_envfind(t_env *begin_list, void *name_ref, int (*cmp)());
void				ft_envdelone(t_env *env, void (*del)(void *));
void				create_env(t_env **env, char *name, char *data);

void				display_error(char *command, char *arg, char *err);

void				ft_pwd(t_env *env);
void				ft_cd(char *arg, t_env *env);
void				ft_export(char **vars, t_env *env);
void				ft_env(t_env *env);


int					match(char *s1, char *s2);

#endif
