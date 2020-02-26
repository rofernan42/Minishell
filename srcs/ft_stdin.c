/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stdin.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofernan <rofernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 16:44:54 by rofernan          #+#    #+#             */
/*   Updated: 2020/02/25 15:41:59 by rofernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void		status_res(t_shell *shell, int status)
{
	t_env	*tmp;

	tmp = ft_envfind(shell->env, "?", ft_strcmp);
	ft_strdel(&tmp->data);
	if (status == -42)
		status = 0;
	tmp->data = ft_itoa(status);
}

int		fork_args(t_shell *shell, int *pdes, int i)
{
	int		status;
	pid_t	child_right;
	pid_t	child_left;
	int		sl;
	int		ret;
	int s= 0;

	ret = 0;
	status = -50;
	child_left = 1;
	child_right = 1;
	sl = -50;
	dprintf(2, "FORK ARGS DATA in PID=%i et i=%i\n", getpid(), i);
	if (shell->args != NULL)
	{
		ft_p(shell->args);
	}
	else
	{
		dprintf(2, "SHELL->ARGS=NULL\n");
	}
	if (shell->next_args != NULL)
	{
		ft_p(shell->next_args);
	}
	else
	{
		dprintf(2, "SHELL->NEXT_ARGS=NULL\n");
	}

	

	// if (i == 0 && !shell->args && shell->next_args)
	// {
	// 	if (!(status = is_builtin(shell)))
	// 	{
	// 		if (shell->args && (s = 1) && !(child_left = fork()))
	// 		{
	// 			dprintf(2, "JE FORK LEFT 1\n");
	// 			fork_left(shell, pdes);
	// 		}
	// 		else if (s == 0 && shell->args == NULL && child_left == 1 && !(child_right = fork()))
	// 		{
	// 			dprintf(2, "JE FORK RIGHT 1\n");
	// 			fork_right(shell, pdes, i);
	// 		}
	// 		// close(pdes[1]);
	// 		// close(pdes[0]);
	// 		// waitpid(child_left, &sl, WUNTRACED);
	// 		// waitpid(child_right, &status, WUNTRACED);
	// 	}
	// }
	// else
	// {
		if (shell->args && shell->next_args != NULL && (s = 1) && !(child_left = fork()))
		{
				dprintf(2, "JE FORK LEFT 2\n");
				fork_left(shell, pdes);
		}
		if (!(child_right = fork()))
		{				dprintf(2, "JE FORK RIGHT 2\n");

				if (reste_arg(shell->next_args, inv('|')))
				{
					h_split(shell, &shell->next_args);
					exec_pipe(shell, i+1);
				}
				else
				{
					fork_right(shell, pdes, i);
					exit(0);
				}
		}
		// else
		// {
		// 	shell->args = NULL;
		// 	shell->next_args = NULL;
		// }
		
		// close(pdes[1]);
		// close(pdes[0]);
		// waitpid(child_left, &sl, WUNTRACED);
		// waitpid(child_right, &status, WUNTRACED);
	// }

		//printf("GSIG STATUS=%i\n", WEXITSTATUS(status));
				// dprintf(2, "---PID--- = %i\n", getpid());

			// printf("AVAV LEFT = %i, RIGHT = %i\n", child_left, child_right);
		//if (child_right != 1)
		waitpid(child_right, &status, 0);
				// dprintf(2, "---PID--- = %i\n", getpid());

	// printf("GSIG STATUS=%i\n", status);
	//if (child_left != 1)
		waitpid(child_left, &sl, 0);
				// dprintf(2, "---PID--- = %i\n", getpid());
	close(pdes[1]);
	close(pdes[0]);
		// printf("GSIG2 SL=%i\n", sl);

	if (child_left == 1)
		g_sig = status;
	else
	{
		g_sig = sl;
	}
		// dprintf(2, "---PID--- = %i\n", getpid());
		// printf("GSIGFIN=%i et WEX=%i et pid = %i et i=%i\n",g_sig, WEXITSTATUS(g_sig),getpid(), i);
	// printf("LEFT = %i, RIGHT = %i\n", child_left, child_right);
	// if (child_left == 0 || child_right == 0)
	// {
		//g_sig = -1;
				// dprintf(2, "---PID--- = %i\n", getpid());

		// printf("STDINJE RETURN GSIG = %i\n", g_sig);
		if ( i != 0)
			exit(g_sig);
		// else
		// {
			return (g_sig);
		// }
		
	// }
		// printf("status=%i, stIFEX=%i, stEXS=%i, stSIGS=%i, stWSTOPSIG=%i, sl=%i, slIFEX=%i, slEXS=%i, slSIG=%i, slWSTOPSIG=%i\n", status, WIFEXITED(status), WEXITSTATUS(status), WTERMSIG(status), WSTOPSIG(status),sl, WIFEXITED(sl), WEXITSTATUS(sl), WTERMSIG(sl), WSTOPSIG(sl));
		// printf("status=%i, stIFEX=%i, stEXS=%i, stSIGS=%i, stWSTOPSIG=%i, sl=%i, slIFEX=%i, slEXS=%i, slSIG=%i, slWSTOPSIG=%i\n", status, WIFEXITED(status), WEXITSTATUS(status), WTERMSIG(status), WSTOPSIG(status),sl, WIFEXITED(sl), WEXITSTATUS(sl), WTERMSIG(sl), WSTOPSIG(sl));
	// if (g_sig != 0)
	// {
	// 	ret = 130;
	// }
	// else if (WTERMSIG(status) > 0 && WTERMSIG(status) <= 5 && WTERMSIG(sl) > 0 && WTERMSIG(sl) >= 5)
	// {
	// 	if (WTERMSIG(status))
	// 	{
	// 		ret = WTERMSIG(status) + 128;
	// 	}
	// 	else
	// 	{
	// 		ret = WTERMSIG(sl);
	// 	}
		
	// }
	// else if(status == 42)
	// {
	// 	ret = 0;
	// }
	// else if (WIFEXITED(sl) || WIFEXITED(status))
	// {
	// 	if (WEXITSTATUS(sl))
	// 	{
	// 		ret = WEXITSTATUS(sl);
	// 	}
	// 	else
	// 	{
	// 		ret = WEXITSTATUS(status);
	// 	}
	// }
	// g_sig = 0;
	// status_res(shell, ret);
	// if (status == 3 || sl == 3)
	// 	ft_putstr_fd("Quit: 3\n", 1);
	// if (WIFEXITED(status) == 1 && WEXITSTATUS(status) == 42)
	// 	exit(0);
}

int		exec_pipe(t_shell *shell, int i)
{
	int		pdes[2];

	pipe(pdes);
	// if (shell->args && !shell->next_args)
	// {
	// 	shell->next_args = shell->args;
	// 	shell->args = NULL;
	// }
	return (fork_args(shell, pdes, i));
}

int still(t_shell *shell)
{
	if (shell->next_args == NULL)
		return (0);
	int i = 0;
	while(shell->next_args[i])
	{
		if (shell->next_args[i][0] == -1 * '|')
			return (1);
		i++;
	}
	return (0);
}

int execute_cmd2(char **shell)
{
	if (shell == NULL)
		exit(0);
	execve(shell[0], shell, NULL);
	exit(0);
}

void    exec_pipe2(t_shell *shell, int i)
{
    int     pdes[2];
    int     status;
    pid_t   child_right;
    pid_t   child_left;

    pipe(pdes);
	if (i == 0 && shell->next_args == NULL && shell->args != NULL)
	{
		shell->next_args = shell->args;
		shell->args = NULL;
	}
	if (!(child_left = fork()))
    {
        close(pdes[0]);
        dup2(pdes[1], STDOUT_FILENO);
        /* Execute command to the left of the tree */
        exit(execute_cmd2(shell->args));
    }
    if (!(child_right = fork()))
    {
        close(pdes[1]);
        dup2(pdes[0], STDIN_FILENO);
        /* Recursive call or execution of last command */
		//ft_p(shell->args);
		//ft_p(shell->next_args);
        if (still(shell) == 1) // if contain -|
		{
			printf("RESTE PIPE\n");
			h_split(shell, &shell->next_args);
            exec_pipe2(shell, i+1); //hspli
		}
		else if (shell->next_args != NULL)
            exit(execute_cmd2(shell->next_args));
    }
    /* Should not forget to close both ends of the pipe */
    close(pdes[1]);
    close(pdes[0]);
    wait(NULL);
    waitpid(child_right, &status, 0);
	if (i != 0)
    	exit(status);
}

void		ft_stdin(t_shell *shell, char **command)
{
	int ret;
	ret = test_syntax(shell, command);
	if (ret == 258)
	{
		status_res(shell, 258);
		return ;
	}
	h_split(shell, &command);
	ft_free(&command);
	ft_p(shell->args);
	exec_pipe2(shell, 0);
	printf("\nGSI FINAL=%i et WEX=%i et pid = %i\n",g_sig, WEXITSTATUS(g_sig),getpid());
}
