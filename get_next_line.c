/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccompote <ccompote@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 15:01:31 by ccompote          #+#    #+#             */
/*   Updated: 2023/04/09 16:02:13 by ccompote         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*ft_dup(char *str)
{
	char	*res;
	int		i;

	i = 0;
	if (!str[i])
		return (NULL);
	while (str[i] && str[i] != '\n')
		i++;
	res = (char *)malloc(sizeof(char) * (i + 2));
	if (res == NULL)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '\n')
	{
		res[i] = str[i];
		i++;
	}
	if (str[i] == '\n')
	{
		res[i] = str[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}

char	*ft_read(int fd, char *progress)
{
	char	*buf;
	int		res_read;

	buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (NULL);
	res_read = 1;
	while (!gn_strchr(progress, '\n') && res_read != 0)
	{
		res_read = read(fd, buf, BUFFER_SIZE);
		if (res_read == -1)
		{
			free(buf);
			return (NULL);
		}
		buf[res_read] = '\0';
		progress = gn_strjoin(progress, buf);
	}
	free(buf);
	return (progress);
}

char	*ft_next_line(char *progress)
{
	int		i;
	int		j;
	char	*s;

	i = 0;
	j = 0;
	while (progress[i] && progress[i] != '\n')
		i++;
	if (!progress[i])
	{
		free(progress);
		return (NULL);
	}
	s = (char *)malloc(sizeof(char) * (ft_strlen(progress) - i + 1));
	if (!s)
		return (NULL);
	i++;
	while (progress[i])
		s[j++] = progress[i++];
	free(progress);
	s[j] = '\0';
	return (s);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*progress;

	if (fd < 0 || BUFFER_SIZE < 1 || (read(fd, NULL, 0) < 0))
		return (NULL);
	progress = ft_read(fd, progress);
	if (progress == NULL)
		return (NULL);
	line = ft_dup(progress);
	progress = ft_next_line(progress);
	return (line);
}
