/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_body.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofernan <rofernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 10:42:36 by augay             #+#    #+#             */
/*   Updated: 2020/02/27 10:26:43 by rofernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	shell_body_3(char **cmdf, int *tabf)
{
	char *sp;

	sp = ft_strdup(cmdf[0]);
	free(cmdf[0]);
	cmdf[0] = NULL;
	if ((cmdf[0] = malloc(sizeof(char) * 100)) == NULL)
		exit(1);
	ft_memset(cmdf[0], 0, 100);
	parsing(sp, &(cmdf[0]), tabf);
	free(sp);
}

char		**rev_p(char **cmd)
{
	int i;
	int j;

	i = 0;
	while (cmd[i])
	{
		j = 0;
		while (cmd[i][j])
		{
			if (cmd[i][j] == -1 * ';')
				cmd[i][j] = ';';
			j++;
		}
		i++;
	}
	return (cmd);
}

static void	shell_body_4(char ***cmd, t_shell *shell)
{
	int fin;
	int part;
	int last_part;

	part = -1;
	if (!(last_part = 0) && test_syntax(shell, cmd[0]) == 258)
	{
		status_res(shell, 258);
		return ;
	}
	fin = ft_tablength(cmd[0]);
	if (cmd[0][0] == NULL)
		return ;
	while (++part <= fin)
	{
		if (part == fin || !wrap_cmp(cmd[0][part], ';'))
		{
			ft_stdin(shell, ft_tabcopy(cmd[0] + last_part, part - last_part));
			last_part = part + 1;
		}
		if (cmd[0][part] && !wrap_cmp(cmd[0][part], ';') && !cmd[0][part + 1])
			break ;
	}
	ft_free(cmd);
}

static void	shell_body_2(t_shell *shell, char *full)
{
	int		fin;
	int		*tab;
	char	**cmd;
	int		**tabf;

	fin = -1;
	tab = fill_tab(full);
	cmd = split_cmd(full, tab);
	tabf = fill_tabf(cmd);
	while (cmd[++fin])
		shell_body_3(&cmd[fin], tabf[fin]);
	cmd = finish_p(cmd, tabf);
	pop_word(cmd);
	ft_reverse(cmd);
	shell_body_4(&cmd, shell);
	free(tab);
	fin = 0;
	while (tabf[fin])
	{
		free(tabf[fin]);
		fin++;
	}
	free(tabf[fin]);
	free(tabf);
}

void		shell_body(char *in, t_shell *shell)
{
	char *full;

	full = ft_strdup(in);
	full[ft_strlen(full) - 1] = '\0';
	if (full[0] != '\0')
	{
		trad(&full, shell->env);
		shell_body_2(shell, full);
	}
	free(full);
	full = NULL;
}
