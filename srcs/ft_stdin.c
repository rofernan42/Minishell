/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stdin.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofernan <rofernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 16:44:54 by rofernan          #+#    #+#             */
/*   Updated: 2020/02/26 13:37:34 by rofernan         ###   ########.fr       */
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

int execute_cmd2(char **s, t_shell *shell)
{
	int ret;

	ret = open_fd(shell, s);
	if (!ret)
		return (1);
	// dprintf(2, "RET OPENFD= %i\n",ret);
	copy_stdinout(shell);
	if (is_builtin(shell, s))
		exit(0);
	s = extract(s);
	// dprintf(2, "RES EXTRACT\n");
	// ft_p(s);
	prep_path(shell, s);
	// ft_p(s);
	execve(s[0], s, NULL);
	// close_stdinout(shell);
	return (127);
}

int    exec_pipe2(t_shell *shell, int i)
{
    int     pdes[2];
    int     status;
    pid_t   child_right;
    pid_t   child_left;
	int f;

    pipe(pdes);
	if (i == 0 && shell->next_args == NULL && shell->args != NULL)
	{
		shell->next_args = shell->args;
		shell->args = NULL;
		if (!open_fd(shell, shell->next_args))
			return (1);
		f = copy_stdinout(shell);
		if (is_builtin(shell, shell->next_args))
		{
			if (f)
				close_stdinout(shell);
			return (0);
		}
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
			// printf("RESTE PIPE\n");
			h_split(shell, &shell->next_args);
            exec_pipe2(shell, i+1);
		}
		else if (shell->next_args != NULL)
            exit(execute_cmd2(shell->next_args, shell));
    }
    close(pdes[1]);
    close(pdes[0]);
    wait(NULL);
    waitpid(child_right, &status, 0);
	// dprintf(2, "RET VAL=%i, pid=%i\n",status, getpid());
	if (i != 0)
    	exit(status);
	else
	{
		close_stdinout(shell);
		return (status);
	}
	
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
	g_sig = exec_pipe2(shell, 0);
}
