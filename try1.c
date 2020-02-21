#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <dirent.h>
#include "includes/minishell.h"
#include "libft/libft.h"
#include <signal.h>

void ft_write(int fd, char *s, int l)
{
	int i = 0;
	while(i < l)
	{
		printf("s[%i]=[%i]\n",i, (int)s[i]);
		i++;
	}
}

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
	int state = 0;
	while (1)
	{
		memset(s, 0, 10);
		i = read(0, s, 10);
		//printf("read=%i\n",(int)ft_strlen(s));
		//ft_write(1, s, 12);
		if (ft_strlen(s) != 0 && s[ft_strlen(s) - 1] != '\n')
		{	
			state = 1;
		//	printf("CTRLD FAIT RIEN\n");
		}
		s[i] = 0;
		full = ft_strjoin_free(full, s, 1);
		//write(1, s, 50);
		// if (contain_c(full, '\n') == 0)
		// 	state = 1;
		if (contain_c(full, '\n'))
		{
			full[ft_strlen(full) - 1] = '\0';
			if (full[0] != '\0')
			{
				trad(&full, shell.env);
				tab = fill_tab(full);
				cmd = split_cmd(full, tab);
				tabf = fill_tabf(cmd);
				while (cmd[fin])
				{
					sp = ft_strdup(cmd[fin]);
					free(cmd[fin]);
					cmd[fin] = NULL;
					cmd[fin] = malloc(sizeof(char) * 100);
					ft_memset(cmd[fin], 0, 100);
					parsing(sp, &(cmd[fin]), tabf[fin]);
					free(sp);
					fin++;
				}
				def = finish_p(cmd, tabf);
				pop_word(def);
				ft_reverse(def);
				fin = ft_tablength(def);
				while (part <= fin)
				{
					if (part == fin || !ft_strcmp(def[part], ";"))
					{
						ft_stdin(&shell,ft_tabcopy(def + last_part, part - last_part));
						last_part = part + 1;
					}
					part++;
				}
				part = 0;
				last_part = 0;
				shell.args = def;
				def = NULL;
				del_args(cmd);
				fin = 0;
				cmd = NULL;
			}
			else
			{
				ft_putstr_fd("\033[33mminishell$\033[0m ", 1);
			}
			
			free(full);
			full = malloc(sizeof(char) * 1);
			full[0] = '\0';
			state = 0;
		}
		else if (state == 0)
		{		//printf("state=%i\n",state);

			ft_putendl_fd("exit", 2);
			exit(0);
		}
	}
	return (0);
}
