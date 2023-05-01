/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccompote <ccompote@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 19:32:08 by ccompote          #+#    #+#             */
/*   Updated: 2023/05/01 11:42:38 by ccompote         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	file_lines(int fd, t_cub3d *main_cub)
{
	int		i;
	char	*str;

	i = 0;
	str = get_next_line(fd);
	if (str == NULL)
		return (0);
	i++;
	while (str)
	{
		free(str);
		str = get_next_line(fd);
		if (!str)
			break ;
		i++;
	}
	main_cub->file_rows = i;
	return (1);
}

void	rect_map_null(t_map *c_map)
{
	int		i;
	int		j;

	i = 0;
	c_map->temp_map = ft_calloc(c_map->rows + 1, sizeof(char *));
	while (i < c_map->rows)
	{
		j = 0;
		c_map->temp_map[i] = ft_calloc((c_map->column + 1), sizeof(char));
		while (j < c_map->column)
		{
			if (c_map->ar_map[i][j] && (ft_isdigit(c_map->ar_map[i][j])
				|| ft_strchr("NSEW", c_map->ar_map[i][j]))
				&& (j <= ft_strlen(c_map->ar_map[i])))
				c_map->temp_map[i][j] = c_map->ar_map[i][j];
			else
				c_map->temp_map[i][j] = '0';
			j++;
		}
		c_map->temp_map[i][c_map->column] = '\0';
		i++;
	}
	c_map->temp_map[i] = NULL;
}

char	**arr_cpy(char **src, int size)
{
	int		i;
	char	**dst;

	i = 0;
	dst = ft_calloc(sizeof(char *), size + 1);
	while (src[i])
	{
		dst[i] = ft_strdup(src[i]);
		i++;
	}
	dst[i] = NULL;
	return (dst);
}

bool	dfs(t_map *map, int x, int y)
{
	if (map->temp_map[y][x] == '1')
		return (true);
	if (x == 0 || y == 0 || x == map->column - 1 || y == map->rows - 1)
		return (false);
	else
	{
		map->temp_map[y][x] = '1';
		return (dfs(map, x + 1, y) && dfs(map, x - 1, y) && dfs(map, x, y + 1)
			&& dfs(map, x, y - 1) && dfs(map, x + 1, y + 1)
			&& dfs(map, x + 1, y - 1) && dfs(map, x - 1, y + 1)
			&& dfs(map, x - 1, y - 1));
	}
}

int	map_holes(t_map *map)
{
	bool	res;
	int		x;
	int		y;

	rect_map_null(map);
	if (!find_pl(map, &x, &y))
	{
		tdimarr_clear(map->temp_map);
		return (0);
	}
	res = dfs(map, x, y);
	tdimarr_clear(map->temp_map);
	return (res);
}
