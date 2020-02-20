#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <dirent.h>
#include "includes/minishell.h"
#include "libft/libft.h"
#include <signal.h>
int *fill_tab(const char *s);

void prep_0(t_shell *shell);


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
		////printf("%s=%s\n", env->name, env->data);
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

int		contain(char *s)
{
	int i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

int		is_in_s(char *s, int m)
{
	int i;
	int std;
	int deb;
	int sts;

	i = -1;
	std = 0;
	sts = 0;
	while (s[++i] && i < m)
		if (!sts && !std && s[i] == '"' && nb_bs(s, i - 1) % 2 == 0)
		{
			std = 1;
			deb = i;
		}
		else if (!sts && std && s[i] == '"' && nb_bs(s, i - 1) % 2 == 0)
			std = 0;
		else if (!std && !sts && s[i] == '\'' && nb_bs(s, i - 1) % 2 == 0)
		{
			deb = i;
			sts = 1;
		}
		else if (!std && sts && s[i] == '\'' && nb_bs(s, i - 1) % 2 == 0)
			sts = 0;
	return (sts);
}

int		is_in_sd(const char *s, int m, int *tab)
{
	int i;
	int std;
	int deb;
	int sts;
	int state;

	i = 0;
	std = 0;
	sts = 0;
	state = 0;
	if (tab == NULL && (state = 1))
		tab = fill_tab(s);
	while (s[i] && i < m)
	{
		if (tab[i] == 0 && !sts && !std && s[i] == '"' &&
		nb_bs(s, i - 1) % 2 == 0)
		{
			std = 1;
			deb = i;
		}
		else if (tab[i] == 0 && !sts && std && s[i] == '"' &&
		nb_bs(s, i - 1) % 2 == 0)
			std = 0;
		else if (tab[i] == 0 && !std && !sts && s[i] == '\'' &&
		nb_bs(s, i - 1) % 2 == 0)
		{
			deb = i;
			sts = 1;
		}
		else if (tab[i] == 0 && !std && sts && s[i] == '\'' &&
		nb_bs(s, i - 1) % 2 == 0)
			sts = 0;
		i++;
	}
	if (state == 1)
		free(tab);
	return (sts + std);
}

void	ft_translate(char **s, int d, int f, char **out, int *tab)
{
	int		i;
	char	*q;
	char	*tmp;
	//printf("s=%s\n",s[0]);
	//ft_p(s);
	tmp = malloc(sizeof(char) * 2);
	i = d;
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
				out[0] = ft_concat(out[0], "\\");
			else if (s[0][i] == '$')
				out[0] = ft_concat(out[0], "$");
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
	//printf("out=%s\n",out[0]);
	return;
}

int quote(char *s, char **out, int *tab)
{
	int i = 0;
	int std = 0;
	int deb;
	int sts = 0;
	sts = is_in_sd(s, ft_strlen(s), tab);
	ft_translate(&s, 0, i, out, tab);
	return (0);
}

void parsing(char *s, char **out, int *tab)
{
	quote(s, out, tab);
}

void ft_p(char **s)
{
	int i = 0;
	if (s == NULL)
	{
		return ;
	}
	while (s[i])
	{
		printf("s[%i]=[%s]\n", i, s[i]);
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
		if ((s[i] == ' ' && s[i + 1] != ' ') && is_in_sd(s, i, tab) == 0)
		{
			nbc++;
		}
		i++;
	}
	out = malloc(sizeof(char *) * (nbc + 1));
	out[nbc] = 0;
	i = 0;
	out = splitbody(nbc, s, out, tab);
	return (out);
}

int end_name(char c, int i)
{
	if (i == 0)
		if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '?')
			return (1);
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9') || c == '_' || c == '?')
		return (1);
	return (0);
}
int replace(char **s, int d, t_env *env)
{
	int i = d;
	while (end_name(s[0][i], i) == 1)
	{
		i++;
	}
	char *n = ft_substr(s[0], d, i - d);
	//////printf("LABEL=%s\n",n);
	t_env *e1 = ft_envfind(env, n, ft_strcmp);

	if (e1 == NULL)
	{
		e1 = ft_envnew(n, "");
	}
	//////printf("e1=%s\n", e1->data);
	int l1 = ft_strlen(s[0]);
	int l2 = ft_strlen(e1->data);
	int l3 = ft_strlen(e1->name);
	int lt = l1 + l2 - l3;
	char *out = malloc(sizeof(char) * lt);
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
			out[j] = -e1->data[k];
		}
		j++;
		k++;
	}
	int ret = j;
	while (s[0][i])
	{
		out[j] = s[0][i];
		j++;
		i++;
	}
	if (s[0] != NULL)
		free(s[0]);
	s[0] = out;
	free(n);
	return ((int)(d + (int)ft_strlen(e1->data)) - 1);
}

