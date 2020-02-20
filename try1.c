#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <dirent.h>
#include "includes/minishell.h"
#include "libft/libft.h"
#include <signal.h>

int main()
{
	signal(SIGINT, sig_handle_c);
	signal(SIGQUIT, sig_handle_b);
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
		full = ft_strjoin_free(full, s, 1);
		if (contain_c(full, '\n'))
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
					ft_memset(cmd[fin], 0, 100);
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
				fin = ft_tablength(def);
				while (part <= fin)
				{
					if (part == fin || !ft_strcmp(def[part], ";"))
					{
						//ft_p(def);
						//////printf("last=%i, part=%i, fin=%i\n",last_part,part, fin);
						ft_stdin(&shell,ft_tabcopy(def + last_part, part - last_part));
						last_part = part + 1;
					}
					part++;
				}
				part = 0;
				last_part = 0;
				shell.args = def;
				//ft_stdin(&shell);
				def = NULL;
				del_args(cmd);
				fin = 0;
				cmd = NULL;
				// ft_putstr_fd("\033[33mminishell$\033[0m ", 1);
			}
			free(full);
			full = malloc(sizeof(char) * 1);
			full[0] = '\0';
		}
		else if (i == 0)
		{
			ft_putendl_fd("exit", 2);
			exit(0);
		}

	}
	return (0);
}
