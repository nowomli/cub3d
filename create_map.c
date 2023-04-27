/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccompote <ccompote@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 16:00:08 by ccompote          #+#    #+#             */
/*   Updated: 2023/04/27 19:47:25 by ccompote         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

int	file_lines(int fd, t_cub3d *main_cub)
{
	int		i;
	char	*str;

	i = 0;
	str = get_next_line(fd);
	if (str == NULL)
		return (0);
	i++;
	while (str)
	{
		free(str);
		str = get_next_line(fd);
		if (!str)
			break ;
		i++;	
	}
	main_cub->file_rows = i;
	return (1);
}

int	create_images(t_map *c_map, char *line)
{
	char	*tmp;
	int		i;
	int 	line_len;

	i = 0;
	if (!check_png(line))
		return (0);
	if (!ft_strncmp(line, "NO ", 3))
	{
		line += 3;
		while (*line == ' ' || *line == '\n')
			line++;
		line_len = ft_strlen(line);
		tmp = ft_calloc((ft_strlen(line) - 1), sizeof(char));
		while (i < (line_len - 1))
		{
			tmp[i] = *line;
			i++;
			line++;
		}
		tmp[i] = '\0';
		c_map->north_path = ft_strdup(tmp);
		free(tmp);
	}
	else if (!ft_strncmp(line, "SO ", 3))
	{
		line += 3;
		while (*line == ' ' || *line == '\n')
			line++;
		line_len = ft_strlen(line);
		tmp = ft_calloc((ft_strlen(line) - 1), sizeof(char));
		while (i < (line_len - 1))
		{
			tmp[i] = *line;
			i++;
			line++;
		}
		tmp[i] = '\0';
		c_map->south_path = ft_strdup(tmp);
		free(tmp);
	}
	else if (!ft_strncmp(line, "WE ", 3))
	{
		line += 3;
		while (*line == ' ' || *line == '\n')
			line++;
		line_len = ft_strlen(line);
		tmp = ft_calloc((ft_strlen(line) - 1), sizeof(char));
		while (i < (line_len - 1))
		{
			tmp[i] = *line;
			i++;
			line++;
		}
		tmp[i] = '\0';
		c_map->west_path = ft_strdup(tmp);
		free(tmp);
	}
	else if (!ft_strncmp(line, "EA ", 3))
	{
		line += 3;
		while (*line == ' ' || *line == '\n')
			line++;
		line_len = ft_strlen(line);
		tmp = ft_calloc((ft_strlen(line) - 1), sizeof(char));
		while (i < (line_len - 1))
		{
			tmp[i] = *line;
			i++;
			line++;
		}
		tmp[i] = '\0';
		c_map->east_path = ft_strdup(tmp);
		free(tmp);
	}
	return (1);
}





// void	fill(t_cub3d *main_cub, t_point cur, char to_fill)
// {
// 	if (!ft_strchr("01F", main_cub->temp_map[cur.y][cur.x])
// 		|| (main_cub->temp_map[cur.y][0] == '0')
// 		|| ((main_cub->temp_map[cur.y][cur.x] == '0')
// 			&& cur.y == 0)
// 		|| ((main_cub->temp_map[cur.y][cur.x] == '0')
// 			&& (!main_cub->temp_map[cur.y][cur.x + 1])))
// 		main_cub->status = 0;
// 	else if (cur.x < 0 || cur.x >= (int)ft_strlen(main_cub->temp_map[cur.y])
// 		|| cur.y < 0 || cur.y >= main_cub->c_map->rows
// 		|| main_cub->temp_map[cur.y][cur.x] != to_fill)
// 		return ;
// 	main_cub->temp_map[cur.y][cur.x] = 'F';
// 	fill(main_cub, (t_point){cur.x - 1, cur.y}, to_fill);
// 	fill(main_cub, (t_point){cur.x + 1, cur.y}, to_fill);
// 	fill(main_cub, (t_point){cur.x, cur.y - 1}, to_fill);
// 	fill(main_cub, (t_point){cur.x, cur.y + 1}, to_fill);
// }

int	create_map(t_cub3d *main_cub, int inx)
{
	int	j;
	int i;

	j = inx;
	i = 0;
	main_cub->c_map->rows = 0;
	main_cub->c_map->column = 0;
	while (main_cub->map_file[j])
	{
		if (ft_strlen_no_nl(main_cub->map_file[j]) == 0)
			return (0);
		if (ft_strlen_no_nl(main_cub->map_file[j]) > main_cub->c_map->column)
			main_cub->c_map->column = ft_strlen_no_nl(main_cub->map_file[j]);
		j++;
		main_cub->c_map->rows++;
	}
	main_cub->c_map->ar_map = ft_calloc(main_cub->c_map->rows + 1, sizeof(char *));
	j = inx;
	while (i < main_cub->c_map->rows)
	{
		main_cub->c_map->ar_map[i] = ft_strdup(main_cub->map_file[j]);
		i++;
		j++;
	}
	main_cub->c_map->ar_map[i] = NULL;
	return (1);
}


int	parse_file(t_cub3d *main_cub)
{
	int	i;
	int	j;
	int found;

	i = 0;
	found = 0;
	while (i < main_cub->file_rows)
	{
		j = 0;
		while (main_cub->map_file[i][j] == ' ' || main_cub->map_file[i][j] == '\t')
			main_cub->map_file[i]++;
		while (main_cub->map_file[i][j] == '\n')
			i++;
		if (main_cub->map_file[i][j] == 'F')
		{
			main_cub->map_file[i] += 2;
			while (main_cub->map_file[i][j] == ' ' || main_cub->map_file[i][j] == '\t')
				main_cub->map_file[i]++;
			if (create_colors(main_cub->c_map, main_cub->map_file[i], 'F'))
			{
				found++;
			}
			else
			{
				printf("Error\nWrong config file color\n");
				return (0);
			}
		}
		else if (main_cub->map_file[i][j] == 'C')
		{
			main_cub->map_file[i] += 2;
			while (main_cub->map_file[i][j] == ' ' || main_cub->map_file[i][j] == '\t')
				main_cub->map_file[i]++;
			if (create_colors(main_cub->c_map, main_cub->map_file[i], 'C'))
			{
				found++;
			}
			else
			{
				printf("Error\nWrong config file color\n");
				return (0);
			}
		}
		else if (!ft_strncmp(main_cub->map_file[i], "NO ", 3)
			|| !ft_strncmp(main_cub->map_file[i], "SO ", 3)
			|| !ft_strncmp(main_cub->map_file[i], "WE ", 3)
			|| !ft_strncmp(main_cub->map_file[i], "EA ", 3))
		{
			if (create_images(main_cub->c_map, main_cub->map_file[i]))
			{
				found++;
			}
			else
			{
				printf("Error\nWrong config file\n");
				return (0);
			}

		}

		else if (check_is_map(main_cub, i, main_cub->file_rows))
		{
			if (found == 6)
			{
				if (!create_map(main_cub, i))
				{
					printf("Error\nWrong config file\n");
					return (0);
				}
				if (!map_holes(main_cub->c_map))
				{
					printf("Error\nWrong config file here\n");
					return (0);
				}
				if (!find_player(main_cub))
				{
					printf("Wrong config file\n");
					return (0);
				}
				rect_map(main_cub->c_map);
				i = i + main_cub->c_map->rows;
				found++;
				main_cub->map_found = 1;
			}
			else
			{
				printf("Error\nWrong config file\n");
				return (0);	
			}
		}
		i++;
	}

	if (found != 7 || main_cub->map_found != 1)
	{
		printf("Error\nWrong config file\n");
		return (0);
	}

	return (1);
}

