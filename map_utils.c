/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccompote <ccompote@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 19:32:08 by ccompote          #+#    #+#             */
/*   Updated: 2023/04/28 17:31:41 by ccompote         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	rect_map_null(t_map *c_map)
{
	char	**new_map;
	int		i;
	int		j;

	i = 0;
	new_map = ft_calloc(c_map->rows + 1, sizeof(char *));
	while (i < c_map->rows)
	{
		j = 0;
		new_map[i] = ft_calloc((c_map->column + 1), sizeof(char));
		while (j < c_map->column)
		{
			if (c_map->ar_map[i][j]
				&& (ft_isdigit(c_map->ar_map[i][j])
				|| ft_strchr("NSEW", c_map->ar_map[i][j]))
				&& (j <= ft_strlen(c_map->ar_map[i])))
				new_map[i][j] = c_map->ar_map[i][j];
			else
				new_map[i][j] = '0';
			j++;
		}
		new_map[i][c_map->column] = '\0';
		i++;
	}
	new_map[i] = NULL;
	tdimarr_clear(c_map->temp_map);
	c_map->temp_map = new_map;
}

char	**arr_cpy(char **src, int size)
{
	int	i;
	char **dst;

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
	
	map->temp_map = arr_cpy(map->ar_map, map->rows);
	// main_cub->temp_c_map = ft_calloc(1, sizeof(t_map));
	// main_cub->temp_c_map->ar_map = arr_cpy(main_cub->c_map->ar_map, main_cub->c_map->rows);
	// main_cub->temp_c_map->rows = main_cub->c_map->rows;
	// main_cub->temp_c_map->column = main_cub->c_map->column;
	// rect_map_null(main_cub->temp_c_map);
	rect_map_null(map);
	if (!find_pl(map, &x, &y))
	{
		tdimarr_clear(map->temp_map);
		return (0);
	}
	// print_arg(main_cub->temp_c_map->ar_map);
	// printf("%f%f\n", main_cub->pl_pos->x, main_cub->pl_pos->y);
	// int		x;
	// int		y;
	res = dfs(map, x, y);
	tdimarr_clear(map->temp_map);
	return (res);
}