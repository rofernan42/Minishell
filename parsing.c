/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofernan <rofernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 17:19:06 by rofernan          #+#    #+#             */
/*   Updated: 2020/02/17 18:58:19 by rofernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

int nb_bs(const char *s, int f)
{
	int i = f;
	while (f >= 0 && s[f] && s[f] == '\\')
		f--;
	return (i - f);
}

int	check_char(char *s, char c)
{
	int i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int is_in_s(char *s, int m)
{
	int i;
	int std;
	int sts;

	i = 0;
	std = 0;
	sts = 0;
	while (s[i] && i < m)
	{
		if (!sts && !std && s[i] == '"' && nb_bs(s, i - 1) % 2 == 0)
			std = 1;
		else if (!sts && std && s[i] == '"' && nb_bs(s, i - 1) % 2 == 0)
			std = 0;
		else if (!std && !sts && s[i] == '\'' && nb_bs(s, i - 1) % 2 == 0)
			sts = 1;
		else if (!std && sts && s[i] == '\'' && nb_bs(s, i - 1) % 2 == 0)
			sts = 0;
		i++;
	}
	return (sts);
}

int is_in_sd(const char *s, int m, int *tab)
{
	int i;
	int std;
	int sts;
	int state;

	i = 0;
	std = 0;
	sts = 0;
	state = 0;
	if (tab == NULL)
	{
		tab = ft_calloc(sizeof(int), 100);
		state = 1;
	}
	while (s[i] && i < m)
	{
		if (tab[i] == 0 && !sts && !std && s[i] == '"' \
		&& nb_bs(s, i - 1) % 2 == 0)
			std = 1;
		else if (tab[i] == 0 && !sts && std && s[i] == '"' \
		&& nb_bs(s, i - 1) % 2 == 0)
			std = 0;
		else if (tab[i] == 0 && !std && !sts && s[i] == '\'' \
		&& nb_bs(s, i - 1) % 2 == 0)
			sts = 1;
		else if (tab[i] == 0 && !std && sts && s[i] == '\'' \
		&& nb_bs(s, i - 1) % 2 == 0)
			sts = 0;
		i++;
	}
	if (state == 1)
		free(tab);
	return (sts + std);
}

void ft_translate(char **s, char **out, int *tab)
{
	int		i;
	char	*q;
	char	tmp[2];

	i = 0;
	tmp[1] = '\0';
	while (s[0][i] && s[0][i] != '\n')
	{
		if (is_in_s(s[0], i) == 0 && s[0][i] == '\\' && s[0][i + 1] \
		&& (s[0][i + 1] == '"' || s[0][i + 1] == '\\' || s[0][i + 1] == '$'))
		{
			i++;
			if (s[0][i] == '"')
			{
				tmp[0] = -1 * '"';
				out[0] = ft_strjoin_free(out[0], tmp, 1);
			}
			else if (s[0][i] == '\\')
				out[0] = ft_strjoin_free(out[0], "\\", 1);
			else if (s[0][i] == '$')
				out[0] = ft_strjoin_free(out[0], "$", 1);
		}
		else if (is_in_sd(s[0], i, NULL) == 0 && s[0][i] == '\\' \
		&& s[0][i + 1] && (s[0][i + 1] == '\'' || s[0][i + 1] == '>' \
		|| s[0][i + 1] == '<' || s[0][i + 1] == '|'))
		{
			i++;
			if (s[0][i] == '\'')
			{
				tmp[0] = -1 * '\'';
				out[0] = ft_strjoin_free(out[0], tmp, 1);
			}
			if (s[0][i] == '>')
				out[0] = ft_strjoin_free(out[0], ">", 1);
			if (s[0][i] == '<')
				out[0] = ft_strjoin_free(out[0], "<", 1);
			if (s[0][i] == '|')
				out[0] = ft_strjoin_free(out[0], "|", 1);
			tab[ft_strlen(out[0]) - 1] = 1;
		}
		else
		{
			q = ft_substr(s[0], i, 1);
			out[0] = ft_strjoin_free(out[0], q, 1);
			free(q);
		}
		i++;
	}
	return;
}

void parsing(char *s, char **out, int *tab)
{
	ft_translate(&s, out, tab);
}

void ft_p(char **s)
{
	int i = 0;
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
				while (s[i + 1 + j] && ((s[i + 1 + j] != ' ') \
				|| is_in_sd(s, i + 1 + j, tab) > 0))
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
			nbc++;
		// else if (s[i] == ';' && is_in_sd(s, i, tab) == 0)
		// 	break;
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
		if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
			return (1);
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9') || c == '_')
		return (1);
	return (0);
}

int replace(char **s, int d, t_env *env, int *tab)
{
	int i = d;
	while (end_name(s[0][i], i) == 1)
	{
		i++;
	}
	char *n = ft_substr(s[0], d, i - d);
	t_env *e1 = ft_envfind(env, n, ft_strcmp);
	if (e1 == NULL)
		e1 = ft_envnew(n, "");
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
	if (s[0] != NULL)
		free(s[0]);
	s[0] = out;
	free(n);
	return ((int)(d + (int)ft_strlen(e1->data)) - 1);
}

void trad(char **s, t_env *env, int *tab)
{
	int i = 0;
	while (s[0][i])
	{
		if (s[0][i] == '$' && nb_bs(s[0], i - 1) % 2 == 0 && is_in_s(s[0], i) == 0)
		{
			i = replace(s, i + 1, env, tab);
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
	ft_putstr_fd("\033[33mminishell$\033[0m ", 1);
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
				oo = ft_strjoin_free(oo, tmp, 1);
				free(tmp);
			}
			else
			{
				oo = ft_strjoin_free(oo, " ", 1);
				tmp = ft_substr(cmd[i], j, 1);
				oo = ft_strjoin_free(oo, tmp, 1);
				free(tmp);
				oo[ft_strlen(oo) - 1] = oo[ft_strlen(oo) - 1] * -1;
				tt[ft_strlen(oo) - 1] = -1;
				oo = ft_strjoin_free(oo, " ", 1);
			}

			j++;
		}
		oo = ft_strjoin_free(oo, " ", 1);
		i++;
		j = 0;
	}

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

int main(int ac, char **av)
{
	signal(SIGINT, sig_handle_C);
	signal(SIGQUIT, sig_handle_B);
	t_env *e1 = ft_envnew("PWD", "/home");
	t_env *e2 = ft_envnew("ENV", "ba\"sh");
	t_env *e3 = ft_envnew("ZSH", "/te\'st/zsh");
	t_env *e4 = ft_envnew("LOGNAME", "aug><><ay");
	t_env *e5 = ft_envnew("TERM", "xterm");
	int *tab = malloc(sizeof(int) * 100);
	int cpt = 0;
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
	ft_envadd_back(&e1, e2);
	ft_envadd_back(&e1, e3);
	ft_envadd_back(&e1, e4);
	ft_envadd_back(&e1, e5);
	int i = 0;
	char *s = malloc(sizeof(char) * 11);
	char *full = malloc(sizeof(char) * 1);
	char **cmd;
	full[0] = '\0';
	t_env *env;
	env = malloc(sizeof(t_env));
	int fin = 0;
	char *sp;
	char **def;
	while (1)
	{
		i = read(0, s, 10);
		s[i] = 0;
		full = ft_strjoin_free(full, s, 1);
		if (check_char(full, '\n'))
		{
			full[ft_strlen(full) - 1] = '\0';
			if (full[0] != '\0')
			{
				trad(&full, e1, tab);
				cmd = split_cmd(full, tab);
				while (cmd[fin])
				{
					sp = ft_strdup(cmd[fin]);
					free(cmd[fin]);
					cmd[fin] = NULL;
					cmd[fin] = malloc(sizeof(char) * 100);
					memset(cmd[fin], 0, 100);
					parsing(sp, &(cmd[fin]), tabf[fin]);
					free(sp);
					fin++;
				}
				def = finish_p(cmd, tabf);
				pop_word(def);
				ft_reverse(def);
				//ft_p(def);
				ft_free(def);
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
			free(s);
			free(tab);
			i = 0;
			while (i < 10)
			{
				free(tabf[i]);
				i++;
			}
			free(tabf);
			system("leaks a.out");
			exit(1);
		}
	}
	return (0);
}
