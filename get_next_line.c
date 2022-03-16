#include "get_next_line.h"

char	*ft_str_replace(char *str)
{
	char	*strcpy;
	int		i;
	int		j;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i] == '\n')
		i++;
	strcpy = malloc(i + 1);
	if (!strcpy)
		return (NULL);
	j = 0;
	while (j < i)
	{
		strcpy[j] = str[j];
		j++;
	}
	strcpy[j] = 0;
	return (strcpy);
}

char	*ft_next(char *str)
{
	char	*newstr;
	int		i;
	int		j;
	int		len;

	i = 0;
	len = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i] == '\n')
		i++;
	j = ft_strlen(str);
	newstr = malloc(j - i);
	if (!newstr)
		return (NULL);
	while (i < j)
	{
		newstr[len] = str[i];
		i++;
		len++;
	}
	newstr[len] = 0;
	free (str);
	return (newstr);
}

char	*get_next_line(int fd)
{
	static char	*str = 0;
	char		*buffer;
	char		*strcpy;
	int			flag;

	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	flag = 1;
	while (!(ft_strrchr(str, '\n')) && flag != 0)
	{
		flag = _read(fd, buffer, BUFFER_SIZE);
		buffer[flag] = 0;
		str = ft_strjoin(str, buffer);
	}
	free (buffer);
	strcpy = ft_str_replace(str);
	if (flag == 0)
		strcpy = 0;
	str = ft_next(str);
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