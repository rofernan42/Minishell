#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <dirent.h>
#include "includes/minishell.h"
#include "libft/libft.h"
#include <signal.h>

void prep_0(t_shell *shell);

// void	ft_echo(int ac, char **av, t_shell *shell)
// {
// 	int i;

// 	i = 1;
// 	// printf("ECHO\n");
// 	// return;
// 	shell->str_echo = ft_strdup("");
// 	while (i < ac)
// 	{
// 		shell->str_echo = ft_strjoin_free(shell->str_echo, av[i], 1);
// 		if (i < ac - 1)
// 			shell->str_echo = ft_strjoin_free(shell->str_echo, " ", 1);
// 		i++;
// 	}
// 	ft_putendl_fd(shell->str_echo, 1);
// }

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

// void	del_args(t_shell *shell)
// {
// 	int i;

// 	i = 0;
// 	while (shell->args[i])
// 		ft_strdel(&shell->args[i++]);
// 	ft_strdel(&shell->args[i]);
// 	free(shell->args);
// 	shell->args = NULL;
// }

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
	create_env(env, "HOME", "/Users/rofernan");
	create_env(env, "PWD", getcwd(NULL, 0));
	create_env(env, "OLDPWD", getcwd(NULL, 0));
	create_env(env, "PATH", "/Users/augay/.brew/bin:/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/Applications/VMware Fusion.app/Contents/Public:/usr/local/mongodb/bin:/usr/local/munki:/Library/Frameworks/Mono.framework/Versions/Current/Commands");
}


int nb_bs(const char *s, int f)
{
	int i = f;
	while (f >= 0 && s[f] && s[f] == '\\')
	{
		f--;
	}
	//printf("NB bs = %i a %i sur [%s]\n",i-f,f,s);
	return (i - f);
}

void print_env(t_env *env)
{
	while (env != NULL)
	{
		printf("%s=%s\n", env->name, env->data);
		env = env->next;
	}
}

char *ft_concat(char *s1, char *s2)
{
	int i1 = ft_strlen(s1);
	int i2 = ft_strlen(s2);
	char *o = malloc(sizeof(char) * (i1 + i2 + 2));
	int i = 0;
	while (s1[i])
	{
		o[i] = s1[i];
		i++;
	}
	i2 = 0;
	//o[i] = '\n';
	//i++;
	while (s2[i2])
	{
		o[i + i2] = s2[i2];
		i2++;
	}
	o[i + i2] = '\0';
	free(s1);
	return (o);
}

