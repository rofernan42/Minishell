/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofernan <rofernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 15:39:35 by rofernan          #+#    #+#             */
/*   Updated: 2020/02/24 17:41:56 by rofernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	g_sig;

static int	init_main(t_shell *shell, char **s, char **full)
{
	init_env(&shell->env);
	s[0] = malloc(sizeof(char) * 11);
	full[0] = malloc(sizeof(char) * 1);
	shell->args = NULL;
	shell->next_args = NULL;
	signal(SIGINT, sig_handle_c);
	signal(SIGQUIT, sig_handle_b);
	ft_putstr_fd("\033[33mminishell$\033[0m ", 1);
	if (s[0] == NULL || full[0] == NULL)
		exit(1);
	full[0][0] = '\0';
	return (0);
}

static void	ft_reset(char **full)
{
	free(full[0]);
	full[0] = NULL;
	full[0] = malloc(sizeof(char) * 1);
	full[0][0] = '\0';
}

static int	print_exit(void)
{
	ft_putendl_fd("exit", 2);
	return (0);
}

static void	last_one(char **full, char **s, int *state, t_shell *shell)
{
	if (ft_strlen(s[0]) != 0 && s[0][ft_strlen(s[0]) - 1] != '\n')
		*state = 1;
	full[0] = ft_strjoin_free(full[0], s[0], 1);
	if (contain_c(full[0], '\n') && !(*state = 0))
	{
		shell_body(full[0], shell);
		ft_reset(full);
		ft_putstr_fd("\033[33mminishell$\033[0m ", 1);
	}
	else if (*state == 0)
		exit(print_exit());
}

int			main(int ac, char **av)
{
	t_shell	shell;
	int		i;
	char	*s;
	char	*full;
	int		state;

	g_sig = 0;
	init_name_prog(&shell, av[0]);
	if (ac == 1)
	{
		state = init_main(&shell, &s, &full);
		while (1)
		{
			i = read(0, s, 10);
			s[i] = 0;
			last_one(&full, &s, &state, &shell);
		}
	}
	else if (ac > 1)
		disp_err(shell.name_prog, 0, av[1], "No such file or directory");
	return (0);
}
