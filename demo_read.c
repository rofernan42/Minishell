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
	//o[i] = '\n';
	//i++;
	while(s2[i2])
	{
		o[i + i2] = s2[i2];
		i2++;
	}
	o[i + i2] = '\0';
	free(s1);
	return (o);
}

int contain(char *s)
{
	int i = 0;
	while(s[i])
	{
		if (s[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

int main()
{
	int i = 0;
	char *s = malloc(sizeof(char) * 11);
	char *full = malloc(sizeof(char) * 1);
	full[0] = '\0';
	while(1)
	{
		i = read(0, s, 10);
		s[i] = 0;
		full = ft_concat(full, s);
		//printf("i=%i, s=%s\n",i,s);
		printf("FULL=%s\n",full);
		if (contain(full))
		{
			printf("LAST\n");
			free(full);
			full = malloc(sizeof(char) * 1);
			full[0] = '\0';
		}
		if(i == 0)
			exit(1);
	}
	return (0);
}