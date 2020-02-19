/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stdin.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofernan <rofernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 16:44:54 by rofernan          #+#    #+#             */
/*   Updated: 2020/02/18 18:41:14 by rofernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void exec_pipe(t_shell *shell);

static char **extract(t_shell *shell)
{
	int i;
	int j;
	char **tmp;

	i = 0;
	j = 0;
	while (shell->args[i])
	{
		if (i == 0 || (i > 0 && !is_chevron(shell->args[i]) && !is_chevron(shell->args[i - 1])))
			j++;
		i++;
	}
	if (!(tmp = malloc(sizeof(char *) * (j + 1))))
		exit(EXIT_FAILURE);
	i = -1;
	j = 0;
	while (shell->args[++i])
		if (i == 0 || (i > 0 && !is_chevron(shell->args[i]) && !is_chevron(shell->args[i - 1])))
			tmp[j++] = ft_strdup(shell->args[i]);
	tmp[j] = NULL;
	return (tmp);
}

static int is_builtin(t_shell *shell)
{
	shell->args = extract(shell);
	if (!ft_strcmp(shell->args[0], "echo"))
		ft_echo(shell);
	else if (!ft_strncmp(shell->args[0], "cd", 2))
		ft_cd(shell->args[1], shell->env);
	else if (!ft_strcmp(shell->args[0], "pwd"))
		ft_pwd(shell->env);
	else if (!ft_strcmp(shell->args[0], "export"))
		ft_export(&shell->args[1], shell->env);
	else if (!ft_strcmp(shell->args[0], "unset"))
		ft_unset(&shell->args[1], shell->env);
	else if (!ft_strcmp(shell->args[0], "env"))
		ft_env(shell->env);
	else if (!ft_strcmp(shell->args[0], "exit"))
	{
		ft_putendl_fd("exit", 1);
		free_all(shell);
		exit(0);
	}
	else
		return (0);
	return (1);
}

static void process_exec(t_shell *shell)
{
	char **tmp;

	tmp = extract(shell);
	execve(shell->args[0], tmp, 0);
}

static void copy_stdinout(t_shell *shell)
{
	if (shell->fd_in >= 0)
	{
		shell->stdout_cpy = dup(1);
		close(1);
		dup2(shell->fd_in, 1);
	}
	if (shell->fd_out >= 0)
	{
		shell->stdin_cpy = dup(0);
		close(0);
		dup2(shell->fd_out, 0);
	}
}

static void close_stdinout(t_shell *shell)
{
	if (shell->fd_in >= 0)
	{
		dup2(shell->stdout_cpy, 1);
		close(shell->stdout_cpy);
	}
	if (shell->fd_out >= 0)
	{
		dup2(shell->stdin_cpy, 0);
		close(shell->stdin_cpy);
	}
}

int nb_pipe(char **s)
{
	int i;
	int j;

	j = 0;
	i = 0;
	while (s[i])
	{
		if (!ft_strcmp(s[i], "|"))
			j++;
		i++;
	}
	return (j);
}

void h_split(t_shell *shell, char **cmd)
{
	int i = 0;
	ft_p(cmd);
	int fin = ft_long(cmd);
	char ***h = malloc(sizeof(char **) * 2);
	int p = 0;
	int d = 0;
	int part = 0;
	int last_part = 0;
	fin = ft_long(cmd);
	while (part <= fin && p < 1)
	{
		if (part == fin || !strcmp(cmd[part], "|"))
		{
			//ft_p(def);
			printf("last=%i, part=%i, fin=%i, p=%i\n", last_part, part, fin, p);
			h[0] = (ft_copy(cmd + last_part, part - last_part));
			last_part = part + 1;
			p++;
		}
		part++;
	}
	if (part < fin)
		h[1] = ft_copy(cmd + last_part, fin - last_part);
	printf("H0\n");
	ft_p(h[0]);
	if (part < fin)
	{
	printf("H1\n");
	ft_p(h[1]);
	}
	shell->args = h[0];
	if (part < fin)
		shell->next_args = h[1];
	else
	{
		shell->next_args = NULL;
	}
	
}
int execute_cmd(char **cmd, t_shell *shell);

int reste(char **s)
{
	int i = 0;
	if (s == NULL)
		return (0);
	while(s[i])
	{
		if (!ft_strcmp(s[i], "|"))
		{
			return (1);
		}
		i++;
	}
	return (0);
}

void exec_pipe(t_shell *shell)
{
	int pdes[2];
	int status;
	pid_t child_right;
	pid_t child_left;
	pipe(pdes);
	if (!(child_left = fork()))
	{
		close(pdes[0]);
		dup2(pdes[1], STDOUT_FILENO);
		/* Execute command to the left of the tree */
		exit(execute_cmd(shell->args, shell));
	}
	if (!(child_right = fork()))
	{
		close(pdes[1]);
		dup2(pdes[0], STDIN_FILENO);
		/* Recursive call or execution of last command */
		if (reste(shell->next_args)) // if plusieurs pipe
		{
			h_split(shell, shell->next_args);
			exec_pipe(shell);
		}
		else if(shell->next_args != NULL)
			exit(execute_cmd(shell->next_args, shell));
	}
	/* Should not forget to close both ends of the pipe */
	close(pdes[1]);
	close(pdes[0]);
	wait(NULL);
	waitpid(child_right, &status, 0);
	// exit(0);
}

int execute_cmd(char **cmd, t_shell *shell)
{
	shell->args = cmd;
	open_fd(shell);
	//{
	copy_stdinout(shell);
	//ft_p(cmd);
	if (!is_builtin(shell))
	{
		if (fork() == 0)
		{
			prep_path(shell);
			process_exec(shell);
			exit(0);
		}
		else
		{
			wait(NULL);
		}
	}
	close_stdinout(shell);
	//}
	return (0);
}
void ft_stdin(t_shell *shell, char **command)
{
	int end;
	int part;
	int last_part;
	int pipe_fd[2];
	int nbp = nb_pipe(command);
	char ***h;
	//printf("NBP = %i\n", nbp);
	//ft_p(command);
	pipe(pipe_fd);
	part = 0;
	last_part = 0;
	h_split(shell, command);
	exec_pipe(shell);
	// if (open_fd(shell))
	// {
	// 	copy_stdinout(shell);
	// 	if (!is_builtin(shell))
	// 	{
	// 		if (fork() == 0)
	// 		{
	// 			prep_path(shell);
	// 			process_exec(shell);
	// 			exit(0);
	// 		}
	// 		else
	// 		{
	// 			wait(NULL);
	// 		}
	// 	}
	// 	close_stdinout(shell);
	// }
	// // free(shell->command);
	// // shell->command = ft_strdup("");
	// del_args(command);
}
