/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccompote <ccompote@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 12:55:31 by ccompote          #+#    #+#             */
/*   Updated: 2023/04/24 13:34:52 by ccompote         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


// int	checker_2(t_game *zop, char **argv)
// {
// 	zop->fd = open(argv[1], O_RDONLY);
// 	if (zop->fd == -1)
// 	{
// 		ft_putstr_fd("Map file not readable\n", 1);
// 		close(zop->fd);
// 		return (1);
// 	}
// 	if (!map_lines(zop->fd, zop))
// 	{
// 		ft_putstr_fd("Error\nWrong map\n", 1);
// 		close(zop->fd);
// 		return (1);
// 	}
// 	close(zop->fd);
// 	return (0);
// }

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
	if (!find_player(main_cub))
		return (0);
	rect_map(main_cub->c_map);
	return (1);
}