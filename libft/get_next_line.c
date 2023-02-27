/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djmekki < djmekki@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 07:23:51 by djmekki           #+#    #+#             */
/*   Updated: 2022/07/09 23:40:19 by djmekki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_readfile(int fd, char *buffer, char *tmp, char **str)
{
	int		bytes_size;

	bytes_size = 1;
	while (bytes_size != 0)
	{
		bytes_size = read(fd, buffer, BUFFER_SIZE);
		if (bytes_size == -1)
			return (NULL);
		buffer[bytes_size] = 0;
		tmp = *str;
		if (!tmp)
		{
			tmp = (char *)malloc(sizeof(char) * 1);
			if (!tmp)
				return (NULL);
			tmp[0] = 0;
		}
		*str = ft_strjoin(tmp, buffer);
		free(tmp);
		if (ft_isline(*str))
			bytes_size = 0;
	}
	free(buffer);
	return (*str);
}

char	*ft_getline(char *str)
{
	int		i;
	char	*line;

	if (!str)
		return (NULL);
	if (*str == 0)
		return (NULL);
	line = (char *)malloc(sizeof(char) * (ft_linelen(str) + 1));
	if (!line)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '\n')
	{
		line[i] = str[i];
		i++;
	}
	if (str[i] == 0)
		line[i] = 0;
	else if (str[i] == '\n')
	{
		line[i++] = '\n';
		line [i] = 0;
	}
	return (line);
}

char	*ft_save(char *str)
{
	char	*saved;
	int		j;
	int		i;

	j = 0;
	i = ft_strlen(str);
	if (!str)
		return (NULL);
	while (str[j] && str[j] != '\n')
		j++;
	if (str[j] == 0)
	{
		free(str);
		return (NULL);
	}
	saved = (char *)malloc(sizeof(char) * (i - j));
	if (!saved)
		return (NULL);
	i = 0;
	j++;
	while (str[j])
		saved[i++] = str[j++];
	saved[i] = 0;
	free(str);
	return (saved);
}

char	*get_next_line(int fd)
{
	char		*buffer;
	static char	*str;
	char		*line;
	char		*tmp;

	tmp = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, NULL, 0) < 0)
		return (NULL);
	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	ft_readfile(fd, buffer, tmp, &str);
	if (!str)
		return (NULL);
	line = ft_getline(str);
	str = ft_save(str);
	return (line);
}