void trad(char **s, t_env *env)
{
	int i = 0;
	while (s[0][i])
	{

		if (s[0][i] == '$' && nb_bs(s[0], i - 1) % 2 == 0 && is_in_s(s[0], i) == 0)
		{
			i = replace(s, i + 1, env);
			if (i == 0)
			{
				s[0][0] = '\0';
				i = 0;
			}
			i--;
		}
		i++;
	}
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
	//printf("SIG=%i\n",s);
	ft_putstr_fd("\n\033[33mminishell$\033[0m ", 1);
}

void sig_handle_B(int s)
{
	// write(1, "exit\n", 5);
	// exit(0);
}

int *cp_add(int *t, int p)
{
	int i = 0;
	int *o = malloc(sizeof(int) * (p+1));
	o[p] = -8;
	while(t[i] != -8)
	{
		o[i] = t[i];
		i++;
	}
	while(o[i] != -8)
	{
		o[i] = 0;
		i++;
	}
	free(t);
	return (o);
}

char **finish_p(char **cmd, int **tab)
{
	int i, j = 0;
	char **out;
	int nbc = 0;
	int l = 1;
	if (cmd == NULL)
		return(NULL);
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
	out = malloc(sizeof(char *) * (nbc + 1));
	out[nbc] = 0;
	nbc = 0;
	i = 0;
	int p = 0;
	j = 0;
	char *oo = malloc(sizeof(char) * 1);
	oo[0] = '\0';
	int *tt = malloc(sizeof(int) * 1);
	tt[0] = -8;
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
				if (cmd[i][j+1] == '>')
				{
					oo[ft_strlen(oo) - 1] = oo[ft_strlen(oo) - 1] * -1;
					tt = cp_add(tt, ft_strlen(oo));
					tt[ft_strlen(oo) - 1] = -1;
					oo = ft_concat(oo, ">");
					j++;
				}
				free(tmp);
				oo[ft_strlen(oo) - 1] = oo[ft_strlen(oo) - 1] * -1;
				tt = cp_add(tt, ft_strlen(oo));
				tt[ft_strlen(oo) - 1] = -1;
				oo = ft_concat(oo, " ");
			}

			j++;
		}
		oo = ft_concat(oo, " ");
		i++;
		j = 0;
	}

	tt = cp_add(tt, ft_strlen(oo));
	free(out);
	out = split_cmd(oo, tt);

	free(oo);
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
}

void pop_word(char **s)
{
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
	return (s);
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
	int i = 0;
	char *tmp;
	struct stat a;
	int f = 0;
	int k = 0;
	if (stat(shell->args[0], &a) == 0)
	{
		return;
	}
	while(s[i])
	{
		tmp = ft_concat(s[i], "/");
		tmp = ft_concat(tmp, shell->args[0]);
		if ((k = stat(tmp, &a)) == 0)
		{
			f = 1;
			break;
		}

		i++;
	}
	if (f == 1)
	{
		free(shell->args[0]);
		shell->args[0] = ft_strdup(tmp);
		free(tmp);
	}
	else
	{
		////printf("NOT FOUND\n");
	}
	
}

