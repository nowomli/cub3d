/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_images.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccompote <ccompote@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 11:33:26 by ccompote          #+#    #+#             */
/*   Updated: 2023/05/01 11:42:13 by ccompote         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	im_north(t_map *c_map, char *line)
{
	int		line_len;
	char	*tmp;
	int		i;

	if (!c_map->north_path)
	{
		i = 0;
		line += 3;
		while (*line == ' ' || *line == '\n')
			line++;
		line_len = ft_strlen(line);
		tmp = ft_calloc((ft_strlen(line) - 1), sizeof(char));
		while (i < (line_len - 1))
		{
			tmp[i] = *line;
			i++;
			line++;
		}
		tmp[i] = '\0';
		c_map->north_path = ft_strdup(tmp);
		free(tmp);
	}
	else
		return ;
}

void	im_south(t_map *c_map, char *line)
{
	int		line_len;
	char	*tmp;
	int		i;

	if (!c_map->south_path)
	{
		i = 0;
		line += 3;
		while (*line == ' ' || *line == '\n')
			line++;
		line_len = ft_strlen(line);
		tmp = ft_calloc((ft_strlen(line) - 1), sizeof(char));
		while (i < (line_len - 1))
		{
			tmp[i] = *line;
			i++;
			line++;
		}
		tmp[i] = '\0';
		c_map->south_path = ft_strdup(tmp);
		free(tmp);
	}
	else
		return ;
}

void	im_west(t_map *c_map, char *line)
{
	int		line_len;
	char	*tmp;
	int		i;

	if (!c_map->west_path)
	{
		i = 0;
		line += 3;
		while (*line == ' ' || *line == '\n')
			line++;
		line_len = ft_strlen(line);
		tmp = ft_calloc((ft_strlen(line) - 1), sizeof(char));
		while (i < (line_len - 1))
		{
			tmp[i] = *line;
			i++;
			line++;
		}
		tmp[i] = '\0';
		c_map->west_path = ft_strdup(tmp);
		free(tmp);
	}
	else
		return ;
}

void	im_east(t_map *c_map, char *line)
{
	int		line_len;
	char	*tmp;
	int		i;

	if (!c_map->east_path)
	{
		i = 0;
		line += 3;
		while (*line == ' ' || *line == '\n')
			line++;
		line_len = ft_strlen(line);
		tmp = ft_calloc((ft_strlen(line) - 1), sizeof(char));
		while (i < (line_len - 1))
		{
			tmp[i] = *line;
			i++;
			line++;
		}
		tmp[i] = '\0';
		c_map->east_path = ft_strdup(tmp);
		free(tmp);
	}
	else
		return ;
}

int	create_images(t_map *c_map, char *line)
{
	if (!check_png(line))
		return (0);
	if (!ft_strncmp(line, "NO ", 3))
		im_north(c_map, line);
	else if (!ft_strncmp(line, "SO ", 3))
		im_south(c_map, line);
	else if (!ft_strncmp(line, "WE ", 3))
		im_west(c_map, line);
	else if (!ft_strncmp(line, "EA ", 3))
		im_east(c_map, line);
	return (1);
}
