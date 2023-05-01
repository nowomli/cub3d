/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccompote <ccompote@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 16:00:08 by ccompote          #+#    #+#             */
/*   Updated: 2023/05/01 00:06:01 by ccompote         ###   ########.fr       */
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

void	im_north(t_map *c_map, char *line)
{
	int		line_len;
	char	*tmp;
	int		i;

	if (!c_map->north_path)
	{
		i = 0;
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
	else
		return ;
}

void	im_south(t_map *c_map, char *line)
{
	int		line_len;
	char	*tmp;
	int		i;

	if (!c_map->south_path)
	{
		i = 0;
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
	else
		return ;
}

void	im_west(t_map *c_map, char *line)
{
	int		line_len;
	char	*tmp;
	int		i;

	if (!c_map->west_path)
	{
		i = 0;
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
	else
		return ;
}

void	im_east(t_map *c_map, char *line)
{
	int		line_len;
	char	*tmp;
	int		i;

	if (!c_map->east_path)
	{
		i = 0;
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
	else
		return ;
}

int	create_images(t_map *c_map, char *line)
{
	if (!check_png(line))
		return (0);
	if (!ft_strncmp(line, "NO ", 3))
		im_north(c_map, line);
	else if (!ft_strncmp(line, "SO ", 3))
		im_south(c_map, line);
	else if (!ft_strncmp(line, "WE ", 3))
		im_west(c_map, line);
	else if (!ft_strncmp(line, "EA ", 3))
		im_east(c_map, line);
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
			return (printf("Error\nWrong config file in holes\n"), 0);
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
			return (printf("Error\nWrong config file color\n"), 0);
	}
	else if (find_im_id(cub))
	{
		if (create_images(cub->c_map, cub->map_file[cub->i_file]))
			cub->found_items++;
		else
			return (printf("Error\nWrong config file,,,,,\n"), 0);
	}
	else if (check_is_map(cub, cub->i_file, cub->file_rows))
	{
		if (!parse_map(cub))
			return (0);
	}
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
		printf("Error\nWrong config file here ..\n");
		return (0);
	}
	return (1);
}
