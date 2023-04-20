/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_before_map.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccompote <ccompote@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 16:36:12 by ccompote          #+#    #+#             */
/*   Updated: 2023/04/10 15:14:06 by ccompote         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_arg(int argc, char **argv)
{
	int	i;

	i = 0;
	if (argc != 2)
	{
		ft_putstr_fd("Wrong argument\n", 1);
		return (0);
	}
	while (argv[1][i])
		i++;
	i = i - 4;
	if (ft_strncmp(".cub", &argv[1][i], 4) != 0)
	{
		ft_putstr_fd("Wrong argument\n", 1);
		return (0);
	}
	return (1);
}

// int	checker_2(t_cub3d *zop, char **argv)
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