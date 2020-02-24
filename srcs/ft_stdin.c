/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stdin.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofernan <rofernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 16:44:54 by rofernan          #+#    #+#             */
/*   Updated: 2020/02/24 12:13:09 by rofernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern int sig;

void		ft_free(char ***s)
{
	int i;

	i = 0;
	if (s[0] == NULL)
		return ;
	while (s[0][i])
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

void		status_res(t_shell *shell, int status)
{
	t_env	*tmp;

	tmp = ft_envfind(shell->env, "?", ft_strcmp);
	ft_strdel(&tmp->data);
	if (status == -42)
		status = 0;
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
	if (!(status = is_builtin(shell, i)))
	{
		if (shell->args && !(child_left = fork()))
			fork_left(shell, pdes);
		if (!(child_right = fork()))
			fork_right(shell, pdes, i);
		close(pdes[1]);
		close(pdes[0]);
		waitpid(child_left, &sl, WUNTRACED);
		waitpid(child_right, &status, WUNTRACED);
		printf("status=%i, stIFEX=%i, stEXS=%i, stSIGS=%i, stWSTOPSIG=%i, sl=%i, slIFEX=%i, slEXS=%i, slSIG=%i, slWSTOPSIG=%i\n", status, WIFEXITED(status), WEXITSTATUS(status), WTERMSIG(status), WSTOPSIG(status),sl, WIFEXITED(sl), WEXITSTATUS(sl), WTERMSIG(sl), WSTOPSIG(sl));

	}
	printf("status=%i, stIFEX=%i, stEXS=%i, stSIGS=%i, stWSTOPSIG=%i, sl=%i, slIFEX=%i, slEXS=%i, slSIG=%i, slWSTOPSIG=%i\n", status, WIFEXITED(status), WEXITSTATUS(status), WTERMSIG(status), WSTOPSIG(status),sl, WIFEXITED(sl), WEXITSTATUS(sl), WTERMSIG(sl), WSTOPSIG(sl));
	printf("SIG=%i\n",sig);
	if (sig != 0)
	{
		printf("SIG=%i\n",sig);
	}
	else if (WTERMSIG(status) > 0 && WTERMSIG(status) <= 5 && WTERMSIG(sl) > 0 && WTERMSIG(sl) >= 5)
	{
		if (WTERMSIG(status))
			printf("ret=%i\n", WTERMSIG(status));
		else
		{
			printf("ret=%i\n",WTERMSIG(sl));
		}
		
	}
	else if(status == 42)
	{
		printf("BUI=%i\n", 0);
	}
	else if (WIFEXITED(sl) || WIFEXITED(status))
	{
		if (WEXITSTATUS(sl))
			printf("reT =%i\n",WEXITSTATUS(sl));
		else
			printf("RET = %i\n",WEXITSTATUS(status));
	}
	sig = 0;
	status_res(shell, WEXITSTATUS(status));
	
	if (status == 3 || sl == 3)
		ft_putstr_fd("Quit: 3\n", 1);
	if (WIFEXITED(status) == 1 && WEXITSTATUS(status) == 42)
		exit(0);
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
	int ret;

	ret = test_syntax(shell, command);
	if (ret == 258)
	{
		status_res(shell, 258);
		printf("ret=258\n");
		return ;
	}
	h_split(shell, &command);
	ft_free(&command);
	exec_pipe(shell, 0);
}
