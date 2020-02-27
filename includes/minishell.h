/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofernan <rofernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 10:40:51 by rofernan          #+#    #+#             */
/*   Updated: 2020/02/27 12:55:10 by rofernan         ###   ########.fr       */
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
# include "mini_struct.h"

# define BUF_SIZE 32
# define ERCHEV "syntax error near unexpected token `"

extern int g_sig;

/*
**	BUILTIN.C
*/
int			is_builtin(char **s);
int			builtin_exec(t_shell *shell, char **s);

/*
**	CHECK_QUOTES.C
*/
int			is_in_s(char *s, int m);
int			is_in_sd(const char *s, int m, int *tab);
char		*inv(char c);

/*
**	CONDITIONS.C
*/
int			condition_1(char const *s, int i, int *tab);
int			condition_2(char const *s, int i, int *tab);
int			condition_3(char const *s, int i, int j, int *tab);

/*
**	COPY_CLOSE_FD.C
*/
void		copy_stdinout(t_shell *shell);
void		close_stdinout(t_shell *shell);

/*
**	ENV_*.C
*/
t_env		*ft_envnew(char *name, char *data);
void		ft_envadd_back(t_env **alst, t_env *new);
t_env		*ft_envfind(t_env *begin_list, void *name_ref, int (*cmp)());
void		ft_envdelone(t_env *env);
void		ft_envclear(t_env *begin_env, void (*free_fct)(void *));
void		create_env(t_env **env, char *name, char *data);

/*
**	ERROR.C
*/
<<<<<<< HEAD
void		disp_err(char *prog, char *cmd, char *arg, char *err);
int			chevron_error(char *prog, char *arg, char *cmd, char *end);
void		command_error(char *command, char *err);
=======
void		init_env(t_env **env, char **s);
void		init_name_prog(t_shell *shell, char *av);
>>>>>>> 86bcdd7fde409762dca3744ec1b9f7d092c2e10e

/*
**	EXTRACT.C
*/
char		**extract(char **args);

/*
**	FORKS.C
*/
void		fork_right(t_shell *shell, int i, int *pdes);
int			first(t_shell *shell);
void		fork_left(int *pdes, t_shell *shell);

/*
**	FREE.C
*/
void		ft_free(char ***s);
int			del_war(char ***s, int i);
void		free_all(t_shell *shell);

/*
**	FT_*.C
*/
int			ft_echo(char **args);
int			ft_pwd(void);
int			ft_cd(t_shell *shell, char *arg);
int			ft_export(t_shell *shell, char **vars);
int			ft_unset(char **vars, t_env *env);
int			ft_env(t_env *env);
int			ft_exit(t_shell *shell, char **args);

/*
**	FT_STDIN.C
*/
int			still(t_shell *shell);
int		    execute_cmd(char **s, t_shell *shell);
int			exec_pipe(t_shell *shell, int i);
void		ft_stdin(t_shell *shell, char **command);

/*
**	INIT_TABLE.C
*/
int			*fill_tab(const char *s);
int			**fill_tabf(char **s);

/*
**	INIT.C
*/
void		init_env(t_env **env, char **s);
void		init_name_prog(t_shell *shell, char *av);

/*
**	PATH.C
*/
int			prep_path(t_shell *shell, char **args);

/*
**	POP_WORD.C
*/
char		**wrap(int **tt, char **oo, char **out);
char		**finish_p(char **cmd, int **tab);
void		pop_char(char **s, int i, int c1, int c2);
void		init_pop_word(int *i, char *c, int *c1, int *c2);

/*
**	REDIRECTION.C
*/
int			test_syntax(t_shell *shell, char **args);
int			open_fd(t_shell *shell, char **args);

/*
**	REPLACE.C
*/
int			replace(char **s, int d, t_env *env);
int			*finish_p_i(void);
void		finish_p_1(char **oo, int **tt, int *i, char **cmd);

/*
**	REV_CMD.C
*/
void		pop_word(char **s);
char		**ft_reverse(char **s);
void		trad(char **s, t_env *env);
void		sig_handle_c(int s);
int			*cp_add(int *t, int p);

/*
**	SHELL_BODY.C
*/
void		shell_body(char *in, t_shell *shell);

/*
**	SPLIT.C
*/
void		parsing(char *s, char **out, int *tab);
char		**split_cmd(char *s, int *tab);
int			end_name(char c, int i);

/*
**	STATUS_RES.C
*/
void		status_res(t_shell *shell, int status);

/*
**	TABS.C
*/
int			ft_tablength(char **s);
char		**ft_tabcopy(char **s, int fin);
void		h_split(t_shell *shell, char ***cmd);

/*
**	TRANSLATE.C
*/
void		ft_translate(char **s, int d, char **out, int *tab);

/*
**	UTILS_2.C
*/
void		sig_handle_b(int s);
int			p(char **cmd, int *i);
int			nb_bs(const char *s, int f);

/*
**	UTILS.C
*/
int			count_char(char *s, char c);
int			contain_c(char *s, char c);
int			is_chevron(char *str);
int			reste_arg(char **args, char *reste);
int			nb_arg(char **args, char *to_count);

/*
**	WRAP_CMP.C
*/
int			wrap_cmp(char *s, char c);
int			wrap_cmp_2(char *s, char *c);

/*
**	WRAP_PARSING.C
*/
int			cd(char **cmd, int *i);
int			cg(char **cmd, int *i);
int			v(char **cmd, int *i);
char		re(char **cmd, int *i);

#endif