char **ft_copy(char **s, int fin)
{
	//////printf("FT_COPY\n");
	//ft_p(s);
	int i;
	char **o;

	i = 0;
	while(s[i] && i < fin)
		i++;
	o = malloc(sizeof(char*) * (i + 1));
	o[i] = 0;
	i = 0;
	while (s[i] && i < fin)
	{
		o[i] = ft_strdup(s[i]);
		i++;
	}
	//ft_p(o);
	//////printf("FIN\n");
	return (o);
}

int ft_long(char **s)
{
	int i;

	i = 0;
	if (s == NULL)
		return (0);
	while(s[i])
		i++;
	return (i);
}

int *fill_tab(const char *s)
{
	int l = ft_strlen(s);
	int *o = malloc(sizeof(int) * (l));
	int i = 0;
	while(i < l)
	{
		o[i] = 0;
		if (s[i] < 0)
			o[i] = 1;
		i++;
	}
	return (o);
}

int **fill_tabf(char **s)
{
	int i = 0;
	int j = 0;
	int **o;
	while(s[i])
	{
		i++;
	}

	o = malloc(sizeof(int*) * i);
	i = 0;
	while(s[i])
	{
		while(s[i][j])
		{
			j++;
		}
		o[i] = malloc(sizeof(int) * j);
		memset(o[i], 0, sizeof(int) * j);
		i++;
		j = 0;
	}
	return (o);
}

int main(int ac, char **av)
{
	signal(SIGINT, sig_handle_C);
	signal(SIGQUIT, sig_handle_B);
	int *tab;
	ft_putstr_fd("\033[33mminishell$\033[0m ", 1);
	t_env	*env;
	t_shell shell;
	init_env(&env);
	int cpt = 0;
	shell.env = env;
	int **tabf = malloc(sizeof(int *) * 10);
	cpt = 0;
	int i = 0;
	char *s = malloc(sizeof(char) * 11);
	char *full = malloc(sizeof(char) * 1);
	char **cmd;
	full[0] = '\0';
	env = malloc(sizeof(t_env));
	int fin = 0;
	char *sp;
	char **def;
	int part = 0;
	int last_part = 0;
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
				trad(&full, shell.env);
				//init tab -char
				tab = fill_tab(full);
				cmd = split_cmd(full, tab);
				tabf = fill_tabf(cmd);
				//printf("CMD\n");
				//ft_p(cmd);
				while (cmd[fin])
				{
					sp = ft_strdup(cmd[fin]);
					free(cmd[fin]);
					cmd[fin] = NULL;
					cmd[fin] = malloc(sizeof(char) * 100);
					memset(cmd[fin], 0, 100);
					//printf("pars=%s et in=%i\n",sp,fin);
					parsing(sp, &(cmd[fin]), tabf[fin]);
					//printf("cmd[%i]=%s\n",fin,cmd[fin]);
					free(sp);
					fin++;
				}
				//ft_p(cmd);
				def = finish_p(cmd, tabf);
				pop_word(def);
				ft_reverse(def);
				//ft_p(def);
				fin = ft_long(def);
				while(part <= fin)
				{
					if (part == fin || !strcmp(def[part], ";"))
					{
						//ft_p(def);
						//////printf("last=%i, part=%i, fin=%i\n",last_part,part, fin);
						ft_stdin(&shell,ft_copy(def + last_part, part - last_part));
						last_part = part + 1;
					}
					part++;
				}
				part = 0;
				last_part = 0;
				shell.args = def;
				//ft_stdin(&shell);
				def = NULL;
				ft_free(cmd);
				fin = 0;
				cmd = NULL;
				//ft_putstr_fd("\033[33mminishell$\033[0m ", 1);
			}
			free(full);
			full = malloc(sizeof(char) * 1);
			full[0] = '\0';
		}
		else if (i == 0)
		{
			write(1, "exit\n", 5);
			exit(0);
		}

	}
	return (0);
}