/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofernan <rofernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 14:26:58 by rofernan          #+#    #+#             */
/*   Updated: 2020/02/17 13:01:55 by rofernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// int             main(int ac, char **av, char **envp)
// {
// 	int   ret;
// 	int   pid;
// 	int   *statut;
// 	char  *arg[] = {"", NULL};

// 	ret = open(av[1], O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR);

// 	if (ret == -1)
// 	{
// 	  puts("Error open ....");
// 	  exit(EXIT_FAILURE);
// 	}
// 	dup2(ret, 1);
// 	execve("/bin/pwd", arg, envp);
// 	// if (fork() == 0)
// 	// {
// 	// //   execve("/bin/pwd", arg, envp);
// 	//   perror("Error execve ...");
// 	// }
// 	// else
// 	// {
// 	// 	execve("/bin/pwd", arg, envp);
// 	// 	wait(statut);
// 	// }
// 	// close(ret);
// 	return (1);
// }

void		redir(t_shell *shell, char **envp)
{
	int i;

	i = 0;
	while (shell->args[i])
	{
		if (!ft_strcmp(shell->args[i], ">") || !ft_strcmp(shell->args[i], ">>"))
		{
			if (shell->args[i + 1])
			{
				if (ft_strcmp(shell->args[i + 1], ">") && ft_strcmp(shell->args[i + 1], ">>"))
				{
					if (!ft_strcmp(shell->args[i], ">"))
						shell->fd = open(shell->args[i + 1], O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
					else if (!ft_strcmp(shell->args[i], ">>"))
						shell->fd = open(shell->args[i + 1], O_WRONLY | O_APPEND | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
				}
				else
					display_error("syntax error near unexpected token `", shell->args[i + 1], 0, "'");
			}
			else
				display_error("syntax error near unexpected token `", "newline", 0, "'");			
		}
		i++;
	}
	dup2(shell->fd, 1);
	close(shell->fd);
	// if (fork() == 0)
	// {
	//   execve(shell->args[0], shell->args, envp);
	//   exit(0);
	// }
	// else
	// {
	// 	wait(NULL);
	// 	// printf("test1\n");
	// }
	// close(fd);
}
