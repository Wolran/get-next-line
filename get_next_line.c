/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmuller <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 08:26:05 by vmuller           #+#    #+#             */
/*   Updated: 2022/05/12 08:26:11 by vmuller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_str_replace(char *str)
{
	char	*strcpy;
	int		len;
	int		i;

	len = 0;
	i = 0;
	if (!str || !str[0])
		return (NULL);
	while (str[len] && str[len] != '\n')
		len++;
	if (str[len] == '\n')
		len++;
	strcpy = malloc(sizeof(char) * (len) + 1);
	if (!strcpy)
		return (NULL);
	while (i < len)
	{
		strcpy[i] = str[i];
		i++;
	}
	strcpy[i] = 0;
	return (strcpy);
}

char	*ft_next(char *str)
{
	char	*newstr;
	int		i;
	int		j;
	int		len;

	if (!str)
		return (NULL);
	i = 0;
	len = 0;
	j = ft_strlen(str);
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i] == '\n')
		i++;
	newstr = malloc(sizeof(char) * (j - i) + 1);
	if (!newstr)
		return (NULL);
	while (i < j)
		newstr[len++] = str[i++];
	newstr[len] = 0;
	free (str);
	return (newstr);
}

char	*get_next_line(int fd)
{
	static char	*str;
	char		*buffer;
	char		*strcpy;
	int			flag;

	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	flag = 1;
	while (!(ft_strchr(str, 10)) && flag)
	{
		flag = read(fd, buffer, BUFFER_SIZE);
		if (flag == -1)
			return (NULL);
		buffer[flag] = 0;
		str = ft_strjoin(str, buffer);
		if (!str)
			return (NULL);
	}
	strcpy = ft_str_replace(str);
	str = ft_next(str);
	free (buffer);
	return (strcpy);
}
/*
# include <stdio.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
int	main(void)
{
	int	fd;
	fd = open("fichier", O_RDONLY);
	for (int i = 0; i < 10; i++)
		printf("%s", get_next_line(fd));
}
*/