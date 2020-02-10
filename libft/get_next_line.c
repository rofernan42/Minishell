/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofernan <rofernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 10:06:27 by rofernan          #+#    #+#             */
/*   Updated: 2019/11/26 16:10:28 by rofernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	fill_line(char **str, char **line, int fd)
{
	int		i;
	char	*tmp;

	i = 0;
	while (str[fd][i] && str[fd][i] != '\n')
		i++;
	if (!(*line = ft_substr(str[fd], 0, i)))
		return (-1);
	if (ft_strchr(str[fd], '\n'))
	{
		if (!(tmp = ft_strdup(&str[fd][i + 1])))
			return (-1);
		free(str[fd]);
		str[fd] = tmp;
	}
	return (1);
}

static int	read_line(int fd, char **str)
{
	char	buffer[BUFFER_SIZE + 1];
	int		ret;

	if ((ret = read(fd, buffer, BUFFER_SIZE)) > 0)
	{
		buffer[ret] = '\0';
		if (!(str[fd] = ft_strjoin_free(str[fd], buffer, 1)))
			return (-1);
	}
	return (ret);
}

int			get_next_line(int fd, char **line)
{
	int			ret;
	static char	*str[1024];

	if (fd < 0 || !line || BUFFER_SIZE < 1)
		return (-1);
	*line = NULL;
	if (!str[fd])
		if (!(str[fd] = ft_strdup("")))
			return (-1);
	while (!ft_strchr(str[fd], '\n'))
	{
		ret = read_line(fd, str);
		if (ret == 0)
		{
			*line = ft_strdup(str[fd]);
			ft_strdel(&str[fd]);
			return (0);
		}
		if (ret < 0)
		{
			ft_strdel(&str[fd]);
			return (-1);
		}
	}
	return (fill_line(str, line, fd));
}
