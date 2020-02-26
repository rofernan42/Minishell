/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stdin.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofernan <rofernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 16:44:54 by rofernan          #+#    #+#             */
/*   Updated: 2020/02/26 16:10:58 by rofernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void status_res(t_shell *shell, int status)
{
	t_env *tmp;

	tmp = ft_envfind(shell->env, "?", ft_strcmp);
	ft_strdel(&tmp->data);
	if (status == -42)
		status = 0;
	tmp->data = ft_itoa(status);
}

int still(t_shell *shell)
{
	if (shell->next_args == NULL)
		return (0);
	int i = 0;
	while (shell->next_args[i])

	{
		if (shell->next_args[i][0] == -1 * '|')
			return (1);
		i++;
	}
	return (0);
}

int execute_cmd2(char **s, t_shell *shell)
{
	int ret;

	if (!open_fd(shell, s))
		return (1);
	// dprintf(2, "RET OPENFD= %i\n",ret);
	copy_stdinout(shell);
	if (is_builtin(shell, s))

	{
		close_stdinout(shell);
		exit(0);
	}
	s = extract(s);
	// dprintf(2, "RES EXTRACT\n");
	// ft_p(s);
	ret = prep_path(shell, s);
	// ft_p(s);
	execve(s[0], s, NULL);
	close_stdinout(shell);
	// dprintf(2,"RET = %i\n", ret);
	return (ret);
}

int exec_pipe2(t_shell *shell, int i)
{
	int pdes[2];
	int status;
	pid_t child_right = 25;
	pid_t child_left = 25;
	int f;

	pipe(pdes);
	if (i == 0 && shell->next_args == NULL && shell->args != NULL)

	{
		shell->next_args = shell->args;
		shell->args = NULL;
		if (!open_fd(shell, shell->next_args))
			return (1);
		copy_stdinout(shell);
		if (is_builtin(shell, shell->next_args))

		{
			close_stdinout(shell);
			return (0);
		}
		else
			close_stdinout(shell);
	}
	if (shell->args && !(child_left = fork()))

	{
		close(pdes[0]);
		dup2(pdes[1], STDOUT_FILENO);
		exit(execute_cmd2(shell->args, shell));
	}
	if (!(child_right = fork()))

	{

		if (shell->args)

		{
			close(pdes[1]);
			dup2(pdes[0], STDIN_FILENO);
		}
		if (still(shell) == 1)

		{
			h_split(shell, &shell->next_args);
			exec_pipe2(shell, i + 1);
		}
		else if (shell->next_args != NULL)

		{
			exit(execute_cmd2(shell->next_args, shell));
		}
	}
	close(pdes[1]);
	close(pdes[0]);

	status = 0;
	waitpid(child_left, &status, 0);
	status = 0;
	waitpid(child_right, &status, 0);
	if (i != 0)
		exit(WEXITSTATUS(status));
	else
	{
		return (status);
	}
}

void ft_stdin(t_shell *shell, char **command)
{
	int ret;

	ret = test_syntax(shell, command);
	if (ret == 258)

	{
		status_res(shell, 258);
		return;
	}
	h_split(shell, &command);
	ft_free(&command);
	ret = exec_pipe2(shell, 0);
	// printf("g_sig=%i, ret=%i BLOBLB\n",g_sig, ret);
	if (g_sig == 11)
		ret = 130;
	else if (g_sig == 8)
		ret = 131;
	else if (ret == 1)
		ret = 1;
	else
		ret = WEXITSTATUS(ret);
	status_res(shell, ret);
	// printf("g_sig=%i, ret=%i BLOBLB\n",g_sig, ret);
	g_sig = 0;
}
