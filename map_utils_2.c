/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccompote <ccompote@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 11:36:17 by ccompote          #+#    #+#             */
/*   Updated: 2023/05/01 11:37:12 by ccompote         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_map(t_cub3d *m_cub)
{
	if (m_cub->map_file)
		tdimarr_clear(m_cub->map_file);
	if (m_cub->c_map->ar_map)
		tdimarr_clear(m_cub->c_map->ar_map);
	if (m_cub->c_map->north_path)
		free(m_cub->c_map->north_path);
	if (m_cub->c_map->south_path)
		free(m_cub->c_map->south_path);
	if (m_cub->c_map->west_path)
		free(m_cub->c_map->west_path);
	if (m_cub->c_map->east_path)
		free(m_cub->c_map->east_path);
	if (m_cub->c_map)
		free(m_cub->c_map);
}

int	check_png(char *path)
{
	int	i;

	i = 0;
	while (path[i])
		i++;
	i = i - 5;
	if (ft_strncmp(".png", &path[i], 4) != 0)
	{
		return (0);
	}
	return (1);
}
