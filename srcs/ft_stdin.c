/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stdin.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofernan <rofernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 16:44:54 by rofernan          #+#    #+#             */
/*   Updated: 2020/02/27 12:20:49 by rofernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		still(t_shell *shell)
{
	int i;

	i = 0;
	if (shell->next_args == NULL)
		return (0);
	while (shell->next_args[i])
	{
		if (shell->next_args[i][0] == -1 * '|')
			return (1);
		i++;
	}
	return (0);
}

int		execute_cmd(char **s, t_shell *shell)
{
	int ret;

	if (!open_fd(shell, s))
		return (1);
	copy_stdinout(shell);
	if (is_builtin(s))
	{
		ret = builtin_exec(shell, s);
		close_stdinout(shell);
		exit(ret);
	}
	s = extract(s);
	ret = prep_path(shell, s);
	execve(s[0], s, NULL);
	close_stdinout(shell);
	return (ret);
}

int		exec_pipe(t_shell *shell, int i)
{
	int		pdes[2];
	int		status;
	pid_t	child_right;
	pid_t	child_left;

	child_right = 25;
	child_left = 25;
	pipe(pdes);
	if (i == 0 && shell->next_args == NULL && shell->args != NULL)
		if (((status = first(shell)) >= 0))
			return (status);
	if (shell->args && !(child_left = fork()))
		fork_left(pdes, shell);
	if (!(child_right = fork()))
		fork_right(shell, i, pdes);
	close(pdes[1]);
	close(pdes[0]);
	waitpid(child_left, &status, 0);
	waitpid(child_right, &status, 0);
	if (status == 3)
		ft_putstr_fd("Quit: 3\n", 1);
	if (i != 0)
		exit(WEXITSTATUS(status));
	else
		return (status);
}

void	ft_stdin(t_shell *shell, char **command)
{
	int ret;

	h_split(shell, &command);
	ft_free(&command);
	ret = exec_pipe(shell, 0);
	if (g_sig == 11)
		ret = 130;
	else if (g_sig == 8)
		ret = 131;
	else if (ret == 256)
		ret = WEXITSTATUS(ret);
	else if (ret == 32512)
		ret = 127;
	status_res(shell, ret);
	g_sig = 0;
}
