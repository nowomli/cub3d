/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccompote <ccompote@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 12:55:31 by ccompote          #+#    #+#             */
/*   Updated: 2023/04/30 16:16:05 by ccompote         ###   ########.fr       */
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

int	create_file_arr(int fd, t_cub3d *main_cub)
{
	int	i;

	main_cub->map_file = ft_calloc((main_cub->file_rows + 1), sizeof(char *));
	if (!main_cub->map_file)
		return (0);
	i = 0;
	while (i < main_cub->file_rows)
	{
		main_cub->map_file[i] = get_next_line(fd);
		i++;
	}
	main_cub->map_file[i] = NULL;
	return (1);
}

int	checker(t_cub3d *main_cub, char **argv)
{
	int	fd;

	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{
		printf("Error\nWrong config file\n");
		close(fd);
		return (0);
	}
	if (!file_lines(fd, main_cub))
	{
		printf("Error\nEmpty file\n");
		close(fd);
		return (0);
	}
	close(fd);
	fd = open(argv[1], O_RDONLY);
	if (!create_file_arr(fd, main_cub))
	{
		close(fd);
		return (0);
	}
	close(fd);
	return (1);
}

int	check_image_files_two(t_cub3d *main_cub)
{
	int	fd;

	fd = open(main_cub->c_map->west_path, O_RDONLY);
	if (fd == -1)
	{
		printf("Error\nWrong path\n");
		close(fd);
		return (0);
	}
	close(fd);
	fd = open(main_cub->c_map->east_path, O_RDONLY);
	if (fd == -1)
	{
		printf("Error\nWrong path\n");
		close(fd);
		return (0);
	}
	close(fd);
	return (1);
}

int	check_image_files_one(t_cub3d *main_cub)
{
	int	fd;

	fd = open(main_cub->c_map->north_path, O_RDONLY);
	if (fd == -1)
	{
		printf("Error\nWrong path\n");
		close(fd);
		return (0);
	}
	close(fd);
	fd = open(main_cub->c_map->south_path, O_RDONLY);
	if (fd == -1)
	{
		printf("Error\nWrong path\n");
		close(fd);
		return (0);
	}
	close(fd);
	if (!check_image_files_two(main_cub))
		return (0);
	return (1);
}

int	read_file(t_cub3d *main_cub, char **argv)
{
	main_cub->c_map = ft_calloc(1, sizeof(t_map));
	if (!checker(main_cub, argv))
		return (free(main_cub->c_map), 0);
	if (!parse_file(main_cub))
		return (free_map(main_cub), 0);
	if (!check_image_files_one(main_cub))
	{
		free_map(main_cub);
		free(main_cub->pl_pos);
		return (0);
	}
	return (1);
}
