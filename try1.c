#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <dirent.h>
#include "includes/minishell.h"
#include "libft/libft.h"
#include <signal.h>

void	shell_body_3(char **cmdf, int *tabf)
{
	char *sp;

	sp = ft_strdup(cmdf[0]);
	free(cmdf[0]);
	cmdf[0] = NULL;
	cmdf[0] = malloc(sizeof(char) * 100);
	ft_memset(cmdf[0], 0, 100);
	parsing(sp, &(cmdf[0]), tabf);
	free(sp);
}

void	shell_body_4(char ***cmd, t_shell *shell)
{
	int fin;
	int part;
	int last_part;

	fin = 0;
	part = 0;
	last_part = 0;
	fin = ft_tablength(cmd[0]);
	while (part <= fin)
	{
		if (part == fin || !ft_strcmp(cmd[0][part], ";"))
		{
			ft_stdin(shell, ft_tabcopy(cmd[0] + last_part, part - last_part));
			last_part = part + 1;
		}
		part++;
	}
	part = 0;
	last_part = 0;
	del_args(cmd[0]);
	fin = 0;
}

void	shell_body_2(t_shell *shell, char *full)
{
	int		fin;
	int		*tab;
	char	**cmd;
	int		**tabf;

	fin = 0;
	tab = fill_tab(full);
	cmd = split_cmd(full, tab);
	tabf = fill_tabf(cmd);
	while (cmd[fin])
	{
		shell_body_3(&cmd[fin], tabf[fin]);
		fin++;
	}
	cmd = finish_p(cmd, tabf);
	pop_word(cmd);
	ft_reverse(cmd);
	shell_body_4(&cmd, shell);
}

void	shell_body(char *in, t_shell *shell)
{
	char *full;

	full = ft_strdup(in);
	full[ft_strlen(full) - 1] = '\0';
	if (full[0] != '\0')
	{
		trad(&full, shell->env);
		shell_body_2(shell, full);
	}
	else
		ft_putstr_fd("\033[33mminishell$\033[0m ", 1);
}

int		init_main(t_shell *shell, char **s, char **full)
{
	t_env *env;

	init_env(&env);
	shell->env = env;
	s[0] = malloc(sizeof(char) * 11);
	full[0] = malloc(sizeof(char) * 1);
	signal(SIGINT, sig_handle_c);
	signal(SIGQUIT, sig_handle_b);
	ft_putstr_fd("\033[33mminishell$\033[0m ", 1);
	if (s[0] == NULL || full[0] == NULL)
		exit(1);
	full[0][0] = '\0';
	return (0);
}

void	ft_reset(char **full)
{
	free(full[0]);
	full[0] = NULL;
	full[0] = malloc(sizeof(char) * 1);
	full[0][0] = '\0';
}

int		print_exit(void)
{
	ft_putendl_fd("exit", 2);
	return (0);
}

int		main(void)
{
	t_shell	shell;
	int		i;
	char	*s;
	char	*full;
	int		state;

	state = init_main(&shell, &s, &full);
	while (1)
	{
		i = read(0, s, 10);
		s[i] = 0;
		if (ft_strlen(s) != 0 && s[ft_strlen(s) - 1] != '\n')
			state = 1;
		full = ft_strjoin_free(full, s, 1);
		if (contain_c(full, '\n') && !(state = 0))
		{
			shell_body(full, &shell);
			ft_reset(&full);
		}
		else if (state == 0)
			exit(print_exit());
	}
	return (0);
}
