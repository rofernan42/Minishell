/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofernan <rofernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 10:40:51 by rofernan          #+#    #+#             */
/*   Updated: 2020/02/18 18:29:29 by rofernan         ###   ########.fr       */
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
	char			**command;
	char			**args;
	char			*str_echo;
	int				fd_in;
	int				fd_out;
	int				fdpipe[2];
	int				stdout_cpy;
	int				stdin_cpy;
	t_env			*env;
}					t_shell;

/*
**	TABS.C
*/
int					ft_tablength(char **s);
char				**ft_tabcopy(char **s, int fin);
void				del_args(char **args);

/*
**	UTILS.C
*/
int					is_chevron(char *str);

/*
**	ENV_*.C
*/
t_env				*ft_envnew(char *name, char *data);
void				ft_envadd_back(t_env **alst, t_env *new);
t_env				*ft_envfind(t_env *begin_list, void *name_ref, int (*cmp)());
void				ft_envdelone(t_env *env);
void				create_env(t_env **env, char *name, char *data);
void				ft_envclear(t_env *begin_env, void (*free_fct)(void *));

/*
**	ERROR.C
*/
void				disp_err(char *command, char *arg, char *compl, char *err);
void				command_error(char *command, char *err);

/*
**	FREE.C
*/
void				free_all(t_shell *shell);

int					check_env_name(char *name);

void				prep_path(t_shell *shell);

void				ft_echo(t_shell *shell);
void				ft_pwd(t_env *env);
void				ft_cd(char *arg, t_env *env);
void				ft_export(char **vars, t_env *env);
void				ft_unset(char **vars, t_env *env);
void				ft_env(t_env *env);

int					open_fd(t_shell *shell);
void				redirect(t_shell *shell, char **envp);

void				ft_stdin(t_shell *shell, char ** command);


int					match(char *s1, char *s2);
void ft_p(char **s);
char **ft_copy(char **s, int fin);
int ft_long(char **s);

#endif
