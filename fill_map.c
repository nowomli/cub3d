/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccompote <ccompote@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 16:35:10 by ccompote          #+#    #+#             */
/*   Updated: 2023/04/25 13:57:16 by ccompote         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "cub3d.h"

int	find_player(t_cub3d *main_cub)
{
	int	i;
	int	j;
	int	found;

	i = -1;
	found = 0;
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
		printf("Player position wrong\n");
		return (0);
	}
	return (1);
}

// менять размер окна