/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccompote <ccompote@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 18:19:11 by ccompote          #+#    #+#             */
/*   Updated: 2023/04/20 15:14:53 by ccompote         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// void	fillin(t_cub *zop, mlx_image_t *image, int i, int j)
// {
// 	mlx_image_to_window(zop->mlx, zop->floor_image, j * STEP, i * STEP);
// 	mlx_image_to_window(zop->mlx, image, j * STEP, i * STEP);
// 	if (zop->map[i][j] == 'C')
// 		zop->points_begin++;
// 	if (zop->map[i][j] == 'E')
// 	{
// 		zop->door_x = j;
// 		zop->door_y = i;
// 	}
// }

// int	fill_images(t_cub3d *zop, int x, int y)
// {
// 	int	i;
// 	int	j;

// 	i = -1;
// 	while (zop->map[++i])
// 	{
// 		j = -1;
// 		while (zop->map[i][++j] != '\n' && zop->map[i][j])
// 		{
// 			if (zop->map[i][j] == '1')
// 				fillin(zop, zop->tree_image, i, j);
// 			else if (zop->map[i][j] == 'C')
// 				fillin(zop, zop->mushroom_image, i, j);
// 			else if (zop->map[i][j] == 'E')
// 				fillin(zop, zop->door_close_image, i, j);
// 			else if (zop->map[i][j] == '0')
// 				mlx_image_to_window(zop->mlx, zop->floor_image,
// 					j * STEP, i * STEP);
// 			else if (zop->map[i][j] == 'P')
// 				fillin(zop, zop->rat_image, y, x);
// 			else
// 				return (0);
// 		}
// 	}
// 	return (1);
// }

//карту дополнить до квадрата
//найти игрока и потом поставить вместо его 0