/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccompote <ccompote@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 16:00:08 by ccompote          #+#    #+#             */
/*   Updated: 2023/05/01 11:44:10 by ccompote         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	create_map(t_cub3d *cub, int inx)
{
	int	j;
	int	i;

	j = inx;
	i = 0;
	cub->c_map->rows = 0;
	cub->c_map->column = 0;
	while (cub->map_file[j])
	{
		if (ft_strlen_no_nl(cub->map_file[j]) == 0)
			return (0);
		if (ft_strlen_no_nl(cub->map_file[j]) > cub->c_map->column)
			cub->c_map->column = ft_strlen_no_nl(cub->map_file[j]);
		j++;
		cub->c_map->rows++;
	}
	cub->c_map->ar_map = ft_calloc(cub->c_map->rows + 1, sizeof(char *));
	j = inx;
	while (i < cub->c_map->rows)
	{
		cub->c_map->ar_map[i] = ft_strdup(cub->map_file[j++]);
		i++;
	}
	cub->c_map->ar_map[i] = NULL;
	return (1);
}

int	parse_map(t_cub3d *cub)
{
	if (cub->found_items == 6)
	{
		if (!create_map(cub, cub->i_file))
			return (printf("Error\nWrong config file\n"), 0);
		if (!map_holes(cub->c_map))
			return (printf("Error\nWrong config file\n"), 0);
		if (!find_player(cub))
		{
			printf("Error\nWrong config file\n");
			free(cub->pl_pos);
			return (0);
		}
		rect_map(cub->c_map);
		cub->i_file = cub->i_file + cub->c_map->rows;
		cub->found_items++;
		cub->map_found = 1;
	}
	else
		return (printf("Error\nWrong config file\n"), 0);
	return (1);
}

int	find_im_id(t_cub3d *cub)
{
	if (!ft_strncmp(cub->map_file[cub->i_file], "NO ", 3)
		|| !ft_strncmp(cub->map_file[cub->i_file], "SO ", 3)
		|| !ft_strncmp(cub->map_file[cub->i_file], "WE ", 3)
		|| !ft_strncmp(cub->map_file[cub->i_file], "EA ", 3))
		return (1);
	return (0);
}

int	parse_elem(t_cub3d *cub, int j)
{
	if (cub->map_file[cub->i_file][j] == 'F'
		|| cub->map_file[cub->i_file][j] == 'C')
	{
		if (create_colors(cub->c_map, cub->map_file[cub->i_file],
				cub->map_file[cub->i_file][j]))
			cub->found_items++;
		else
			return (printf("Error\nWrong config file\n"), 0);
	}
	else if (find_im_id(cub))
	{
		if (create_images(cub->c_map, cub->map_file[cub->i_file]))
			cub->found_items++;
		else
			return (printf("Error\nWrong config file\n"), 0);
	}
	else if (check_is_map(cub, cub->i_file, cub->file_rows))
	{
		if (!parse_map(cub))
			return (0);
	}
	else
		return (printf("Error\nWrong config file\n"), 0);
	return (1);
}

int	parse_file(t_cub3d *cub)
{
	int	j;

	cub->i_file = 0;
	cub->found_items = 0;
	while (cub->i_file < cub->file_rows)
	{
		j = 0;
		while (cub->map_file[cub->i_file][j] == ' '
			|| cub->map_file[cub->i_file][j] == '\t')
			j++;
		while (cub->map_file[cub->i_file][j] == '\n')
			cub->i_file++;
		if (!parse_elem(cub, j))
			return (0);
		cub->i_file++;
	}
	if (cub->found_items != 7 || cub->map_found != 1)
	{
		printf("Error\nWrong config file\n");
		return (0);
	}
	return (1);
}
