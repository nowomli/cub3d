/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inovomli <inovomli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 16:00:08 by ccompote          #+#    #+#             */
/*   Updated: 2023/04/26 15:20:19 by inovomli         ###   ########.fr       */
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
		ft_putstr_fd("Wrong path\n", 1);
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

int	create_file_arr(int fd, t_cub3d *main_cub)
{
	int i;
	
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

void	rect_map(t_map *c_map)
{
	char	**new_map;
	int		i;
	int		j;

	i = 0;
	new_map = ft_calloc(c_map->rows + 1, sizeof(char *));
	while (i < c_map->rows)
	{
		j = 0;
		new_map[i] = ft_calloc((c_map->column + 1), sizeof(char));
		while (j < c_map->column)
		{
			if (c_map->ar_map[i][j]
				&& (ft_isdigit(c_map->ar_map[i][j])
				|| ft_strchr("NSEW", c_map->ar_map[i][j]))
				&& (j <= ft_strlen(c_map->ar_map[i])))
				new_map[i][j] = c_map->ar_map[i][j];
			else
				new_map[i][j] = '1';
			j++;
		}
		new_map[i][c_map->column] = '\0';
		i++;
	}
	new_map[i] = NULL;
	c_map->ar_map = new_map;
	// print_arg(c_map->ar_map);
}


void	rect_map_null(t_map *c_map)
{
	char	**new_map;
	int		i;
	int		j;

	i = 0;
	new_map = ft_calloc(c_map->rows + 1, sizeof(char *));
	while (i < c_map->rows)
	{
		j = 0;
		new_map[i] = ft_calloc((c_map->column + 1), sizeof(char));
		while (j < c_map->column)
		{
			if (c_map->ar_map[i][j]
				&& (ft_isdigit(c_map->ar_map[i][j])
				|| ft_strchr("NSEW", c_map->ar_map[i][j]))
				&& (j <= ft_strlen(c_map->ar_map[i])))
				new_map[i][j] = c_map->ar_map[i][j];
			else
				new_map[i][j] = '0';
			j++;
		}
		new_map[i][c_map->column] = '\0';
		i++;
	}
	new_map[i] = NULL;
	c_map->ar_map = new_map;
	// print_arg(c_map->ar_map);
}

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

int	check_is_map(t_cub3d *main_cub, int i)
{
	int j;

	while (main_cub->map_file[i])
	{
		j = 0;	
		while (main_cub->map_file[i][j])
		{
			while (main_cub->map_file[i][j] == ' ' || main_cub->map_file[i][j] == '\t')
				j++;
			if (main_cub->map_file[i][j] == '1' || main_cub->map_file[i][j] == '0' 
				|| main_cub->map_file[i][j] == 'N' || main_cub->map_file[i][j] == 'W'
				|| main_cub->map_file[i][j] == 'E' || main_cub->map_file[i][j] == 'S'
				|| main_cub->map_file[i][j] == '\n')
			
				j++;
			else

				return (0);
		}
		i++;
	}
	
	return (1);
}

int	check_color_format(char *str)
{
	int i;
	int j;
	char *tmp;

	i = 0;
	j = 0;
	tmp = ft_strtrim(str, "\n");
	while (str[i])
	{
		if (str[i] == ' ' || str[i] == '\t')
			i++;
		if (ft_isdigit(str[i]))
		{
			j = 1;
			i++;
		}
		else
			return (free(tmp), 0);
	}
	if (j == 1)
		return (free(tmp), 1);
	return (free(tmp), 0);
}

int	create_colors(t_map *c_map, char *line, char c)
{
	char 	**tmp;
	int 	inx;
	int 	i;
	int		ti;

	inx = 0;
	ti = 0;
	i = 0;
	tmp = ft_split(line, ',');
	if (!tmp)
		return (0);
	while (tmp[i])
		i++;
	if (i == 3)
	{
		// if (!check_color_format(tmp[0]) || !check_color_format(tmp[1])
		// 	|| !check_color_format(tmp[2]))
		// 		return (0);
		if (c == 'C')
			return (color_ceiling(c_map, tmp));
		else if (c == 'F')
			return (color_floor(c_map, tmp));
		
	}
	return (0);
}

char	**arr_cpy(char **src, int size)
{
	int	i;
	char **dst;

	i = 0;
	dst = ft_calloc(sizeof(char *), size + 1);
	while (src[i])
	{
		dst[i] = ft_strdup(src[i]);
		i++;
	}
	dst[i] = NULL;
	return (dst);
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

int	dfs(t_cub3d *main_cub, int x, int y)
{
	if (main_cub->temp_map[y][x] == '1')
		return (1);
	if (x == 0 || y == 0 || x == main_cub->c_map->column - 1 || y == main_cub->c_map->rows - 1)
		return (0);
	else
	{
		main_cub->temp_map[y][x] = '1';
		return (dfs(main_cub, x + 1, y) && dfs(main_cub, x - 1, y) && dfs(main_cub, x, y + 1)
			&& dfs(main_cub, x, y - 1) && dfs(main_cub, x + 1, y + 1)
			&& dfs(main_cub, x + 1, y - 1) && dfs(main_cub, x - 1, y + 1)
			&& dfs(main_cub, x - 1, y - 1));
	}
}

// int	map_holes(t_cub3d *main_cub)
// {
// 	// int		i;
// 	// t_point	size;

// 	main_cub->status = 1;
// 	// i = 0;
// 	// size = (t_point){main_cub->c_map->column, main_cub->c_map->rows};
// 	main_cub->temp_map = arr_cpy(main_cub->temp_c_map->ar_map, main_cub->c_map->rows);
// 	// main_cub->temp_map[(int)main_cub->pl_pos->y][(int)main_cub->pl_pos->x] = '0';
// 	// size = (t_point){(int)main_cub->pl_pos->x, (int)main_cub->pl_pos->y};
// 	// fill(main_cub, size, '0');
// 	// if (main_cub->status == 0)
// 	// 	return (1);
// 	// return (0);

// 	int res;
// 	int		x;
// 	int		y;
// 	res = dfs(main_cub, main_cub->pl_pos->x, main_cub->pl_pos->y);
// 	return (res);
// }

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
				// i++;
				found++;
			}
			else
			{
				printf("Wrong colors there\n");
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
				// i++;
				found++;
			}
			else
			{
				printf("Wrong colors here\n");
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
				// i++;
				found++;
			}
			else

				return (0);
		}
		// else if (found == 6)
		// {
			else if (check_is_map(main_cub, i))
			{
				printf("Is map\n");
				if (found == 6)
				{
					if (!create_map(main_cub, i))
					{
						printf("Wrong config file .\n");
						return (0);
					}
					// print_arg(main_cub->c_map->ar_map);
					if (!find_player(main_cub))
					{
						printf("Wrong config file .\n");
						return (0);
					}
					// main_cub->temp_c_map = ft_calloc(1, sizeof(t_map));
					// main_cub->temp_c_map->ar_map = arr_cpy(main_cub->c_map->ar_map, main_cub->c_map->rows);
					// rect_map_null(main_cub->temp_c_map);
					// if (map_holes(main_cub))
					// {
					// 	printf("Wrong config file here\n");
					// 	return (0);
					// }
					print_arg(main_cub->c_map->ar_map);
					rect_map(main_cub->c_map);
					i = i + main_cub->c_map->rows;
					found++;
				}
				else
				{
					printf("Wrong config file there\n");
					return (0);	
				}
				// i++;
			}
			// else
			// {
			// 	printf("Wrong config file\n");
			// 	return (0);	
			// }
		// }
		// if (found > 7)
		// {
		// 	printf("%d\n", found);
		// 	printf("Wrong config file here\n");
		// 	return (0);
		// }
		// else
		// {
		// 	printf("%s\n", main_cub->map_file[i]);
		// 	printf("Wrong config file there\n");
		// 	return (0);
		// }
		i++;
		// printf("%s\n", main_cub->map_file[i]);
	}
	// printf("%d\n", found);
	// if (found != 7)
	// {
				
	// 		// printf("%d\n", found)
	// 		printf("Wrong config file zop\n");
	// 		return (0);
		
	// }
		rect_map(main_cub->c_map);
		find_player(main_cub);
	print_arg(main_cub->c_map->ar_map);
	return (1);
}

