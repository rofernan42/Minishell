/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stdin.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofernan <rofernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 16:44:54 by rofernan          #+#    #+#             */
/*   Updated: 2020/02/20 20:38:00 by rofernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	fork_left(t_shell *shell, int *pdes)
{
	signal(SIGINT, NULL);
	close(pdes[0]);
	dup2(pdes[1], 1);
	exit(execute_cmd(shell->args, shell));
	exit(0);
}

static void	fork_right(t_shell *shell, int *pdes, int i)
{
	signal(SIGINT, NULL);
	if (!(shell->args == NULL && shell->next_args != NULL))
	{
		close(pdes[1]);
		dup2(pdes[0], 0);
	}
	if (reste_arg(shell->next_args, "|"))
	{
		// printf("i = %d\n", i);
		// printf("ARGS\n");
		// ft_p(shell->args);
		// printf("NEXT ARGS\n");
		// ft_p(shell->next_args);

		h_split(shell, shell->next_args);

		// printf("i = %d\n", i);
		// printf("apres ARGS\n");
		// ft_p(shell->args);
		// printf("apres NEXT ARGS\n");
		// ft_p(shell->next_args);
		
		exec_pipe(shell, i + 1);
	}
	else if (shell->next_args != NULL)
		exit(execute_cmd(shell->next_args, shell));
	exit(0);
}

void		fork_args(t_shell *shell, int *pdes, int i)
{
	int		status;
	pid_t	child_right;
	pid_t	child_left;

	status = -42;
	// if (open_file(shell))
	// {
		// copy_stdinout(shell);
		if (!is_builtin(shell, i))
		{
			if (shell->args && !(child_left = fork()))
				fork_left(shell, pdes);
			if (!(child_right = fork()))
				fork_right(shell, pdes, i);
			close(pdes[1]);
			close(pdes[0]);
			waitpid(child_left, NULL, 0);
			waitpid(child_right, &status, 0);
		}
		// else
		// {
		// 	// if (open_file(shell))
		// 	// {
		// 	// copy_stdinout(shell);
		// 	if (reste_arg(shell->next_args, "|"))
		// 	{
		// 	h_split(shell, shell->next_args);
		// 	exec_pipe(shell, i + 1);
		// 	}
		// 	// close_stdinout(shell);

		// 	// }
		// // // 	// printf("test\n");
		// }
		// close_stdinout(shell);
	// }
	if (WIFEXITED(status) == 1 && WEXITSTATUS(status) == 42)
		exit(0);
	if ((WIFEXITED(status) != 0 || status == -42) && i == 0)
		ft_putstr_fd("\033[33mminishell$\033[0m ", 1);
}

void		exec_pipe(t_shell *shell, int i)
{
	int		pdes[2];

	pipe(pdes);
	if (shell->args && !shell->next_args)
	{
		shell->next_args = shell->args;
		shell->args = NULL;
	}
	fork_args(shell, pdes, i);
}

void		ft_stdin(t_shell *shell, char **command)
{
	h_split(shell, command);
	exec_pipe(shell, 0);
}
