/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: augay <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 10:39:18 by augay             #+#    #+#             */
/*   Updated: 2020/02/10 10:39:19 by augay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <dirent.h>
#include "includes/minishell.h"
#include "libft/libft.h"

char *ft_concat(char *s1, char *s2)
{
	int i1 = ft_strlen(s1);
	int i2 = ft_strlen(s2);
	char *o = malloc(sizeof(char) * (i1 + i2 + 2));
	int i = 0;
	while(s1[i])
	{
		o[i] = s1[i];
		i++;
	}
	i2 = 0;
	o[i] = '\n';
	i++;
	while(s2[i2])
	{
		o[i + i2] = s2[i2];
		i2++;
	}
	o[i + i2] = '\0';
	free(s1);
	return (o);
}

char *file2var(int fd)
{
	char *s = NULL;
	char *line;
	int i = 1;
	while((i = get_next_line(fd, &line)) == 1)
	{
		if (s == NULL)
			s = ft_strdup(line);
		else
			s = ft_concat(s, line);
		free(line);
	}
	s = ft_concat(s, line);
	free(line);
	return (s);
}

int main(int argc,char **argv)
{
	//read(0, NULL, 10);
	int fd = open("f3", O_RDONLY);
	char *s = file2var(fd);
	int f1;
	int f2;
	char *v = malloc(sizeof(char) * 3);
	char **av = malloc(sizeof(char*) * 4);
	av[1] = 0;
	av[0] = "grep";
	v[0] = 't';
	v[1] = 'e';
	v[2] = '\0';
	char *v2 = malloc(sizeof(char) * (3));
	v2[0] = '-';
	v2[1] = 'a';
	v2[2] = '\0';
	av[2] = 0;
	av[3] = 0;

	int pi[2];
	pipe(pi);
	close(0);
	dup2(pi[0], 0);
	printf("p0=%i, p1=%i\n",pi[0], pi[1]);
	write(pi[1], s, 23);
	close(pi[1]);
	close(pi[0]);
	if (fork() == 0)
	{
		execv("/bin/cat", av);
		exit(0);	
	}
	else
	{
		wait(NULL);
		printf("proc parent\n");
	}
	
	// DIR *d;
	// d = opendir("/bin");
	// struct dirent *dp;
	// while ((dp = readdir(d)) != NULL)
	// {
	// 	printf("%s\n", dp->d_name);
	// }
	return (0);
}