int contain(char *s)
{
	int i = 0;
	while (s[i])
	{
		if (s[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

int is_in_s(char *s, int m)
{
	int i = 0;
	int std = 0;
	int deb;
	int sts = 0;
	while (s[i] && i < m)
	{
		if (!sts && !std && s[i] == '"' && nb_bs(s, i - 1) % 2 == 0)
		{
			std = 1;
			deb = i;
		}
		else if (!sts && std && s[i] == '"' && nb_bs(s, i - 1) % 2 == 0)
		{
			std = 0;
		}
		else if (!std && !sts && s[i] == '\'' && nb_bs(s, i - 1) % 2 == 0)
		{
			deb = i;
			sts = 1;
		}
		else if (!std && sts && s[i] == '\'' && nb_bs(s, i - 1) % 2 == 0)
		{
			sts = 0;
		}
		i++;
	}
	return (sts);
}

int is_in_sd(const char *s, int m, int *tab)
{
	//printf("s=%s, m=%i\n",s,m);
	int i = 0;
	int std = 0;
	int deb;
	int sts = 0;
	int state = 0;
	if (tab == NULL)
	{
		tab = malloc(sizeof(int) * 100);
		while (i < 100)
		{
			tab[i] = 0;
			i++;
		}
		i = 0;
		state = 1;
	}
	while (s[i] && i < m)
	{
		if (tab[i] == 0 && !sts && !std && s[i] == '"' && nb_bs(s, i - 1) % 2 == 0)
		{
			std = 1;
			deb = i;
		}
		else if (tab[i] == 0 && !sts && std && s[i] == '"' && nb_bs(s, i - 1) % 2 == 0)
		{
			std = 0;
		}
		else if (tab[i] == 0 && !std && !sts && s[i] == '\'' && nb_bs(s, i - 1) % 2 == 0)
		{
			deb = i;
			sts = 1;
		}
		else if (tab[i] == 0 && !std && sts && s[i] == '\'' && nb_bs(s, i - 1) % 2 == 0)
		{
			sts = 0;
		}
		i++;
	}
	if (state == 1)
	{
		free(tab);
	}
	return (sts + std);
}

void ft_translate(char **s, int d, int f, char **out, int *tab)
{
	int i = d;
	char *q;
	char *tmp = malloc(sizeof(char) * 2);
	tmp[1] = '\0';
	while (s[0][i] && s[0][i] != '\n')
	{
		if (is_in_s(s[0], i) == 0 && s[0][i] == '\\' && s[0][i + 1] && (s[0][i + 1] == '"' || s[0][i + 1] == '\\' || s[0][i + 1] == '$'))
		{
			i++;
			if (s[0][i] == '"')
			{
				tmp[0] = -1 * '"';
				out[0] = ft_concat(out[0], tmp);
			}
			else if (s[0][i] == '\\')
			{
				out[0] = ft_concat(out[0], "\\");
			}
			else if (s[0][i] == '$')
			{
				out[0] = ft_concat(out[0], "$");
			}
		}
		else if (is_in_sd(s[0], i, NULL) == 0 && s[0][i] == '\\' && s[0][i + 1] && (s[0][i + 1] == '\'' || s[0][i + 1] == '>' || s[0][i + 1] == '<' || s[0][i + 1] == '|'))
		{
			i++;
			if (s[0][i] == '\'')
			{
				tmp[0] = -1 * '\'';
				out[0] = ft_concat(out[0], tmp);
			}
			if (s[0][i] == '>')
				out[0] = ft_concat(out[0], ">");
			if (s[0][i] == '<')
				out[0] = ft_concat(out[0], "<");
			if (s[0][i] == '|')
				out[0] = ft_concat(out[0], "|");
			tab[ft_strlen(out[0]) - 1] = 1;
		}
		else
		{
			q = ft_substr(s[0], i, 1);
			out[0] = ft_concat(out[0], q);
			free(q);
		}
		i++;
	}
	free(tmp);
	return;
}

int quote(char *s, char **out, int *tab)
{
	int i = 0;
	int std = 0;
	int deb;
	int sts = 0;
	// while (s[i])
	// {
	// if (!sts && !std && s[i] == '"' && nb_bs(s, i - 1) % 2 == 0)
	// {
	// 	std = 1;
	// 	deb = i;
	// }
	// else if (!sts && std && s[i] == '"' && nb_bs(s, i - 1) % 2 == 0)
	// {
	// 	std = 0;
	// }
	// else if (!std && !sts && s[i] == '\'' && nb_bs(s, i - 1) % 2 == 0)
	// {
	// 	deb = i;
	// 	sts = 1;
	// }
	// else if (!std && sts && s[i] == '\'' && nb_bs(s, i - 1) % 2 == 0)
	// {
	// 	sts = 0;
	// }
	sts = is_in_sd(s, ft_strlen(s), tab);
	//	i++;
	//}
	ft_translate(&s, 0, i, out, tab);
	//printf("QUOTE=%s\n",s);
	//if (sts || std)
	//{
	//printf("error quote\n");
	//}
	return (0);
}

void parsing(char *s, char **out, int *tab)
{
	//printf("deb pars.\n");
	quote(s, out, tab);
}

void ft_p(char **s)
{
	int i = 0;
	while (s[i])
	{
		printf("s[%i]=[%s]\n", i, s[i]);
		//printf("BLOBLO\n");
		i++;
	}
}

static char **splitbody(int nbc, char const *s, char **out, int *tab)
{
	int i = 0;
	int j = 0;
	int k;

	k = 0;
	if (s[0] != ' ')
	{
		while (((s[i] && s[i] != ' ') || is_in_sd(s, i, tab) == 1))
			i++;
		out[k] = ft_substr(s, 0, i);
		k++;
	}
	while (s[i] && k < nbc)
	{
		j = 0;
		if ((i == 0 || ((s[i] == ' ') && is_in_sd(s, i, tab) == 0)))
			if (s[i + 1] != s[i])
			{
				//printf("TOT=%i et %i\n",i+1+j,(int)ft_strlen(s));
				while (s[i + 1 + j] && ((s[i + 1 + j] != ' ') || is_in_sd(s, i + 1 + j, tab) > 0))
					j++;
				out[k] = ft_substr(s, i + 1, j);
				k++;
			}
		i++;
	}
	return (out);
}

char **split_cmd(char *s, int *tab)
{
	int i;
	int nbc;
	char **out;

	if (s == NULL)
		return (NULL);
	i = 0;
	nbc = 0;
	if (s[0] && s[0] != ' ')
		nbc++;
	while (s[i] && s[i + 1])
	{
		//printf("2 CALL\n");
		if ((s[i] == ' ' && s[i + 1] != ' ') && is_in_sd(s, i, tab) == 0)
		{
			nbc++;
		}
		// else if (s[i] == ';' && is_in_sd(s, i, tab) == 0)
		// 	break;
		i++;
	}
	//printf("%d=nbc\n",nbc);
	out = malloc(sizeof(char *) * (nbc + 1));
	out[nbc] = 0;
	i = 0;
	out = splitbody(nbc, s, out, tab);
	return (out);
}

int end_name(char c, int i)
{
	if (i == 0)
		if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
			return (1);
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9') || c == '_')
		return (1);
	return (0);
}
// "fjsfjl \\\dsdljsdl" "'alalaa' \n \t \b "
int replace(char **s, int d, t_env *env, int *tab)
{
	int i = d;
	while (end_name(s[0][i], i) == 1)
	{
		i++;
	}
	//printf("s+d=%s\n",ft_substr(s[0], d, i-d));
	char *n = ft_substr(s[0], d, i - d);
	t_env *e1 = ft_envfind(env, n, ft_strcmp);
	//printf("NOTHERE\n");

	if (e1 == NULL)
	{
		//printf("NOT FIND [%s]\n", n);
		e1 = ft_envnew(n, "");
		//return(0);
	}
	//printf("FIND [%s]=[%s]\n", n, e1->data);
	int l1 = ft_strlen(s[0]);
	int l2 = ft_strlen(e1->data);
	int l3 = ft_strlen(e1->name);
	int lt = l1 + l2 - l3;
	char *out = malloc(sizeof(char) * lt);
	//printf("LT=%i\n", lt);
	out[lt - 1] = '\0';
	int j = 0;
	while (j < d - 1)
	{
		out[j] = s[0][j];
		j++;
	}
	int k = 0;
	while (e1->data[k])
	{
		out[j] = e1->data[k];
		if (out[j] == '"' || out[j] == '\'' || out[j] == '>' || out[j] == '<' || out[j] == '|')
		{
			tab[j] = 1;
			out[j] = -e1->data[k];
		}
		j++;
		k++;
	}
	//i++;
	int ret = j;
	while (s[0][i])
	{
		out[j] = s[0][i];
		j++;
		i++;
	}
	//printf("---RES---\n[%s]\n------\n", out);
	if (s[0] != NULL)
		free(s[0]);
	s[0] = out;
	//printf("d=%i, ldata=%i, lname=%i\n",d, (int)ft_strlen(e1->data), (int)ft_strlen(e1->name));
	//printf("ret = %i\n", (int)(d + (int)ft_strlen(e1->data)) - 1);
	free(n);
	return ((int)(d + (int)ft_strlen(e1->data)) - 1);
}

void trad(char **s, t_env *env, int *tab)
{
	int i = 0;
	//printf("i=%iS=%s\n",i,s[0]);
	while (s[0][i])
	{
		//printf("BLO\n");

		if (s[0][i] == '$' && nb_bs(s[0], i - 1) % 2 == 0 && is_in_s(s[0], i) == 0)
		{
			i = replace(s, i + 1, env, tab);
			if (i == 0)
			{
				s[0][0] = '\0';
				i = 0;
			}
			//if (s[0][0] == '\0')
			//printf("CEST 2\n");
			//printf("i=%i, s=[%s]\n", i, s[0]);
			i--;
		}
		i++;
		//printf("i=%iS=%s\n",i,s[0]);
	}
	//printf("i=%i, s=[%s]\n", i, s[0]);
}

int contain_c(char *s, char c)
{
	int i = 0;
	while (s[i])
	{
		if (c == s[i])
			return (1);
		i++;
	}
	return (0);
}

void ft_free(char **s)
{
	int i = 0;
	while (s[i])
	{
		free(s[i]);
		i++;
	}
	free(s);
}

void sig_handle_C(int s)
{
	write(1, "\nminishell$ ", 12);
}

void sig_handle_B(int s)
{
	write(1, "exit\n", 5);
	exit(0);
}

char **finish_p(char **cmd, int **tab)
{
	int i, j = 0;
	char **out;
	int nbc = 0;
	//tab[][] == 1 -> ignore | cmd[][] < 0 -> ignore et inverse
	while (cmd[i])
	{
		while (cmd[i][j])
		{
			if ((cmd[i][j] == '<' || (cmd[i][j] == '>' && cmd[i][j] != '>')) && tab[i][j] == 0 && is_in_sd(cmd[i], j, NULL) == 0)
			{
				if (j != 0)
					nbc++;
				if (cmd[i][j + 1] != '\0')
					nbc++;
			}
			j++;
		}
		j = 0;
		i++;
	}
	nbc += i;
	//printf("NBC FINAL = %i\n",nbc);
	out = malloc(sizeof(char *) * (nbc + 1));
	out[nbc] = 0;
	nbc = 0;
	i = 0;
	int p = 0;
	j = 0;
	char *oo = malloc(sizeof(char) * 1);
	oo[0] = '\0';
	int *tt = malloc(sizeof(int) * 100);
	while (j < 100)
	{
		tt[j] = 0;
		j++;
	}
	j = 0;
	char *tmp;
	while (cmd[i])
	{
		while (cmd[i][j])
		{
			if (tab[i][j] == 1 || (cmd[i][j] != '|' && cmd[i][j] != '>' && cmd[i][j] != '<' && cmd[i][j] != ';') || is_in_sd(cmd[i], j, tab[i]) == 1)
			{
				if (cmd[i][j] < 0 && cmd[i][j] != -1 * '"' && cmd[i][j] != -1 * '\'')
				{
					cmd[i][j] = -1 * cmd[i][j];
				}
				tmp = ft_substr(cmd[i], j, 1);
				oo = ft_concat(oo, tmp);
				free(tmp);
			}
			else
			{
				oo = ft_concat(oo, " ");
				tmp = ft_substr(cmd[i], j, 1);
				oo = ft_concat(oo, tmp);
				free(tmp);
				oo[ft_strlen(oo) - 1] = oo[ft_strlen(oo) - 1] * -1;
				//printf("d=%d\n",(int)ft_strlen(oo) - 1);
				tt[ft_strlen(oo) - 1] = -1;
				oo = ft_concat(oo, " ");
			}

			j++;
		}
		oo = ft_concat(oo, " ");
		i++;
		j = 0;
	}

	free(out);
	out = split_cmd(oo, tt);

	// ft_p(out);
	free(oo);
	//printf("OUT=[%s]\n",oo);
	free(tt);
	return (out);
}

void pop_char(char **s, int i, int c1, int c2)
{
	int j = 0;
	char *out = malloc(sizeof(char) * (ft_strlen(s[i]) - 1));
	out[ft_strlen(s[i]) - 2] = '\0';
	int k = 0;
	while (s[i][j])
	{
		if (j != c1 && j != c2)
		{
			out[k] = s[i][j];
			k++;
			j++;
		}
		else
		{
			j++;
		}
	}
	free(s[i]);
	s[i] = out;
	//printf("s[i]===%s\n",s[i]);
	//return (s);
	//printf("OUT=%s\n",out);
}

void pop_word(char **s)
{
	//printf("POP\n");
	int j = 0;
	int i = 0;
	int ch = 1;
	int deb;
	int fin;
	char c = 0;
	int c1 = 0;
	int c2 = 0;
	while (s[i])
	{
		//printf("si=%s\n",s[i]);
		while (s[i][j])
		{
			if (c == 0 && s[i][j] == '"')
			{
				c = '"';
				c1 = j;
			}
			else if (c == '"' && s[i][j] == '"')
			{
				c = 0;
				c2 = j;
				pop_char(s, i, c1, c2);
				j--;
				j--;
			}
			else if (c == 0 && s[i][j] == '\'')
			{
				c = '\'';
				c1 = j;
			}
			else if (c == '\'' && s[i][j] == '\'')
			{
				c = 0;
				c2 = j;
				pop_char(s, i, c1, c2);
				j--;
				j--;
			}
			j++;
		}
		j = 0;
		i++;
	}
	//ft_p(s);
	//return (s);
}

char **ft_reverse(char **s)
{
	int i = 0;
	int j = 0;
	while (s[i])
	{
		while (s[i][j])
		{
			if (s[i][j] < 0)
				s[i][j] = -1 * s[i][j];
			j++;
		}
		i++;
		j = 0;
	}
	//ft_p(s);
	return (s);
}

// void deal_cmd(char **c)
// {
// 	int i = 0;
// 	int j = 0;
// 	int fd;
// 	char *s = malloc(sizeof(char) * (2));
// 	s[0] = 'c';
// 	s[1] = '\0';
// 	char **t = malloc(sizeof(char *) * (2));
// 	t[0] = s;
// 	t[0] = 0;
// 	//printf("OPEN 1%s\n",c[i+1]);

// 	while (c[i] && i < 10)
// 	{
// 		//printf("OPEN 2%s\n", c[i + 1]);

	
// 		if (c[i][0] == (-1 * '<') && c[i][1] == '\0')
// 		{
// 			//printf("OPEN 3%s\n", c[i + 1]);
// 			// int s1 = dup(1);
// 			// int s0 = dup(0);
// 			//dup2(fd, 0);
// 			//dup2(1, fd);
// 			if (fork() == 0)
// 			{
// 				fd = open(c[i + 1], O_RDWR);
// 				dup2(fd, 1);
// 				//execve("/bin/cat", t, NULL);
// 				write(1, "bonjour\n", 8);
// 				exit(0);
// 				//close(fd);
// 				//close(1);
// 				//close(fd);
// 				//close(0);
// 			}
// 			else
// 			{
// 			wait(NULL);
// 			// dup2(s0,0);
// 			// dup2(s1,1);
// 			// close(s0);
// 			// close(s1);
// 			// close(fd);
// 			}
// 		}
// 		i++;
// 	}
// }

int deal_cmd(t_shell *shell)
{
	char	buffer[BUF_SIZE + 1];
	int		ret;
	int		i;

	// t_env	*env;
	//ft_p(shell->args);
	// init_env(&env);
	//ft_putstr_fd("\033[33mminishell$\033[0m ", 1);
	
			//shell.args = ft_split(shell.command, ' ');
			//shell.args[0] = ft_strlow(shell.args[0]);
			//shell.args = s;
			//ft_p(shell.args);
			//layout_args(&shell);
			i = count_args(shell->args);
			open_fd(shell);

			shell->stdout_cpy = dup(1);
			close(1);
			dup2(shell->fd_out, 1);
			close(0);
			dup2(shell->fd_in, 0);
			//printf("TEST\n");
			//write(1,"QQ", 2);
			//ft_p(shell.args);
			//ft_p(shell->args);
			if (!ft_strcmp(shell->args[0], "echo"))
				ft_echo(shell);
			else if (!ft_strncmp(shell->args[0], "cd", 2))
				ft_cd(shell->args[1], shell->env);
			else if (!ft_strcmp(shell->args[0], "pwd"))
				ft_pwd(shell->env);
			else if (!ft_strcmp(shell->args[0], "export"))
				ft_export(&shell->args[1], shell->env);
			else if (!ft_strcmp(shell->args[0], "unset"))
				ft_unset(&shell->args[1], shell->env);
			else if (!ft_strcmp(shell->args[0], "env"))
				ft_env(shell->env);
			else if (!ft_strcmp(shell->args[0], "exit"))
				exit(0);
			else
			{
				//printf("PREV\n");
				//ft_p(shell->args);
				prep_0(shell);
				//printf("LAST\n");
				//ft_p(shell->args);
				if (fork() == 0)
					execve(shell->args[0], shell->args, NULL);
				else
					wait(NULL);
			}
			//close(shell.fd);
			dup2(shell->stdout_cpy, 1);
			close(shell->stdout_cpy);
			
			//free(shell.command);
			//shell.command = ft_strdup("");
			//del_args(&shell);
			//ft_putstr_fd("\033[33mminishell$\033[0m ", 1);
		
		// if (ret == 0)
		// {
		// 	ft_putendl_fd("exit", 1);
		// 	system("leaks a.out");
		// 	exit(1);
		// }
	return (0);
}

int count_p(char *s)
{
	int i = 0;
	int so = 0;
	while(s[i])
	{
		if (s[i] == ':')
			so += 1;
		i++;
	}
	return (so);
}

void prep_0(t_shell *shell)
{
	char **s;
	t_env *e1 = ft_envfind(shell->env, "PATH", ft_strcmp);
	if (e1 == NULL)
	{
		write(1, "not found\n", 10);
		return ;
	}
	s = ft_split(e1->data, ':');
	//printf("INSIDE\n");
	//ft_p(shell->args);
	int i = 0;
	char *tmp;
	struct stat a;
	int f = 0;
	int k = 0;
	while(s[i])
	{
		tmp = ft_concat(s[i], "/");
		tmp = ft_concat(tmp, shell->args[0]);
		//printf("FOUND HERE=%s\n",tmp);
		if ((k = stat(tmp, &a)) == 0)
		{
			//perror("stat");
			//printf("K=%i\n",k);
			f = 1;
			break;
		}
					//perror("stat");

					//printf("K=%i\n",k);

		i++;
	}
	if (f == 1)
	{
		//printf("FOUND HERE=%s\n",tmp);
		//free((shell->args[0]));
		// if (shell->command != NULL)
		// 	free(shell->command);
		//printf("shell=%s\n",shell->args[0]);
		free(shell->args[0]);
		shell->args[0] = ft_strdup(tmp);
		//ft_p(shell->args);
		free(tmp);
	}
	else
	{
		printf("NOT FOUND\n");
	}
	
}


int main(int ac, char **av)
{
	signal(SIGINT, sig_handle_C);
	signal(SIGQUIT, sig_handle_B);
	write(1, "minishell$ ", 11);
	// t_env *e1 = ft_envnew("PWD", "/home");
	// t_env *e2 = ft_envnew("ENV", "ba\"sh");
	// t_env *e3 = ft_envnew("ZSH", "/te\'st/zsh");
	// t_env *e4 = ft_envnew("LOGNAME", "aug><><ay");
	// t_env *e5 = ft_envnew("TERM", "xterm");
	int *tab = malloc(sizeof(int) * 100);
	t_env	*env;
	//ft_p(s);
	t_shell shell;
	init_env(&env);
	int cpt = 0;
	shell.env = env;
	while (cpt < 100)
	{
		tab[cpt] = 0;
		cpt++;
	}
	int **tabf = malloc(sizeof(int *) * 10);
	cpt = 0;
	int cpt2 = 0;
	while (cpt < 10)
	{
		tabf[cpt] = malloc(sizeof(int) * 100);
		while (cpt2 < 100)
		{
			tabf[cpt][cpt2] = 0;
			cpt2++;
		}
		cpt2 = 0;
		cpt++;
	}
	// ft_envadd_back(&e1, e2);
	// ft_envadd_back(&e1, e3);
	// ft_envadd_back(&e1, e4);
	// ft_envadd_back(&e1, e5);
	//print_env(shell.env);
	int i = 0;
	char *s = malloc(sizeof(char) * 11);
	char *full = malloc(sizeof(char) * 1);
	char **cmd;
	full[0] = '\0';
	env = malloc(sizeof(t_env));
	int fin = 0;
	char *sp;
	char **def;
	while (1)
	{
		i = read(0, s, 10);
		s[i] = 0;
		full = ft_concat(full, s);
		if (contain(full))
		{
			full[ft_strlen(full) - 1] = '\0';
			if (full[0] != '\0')
			{
				trad(&full, shell.env, tab);
				//printf("FUL=%s\n",full);
				cmd = split_cmd(full, tab);
				//ft_p(cmd);
				//printf("FUL=%s\n",full);
				while (cmd[fin])
				{
					//printf("deb pars=%s\n",cmd[fin]);
					sp = ft_strdup(cmd[fin]);
					free(cmd[fin]);
					cmd[fin] = NULL;
					cmd[fin] = malloc(sizeof(char) * 100);
					memset(cmd[fin], 0, 100);
					parsing(sp, &(cmd[fin]), tabf[fin]);
					//printf("res pars=%s\nav=%s\n", cmd[fin], sp);
					free(sp);
					fin++;
				}
				def = finish_p(cmd, tabf);
				//ft_p(def);
				pop_word(def);
				ft_reverse(def);
				//ft_p(def);
				// use def;
				//printf("S1===%s\n",def[1]);
				shell.args = def;
				//ft_p(shell.args);
				//deal_cmd(&shell);
				ft_stdin(&shell);
				//ft_free(def);
				def = NULL;
				write(1, "minishell$ ", 11);
				ft_free(cmd);
				fin = 0;
				cmd = NULL;
			}
			free(full);
			full = malloc(sizeof(char) * 1);
			full[0] = '\0';
		}
		else if (i == 0)
		{
			// free(s);
			// free(tab);
			// i = 0;
			// while (i < 10)
			// {
			// 	free(tabf[i]);
			// 	i++;
			// }
			// free(tabf);
			// //system("leaks parsing");
			// exit(1);
		}
	}
	return (0);
}