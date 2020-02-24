/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_body.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: augay <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 10:42:36 by augay             #+#    #+#             */
/*   Updated: 2020/02/24 10:42:37 by augay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
	ft_free(cmd);
	fin = 0;
}

void	shell_body_2(t_shell *shell, char *full)
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
	free(full);
	full = NULL;
}
