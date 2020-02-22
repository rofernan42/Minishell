/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stdin.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofernan <rofernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 16:44:54 by rofernan          #+#    #+#             */
/*   Updated: 2020/02/21 18:46:12 by rofernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_free(char ***s)
{
	int i = 0;

	if (s[0] == NULL)
		return ;
	while(s[0][i])
	{
		free(s[0][i]);
		s[0][i] = NULL;
		i++;
	}
	free(s[0][i]);
	s[0][i] = NULL;
	free(s[0]);
	s[0] = NULL;
}

void ft_p(char **s)
{
	int i = 0;
	while(s[i])
	{
		printf("s[%i]=[%s]\n",i, s[i]);
		i++;
	}
}

void		status_res(t_shell *shell, int status)
{
	t_env	*tmp;

	tmp = ft_envfind(shell->env, "?", ft_strcmp);
	ft_strdel(&tmp->data);
	tmp->data = ft_itoa(status);
}

void		fork_args(t_shell *shell, int *pdes, int i)
{
	int		status;
	pid_t	child_right;
	pid_t	child_left;
	int		sl;

	status = -42;
	child_left = 0;
	sl = -42;
		// printf("LEAKS FORK 1\n");
		// 	system("leaks a.out");

	if (!(status = is_builtin(shell, i)))
	{
		if (shell->args && !(child_left = fork()))
			fork_left(shell, pdes);
		if (!(child_right = fork()))
			fork_right(shell, pdes, i);
		close(pdes[1]);
		close(pdes[0]);
		waitpid(child_left, &sl, 0);
		waitpid(child_right, &status, 0);
	}
	// printf("LEAKS FORK 2\n");
	// 		system("leaks a.out");

	status_res(shell, status);
	if (status == 3 || sl == 3)
		ft_putstr_fd("Quit: 3\n", 1);
	if (WIFEXITED(status) == 1 && WEXITSTATUS(status) == 42)
		exit(0);
}

void		exec_pipe(t_shell *shell, int i)
{
	int		pdes[2];

	pipe(pdes);
	// printf("LEAKS EXEC 1\n");
	// 		system("leaks a.out");
	if (shell->args && !shell->next_args)
	{
		shell->next_args = shell->args;
		shell->args = NULL;
	}
	// printf("LEAKS EXEC 2\n");
	// 		system("leaks a.out");
	fork_args(shell, pdes, i);
		// printf("LEAKS EXEC 3\n");
		// 	system("leaks a.out");

}

void		ft_stdin(t_shell *shell, char **command)
{
// printf("LEAKS STDIN 1\n");
// 			system("leaks a.out");
	if (!test_syntax(shell, command))
		return ;
	// ft_p(command);
	// printf("LEAKS STDIN 2\n");
	// 		system("leaks a.out");
	h_split(shell, &command);
// printf("LEAKS STDIN 3\n");
			// system("leaks a.out");
	exec_pipe(shell, 0);
	//ft_free(command);
	// printf("LEAKS STDIN 4\n");
	// 		system("leaks a.out");

}
