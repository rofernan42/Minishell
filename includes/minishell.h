/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofernan <rofernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 10:40:51 by rofernan          #+#    #+#             */
/*   Updated: 2020/02/26 13:01:45 by rofernan         ###   ########.fr       */
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
# define ERR_CHEV "syntax error near unexpected token `"

extern int g_sig;

/*
**	TABS.C
*/
int			ft_tablength(char **s);
char		**ft_tabcopy(char **s, int fin);
void		h_split(t_shell *shell, char ***cmd);

/*
**	UTILS.C
*/
int			count_char(char *s, char c);
int			contain_c(char *s, char c);
int			is_chevron(char *str);
int			reste_arg(char **args, char *reste);
int			nb_arg(char **args, char *to_count);

/*
**	UTILS_2.C
*/
void		sig_handle_b(int s);
int			p(char **cmd, int *i);
int			nb_bs(const char *s, int f);

/*
**	SHELL_BODY.C
*/
void		shell_body(char *in, t_shell *shell);

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
**	INIT.C
*/
void		init_env(t_env **env);
void		init_name_prog(t_shell *shell, char *av);

/*
**	INIT_TABLE.C
*/
int			*fill_tab(const char *s);
int			**fill_tabf(char **s);

/*
**	ERROR.C
*/
void		disp_err(char *prog, char *cmd, char *arg, char *err);
int			chevron_error(char *prog, char *arg, char *cmd, char *end);
void		command_error(char *command, char *err);

/*
**	PATH.C
*/
void		prep_path(t_shell *shell, char **args);

/*
**	FT_*.C
*/
void		ft_echo(char **args);
void		ft_pwd(void);
void		ft_cd(t_shell *shell, char *arg);
void		ft_export(t_shell *shell, char **vars);
void		ft_unset(char **vars, t_env *env);
void		ft_env(t_env *env);
void		ft_exit(t_shell *shell, char **args);

/*
**	REDIRECTION.C
*/
int			test_syntax(t_shell *shell, char **args);
int			open_fd(t_shell *shell, char **args);
int			open_file(t_shell *shell);

/*
**	WRAP_CMP.C
*/
int			wrap_cmp(char *s, char c);
int			wrap_cmp_2(char *s, char *c);

/*
**	COPY_CLOSE_FD.C
*/
int			copy_stdinout(t_shell *shell);
void		close_stdinout(t_shell *shell);

/*
**	BUILTIN.C
*/
int			is_builtin(t_shell *shell, char **s);

/*
**	EXEC_COMMANDS.C
*/
char		**extract(char **args);
void		execute_cmd(char **cmd, t_shell *shell);

/*
**	FORKS.C
*/
void		fork_left(t_shell *shell, int *pdes);
void		fork_right(t_shell *shell, int *pdes, int i);

/*
**	FT_STDIN.C
*/
int		    exec_pipe(t_shell *shell, int i);
void		ft_stdin(t_shell *shell, char **command);

/*
**	FREE.C
*/
void		ft_free(char ***s);
int			del_war(char ***s, int i);
void		free_all(t_shell *shell);

/*
**	REV_CMD.C
*/
void		pop_word(char **s);
char		**ft_reverse(char **s);
void		trad(char **s, t_env *env);
void		sig_handle_c(int s);
int			*cp_add(int *t, int p);

/*
**	POP_WORD.C
*/
char		**wrap(int **tt, char **oo, char **out);
char		**finish_p(char **cmd, int **tab);
void		pop_char(char **s, int i, int c1, int c2);
void		init_pop_word(int *i, char *c, int *c1, int *c2);

/*
**	REPLACE.C
*/
int			replace(char **s, int d, t_env *env);
int			*finish_p_i(void);
void		finish_p_1(char **oo, int **tt, int *i, char **cmd);

/*
**	CHECK_QUOTES.C
*/
int			is_in_s(char *s, int m);
int			is_in_sd(const char *s, int m, int *tab);
char		*inv(char c);

/*
**	TRANSLATE.C
*/
void		ft_translate(char **s, int d, char **out, int *tab);

/*
**	SPLIT.C
*/
void		parsing(char *s, char **out, int *tab);
char		**split_cmd(char *s, int *tab);
int			end_name(char c, int i);

/*
**	WRAP_PARSING.C
*/
int			cd(char **cmd, int *i);
int			cg(char **cmd, int *i);
int			v(char **cmd, int *i);
char		re(char **cmd, int *i);

void		ft_p(char **s);

#endif
