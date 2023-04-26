/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccompote <ccompote@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 12:55:31 by ccompote          #+#    #+#             */
/*   Updated: 2023/04/25 18:14:01 by ccompote         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


int	checker(t_cub3d *main_cub, char **argv)
{
	int fd;
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{
		printf("Wrong config file\n");
		close(fd);
		return (0);
	}
	if (!file_lines(fd, main_cub))
	{
		printf("Empty file\n");
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
int	read_file(t_cub3d *main_cub, char **argv)
{
	int fd;	
	
	main_cub->c_map = ft_calloc(1, sizeof(t_map));
	if (!checker(main_cub, argv))
		return (0);
	if (!parse_file(main_cub))
		return (0);
	fd = open(main_cub->c_map->north_path, O_RDONLY);
	if (fd == -1)
	{
		printf("Wrong path\n");
		return (0);
	}
	return (1);
}