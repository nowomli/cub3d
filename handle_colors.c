/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_colors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccompote <ccompote@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 17:26:48 by ccompote          #+#    #+#             */
/*   Updated: 2023/04/27 19:18:17 by ccompote         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	color_floor(t_map *c_map, char **tmp)
{
	c_map->f_color_r = ft_atoi(tmp[0]);
	c_map->f_color_g= ft_atoi(tmp[1]);
	c_map->f_color_b = ft_atoi(tmp[2]);
	if (c_map->f_color_r > 255 || c_map->f_color_g > 255 || c_map->f_color_b > 255)
	{
		printf("Wrong colors\n");
		tdimarr_clear(tmp);
		return (0);
	}
	tdimarr_clear(tmp);
	return (1);
}

int	color_ceiling(t_map *c_map, char **tmp)
{
	c_map->c_color_r = ft_atoi(tmp[0]);
	c_map->c_color_g = ft_atoi(tmp[1]);
	c_map->c_color_b = ft_atoi(tmp[2]);
	
	if (c_map->c_color_r > 255 || c_map->c_color_g > 255 || c_map->c_color_b > 255)
	{
		printf("Wrong colors\n");
		tdimarr_clear(tmp);
		return (0);
	}
	tdimarr_clear(tmp);
	return (1);
}

int	check_color_format(char *str)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (str[i])
	{
        if (str[i] == '\n')
        {
            if (j == 0)
                return (0);
            else
                return (1);
        }
		if (str[i] == ' ' || str[i] == '\t')
			i++;
		if (ft_isdigit(str[i]))
		{
			j = 1;
			i++;
		}
		else
			return (0);
	}
	if (j == 1)
		return (1);
	return (0);
}

int	create_colors(t_map *c_map, char *line, char c)
{
	char 	**tmp;
	int 	i;

	i = 0;
	tmp = ft_split(line, ',');
	if (!tmp)
		return (0);
	while (tmp[i])
		i++;
	if (i == 3)
	{
		if (!check_color_format(tmp[0]) || !check_color_format(tmp[1])
			|| !check_color_format(tmp[2]))
            {

				return (0);
            }
		if (c == 'C')
			return (color_ceiling(c_map, tmp));
		else if (c == 'F')
			return (color_floor(c_map, tmp));
		
	}
	return (0);
}