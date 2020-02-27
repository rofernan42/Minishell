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

int		exec_pipe(t_shell *shell, int i);

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
	if (is_builtin(shell, s))
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

void	fork_right(t_shell *shell, int i, int *pdes)
{
	if (shell->args)
	{
		close(pdes[1]);
		dup2(pdes[0], STDIN_FILENO);
	}
	if (still(shell) == 1)
	{
		h_split(shell, &shell->next_args);
		exec_pipe(shell, i + 1);
	}
	else if (shell->next_args != NULL)
		exit(execute_cmd(shell->next_args, shell));
}

int		first(t_shell *shell)
{
	int ret;

	shell->next_args = shell->args;
	shell->args = NULL;
	if (!open_fd(shell, shell->next_args))
		return (1);
	copy_stdinout(shell);
	if (is_builtin(shell, shell->next_args))
	{
		ret = builtin_exec(shell, shell->next_args);
		close_stdinout(shell);
		return (ret);
	}
	else
	{
		close_stdinout(shell);
		return (-1);
	}
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
		if ((status = first(shell) >= 0))
			return (status);
	if (shell->args && !(child_left = fork()))
	{
		close(pdes[0]);
		dup2(pdes[1], STDOUT_FILENO);
		exit(execute_cmd(shell->args, shell));
	}
	if (!(child_right = fork()))
		fork_right(shell, i, pdes);
	close(pdes[1]);
	close(pdes[0]);
	waitpid(child_left, &status, 0);
	status = 0;
	waitpid(child_right, &status, 0);
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
	else if (ret == 1)
		ret = 1;
	else
		ret = WEXITSTATUS(ret);
	status_res(shell, ret);
	g_sig = 0;
}
