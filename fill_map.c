/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccompote <ccompote@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 16:35:10 by ccompote          #+#    #+#             */
/*   Updated: 2023/04/28 15:31:55 by ccompote         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	rect_map(t_map *c_map)
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
				new_map[i][j] = '1';
			j++;
		}
		new_map[i][c_map->column] = '\0';
		i++;
	}
	new_map[i] = NULL;
	tdimarr_clear(c_map->ar_map);
	c_map->ar_map = new_map;
}

int	find_pl(t_map *map, int *x, int *y)
{
	bool	found;

	*y = 0;
	found = false;
	while (*y < map->rows && !found)
	{
		*x = 0;
		while (*x < map->column && !found)
		{
			if (map->temp_map[*y][*x] == 'N' || map->temp_map[*y][*x] == 'S'
				|| map->temp_map[*y][*x] == 'W' || map->temp_map[*y][*x] == 'E')
			{
				found = true;
				map->temp_map[*y][*x] = '0';
			}
			if (!found)
				*x = *x + 1;
		}
		if (!found)
			*y = *y + 1;
	}
	if (!found)
		return (0);
	return (1);
}

int	find_player(t_cub3d *main_cub)
{
	int	i;
	int	j;
	static int	found = 0;

	i = -1;
	while (main_cub->c_map->ar_map[++i])
	{
		j = -1;
		while (main_cub->c_map->ar_map[i][++j] != '\n' && main_cub->c_map->ar_map[i][j])
		{
			if (main_cub->c_map->ar_map[i][j] == 'N' || main_cub->c_map->ar_map[i][j] == 'S' || main_cub->c_map->ar_map[i][j] == 'W' || main_cub->c_map->ar_map[i][j] == 'E')
			{
				found++;
				main_cub->pl_pos = ft_calloc(1, sizeof(t_player));
				main_cub->pl_pos->x = j + 0.5f;
				main_cub->pl_pos->y = i + 0.5f;
				if (main_cub->c_map->ar_map[i][j] == 'N')
					main_cub->pl_pos->angle = 1.5 * M_PI;
				else if (main_cub->c_map->ar_map[i][j] == 'S')
					main_cub->pl_pos->angle = 0.5 * M_PI;
				else if (main_cub->c_map->ar_map[i][j] == 'W')
					main_cub->pl_pos->angle = 0;
				else if (main_cub->c_map->ar_map[i][j] == 'E')
					main_cub->pl_pos->angle = 1 * M_PI;
				main_cub->c_map->ar_map[i][j] = '0';
			}
		}
	}
	if (found != 1)
	{
		return (0);
	}
	return (1);
}


int	check_is_map(t_cub3d *main_cub, int i, int y)
{
	int j;

	y++;
	while (main_cub->map_file[i])
	{
		j = 0;	
		while (main_cub->map_file[i][j])
		{
			while (main_cub->map_file[i][j] == ' ' || main_cub->map_file[i][j] == '\t')
				j++;
			if (main_cub->map_file[i][j] == '1' || main_cub->map_file[i][j] == '0' 
				|| main_cub->map_file[i][j] == 'N' || main_cub->map_file[i][j] == 'W'
				|| main_cub->map_file[i][j] == 'E' || main_cub->map_file[i][j] == 'S'
				|| main_cub->map_file[i][j] == '\n')
			
				j++;
			else

				return (0);
		}
		i++;
	}
	return (1);
}