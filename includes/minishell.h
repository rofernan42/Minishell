/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofernan <rofernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 10:40:51 by rofernan          #+#    #+#             */
/*   Updated: 2020/02/20 11:21:21 by rofernan         ###   ########.fr       */
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
	char			**args;
	char			**next_args;
	int				fd_in;
	int				fd_out;
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
int					reste_arg(char **args, char *reste);
int					nb_arg(char **args, char *to_count);

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



int					check_env_name(char *name);

void				prep_path(t_shell *shell);

void				ft_echo(t_shell *shell);
void				ft_pwd(t_env *env);
void				ft_cd(char *arg, t_env *env);
void				ft_export(char **vars, t_env *env);
void				ft_unset(char **vars, t_env *env);
void				ft_env(t_env *env);

/*
**	REDIRECTION.C
*/
int					open_fd(t_shell *shell);
void				copy_stdinout(t_shell *shell);
void				close_stdinout(t_shell *shell);

/*
**	EXEC_COMMANDS.C
*/
int					execute_cmd(char **cmd, t_shell *shell);

/*
**	FT_STDIN.C
*/
void				exec_pipe(t_shell *shell);
void				ft_stdin(t_shell *shell, char ** command);

/*
**	FREE.C
*/
void				free_all(t_shell *shell);

/*
**	BONUS
*/
int					match(char *s1, char *s2);

#endif
