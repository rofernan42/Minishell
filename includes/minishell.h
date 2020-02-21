/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofernan <rofernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 10:40:51 by rofernan          #+#    #+#             */
/*   Updated: 2020/02/21 12:04:58 by rofernan         ###   ########.fr       */
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
	char			*name_prog;
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
void				h_split(t_shell *shell, char **cmd);

/*
**	UTILS.C
*/
int					count_char(char *s, char c);
int					contain_c(char *s, char c);
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
void				ft_envclear(t_env *begin_env, void (*free_fct)(void *));
void				create_env(t_env **env, char *name, char *data);
void				init_env(t_env **env);

/*
**	ERROR.C
*/
void				disp_err(char *prog, char *cmd, char *arg, char *comp, char *err);
void				command_error(char *command, char *err);

/*
**	PATH.C
*/
void				prep_path(t_shell *shell);

/*
**	FT_*.C
*/
void				ft_echo(char **args);
void				ft_pwd(t_env *env);
void				ft_cd(t_shell *shell, char *arg);
void				ft_export(t_shell *shell, char **vars);
void				ft_unset(char **vars, t_env *env);
void				ft_env(t_env *env);

/*
**	REDIRECTION.C
*/
int					open_fd(t_shell *shell, char **args);
int					copy_stdinout(t_shell *shell);
void				close_stdinout(t_shell *shell);
int					open_file(t_shell *shell);

/*
**	EXEC_COMMANDS.C
*/
int					is_builtin(t_shell *shell, int i);
int					execute_cmd(char **cmd, t_shell *shell);

/*
**	FT_STDIN.C
*/
void				exec_pipe(t_shell *shell, int i);
void				ft_stdin(t_shell *shell, char ** command);

/*
**	FREE.C
*/
void				free_all(t_shell *shell);

/*
**	BONUS
*/
int					match(char *s1, char *s2);

// int			count_p(char *s);
// char		**prep_0_1(t_shell *shell);
// void		prep_0(t_shell *shell);
// char		**ft_copy(char **s, int fin);
// int			ft_long(char **s);
int			*fill_tab(const char *s);
int			**fill_tabf(char **s);
void		pop_word(char **s);
char		**ft_reverse(char **s);
void		trad(char **s, t_env *env);
// int			contain_c(char *s, char c);
// void		ft_free(char **s);
void		sig_handle_c(int s);
void		sig_handle_b(int s);
int			*cp_add(int *t, int p);
int			cd(char **cmd, int *i);
int			cg(char **cmd, int *i);
int			v(char **cmd, int *i);
char		re(char **cmd, int *i);
char		**wrap(int *tt, char *oo, char **out);
char		**finish_p(char **cmd, int **tab);
void		pop_char(char **s, int i, int c1, int c2);
void		init_pop_word(int *i, char *c, int *c1, int *c2);
int			replace(char **s, int d, t_env *env);
int			*finish_p_i(void);
void		finish_p_1(char **oo, int **tt, int *i, char **cmd);
int			p(char **cmd, int *i);
int			enter(char *str);
// int			count_args(char **args);
// void		layout_args(t_shell *shell);
int			nb_bs(const char *s, int f);
// void		print_env(t_env *env);
// char		*ft_concat(char *s1, char *s2);
// int			contain(char *s);
int			is_in_s(char *s, int m);
int			is_in_sd(const char *s, int m, int *tab);
void		ft_translate(char **s, int d, char **out, int *tab);
int			quote(char *s, char **out, int *tab);
void		parsing(char *s, char **out, int *tab);
void		ft_p(char **s);
static char	**splitbody(int nbc, char const *s, char **out, int *tab);
char		**split_cmd(char *s, int *tab);
int			end_name(char c, int i);

#endif
