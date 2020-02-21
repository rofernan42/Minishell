/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_struct.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: augay <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 16:04:21 by augay             #+#    #+#             */
/*   Updated: 2020/02/21 16:04:23 by augay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_STRUCT_H
# define MINI_STRUCT_H

typedef struct		s_env
{
	char			*name;
	char			*data;
	struct s_env	*next;
}					t_env;

typedef struct		s_shell
{
	char			**args;
	char			**next_args;
	char			*name_prog;
	int				fd_in;
	int				fd_out;
	int				stdout_cpy;
	int				stdin_cpy;
	t_env			*env;
}					t_shell;

#endif
