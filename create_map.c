/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccompote <ccompote@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 16:00:08 by ccompote          #+#    #+#             */
/*   Updated: 2023/04/23 23:09:35 by ccompote         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
	return (0);
}

// void	create_colors(t_cub3d *main_cub)
// {
// 	int		j;
// 	char 	*tmp;
// 	int 	i;
// 	int 	k;
// 	int 	ti;
// 	int		inx;

// 	j = 5;
// 	while (j < 7)
// 	{
// 		if (*main_cub->map_file[j] == 'F')
// 		{
			
// 			i = 0;
// 			main_cub->map_file[j] += 2;
// 			ti = 0;
// 			inx = 0;
// 			while (inx < 3)
// 			{
// 				while (main_cub->map_file[j][ti] != ',')
// 				{
// 					i++;
// 					ti++;
// 				}
// 				tmp = ft_calloc(i, sizeof(int));
// 				k = 0;
// 				while (k < i)
// 				{
// 					tmp[k] = *main_cub->map_file[j];
// 					k++;
// 					main_cub->map_file[j]++;
// 				}
// 				if (inx == 0)
// 					main_cub->c_map->f_color_r = ft_atoi(tmp);
// 				else if (inx == 1)
// 					main_cub->c_map->f_color_g = ft_atoi(tmp);
// 				else if (inx == 2)
// 					main_cub->c_map->f_color_b = ft_atoi(tmp);
// 				main_cub->map_file[j]++;
// 				inx++;
// 			}
// 		}
// 		else if (*main_cub->map_file[j] == 'C')
// 		{
// 			i = 0;
// 			main_cub->map_file[j] += 2;
// 			ti = 0;
// 			inx = 0;
// 			while (inx < 3)
// 			{
// 				while (main_cub->map_file[j][ti] != ',' && main_cub->map_file[j][ti] != '\0')
// 				{
// 					i++;
// 					ti++;
// 				}
// 				tmp = ft_calloc(i, sizeof(int));
// 				k = 0;
// 				while (k < i)
// 				{
// 					tmp[k] = *main_cub->map_file[j];
// 					k++;
// 					main_cub->map_file[j]++;
// 				}
// 				if (inx == 0)
// 					main_cub->c_map->c_color_r = ft_atoi(tmp);
// 				else if (inx == 1)
// 					main_cub->c_map->c_color_g = ft_atoi(tmp);
// 				else if (inx == 2)
// 					main_cub->c_map->c_color_b = ft_atoi(tmp);
// 				main_cub->map_file[j]++;
// 				inx++;
// 			}
// 		}
// 		j++;
// 	}
// }

void	create_file_arr(int fd, t_cub3d *main_cub)
{
	int i;
	
	main_cub->map_file = ft_calloc((main_cub->file_rows + 1), sizeof(char *));
	i = 0;
	while (i < main_cub->file_rows)
	{
		main_cub->map_file[i] = get_next_line(fd);
		i++;
	}
	main_cub->map_file[i] = NULL;
}

void	create_map(t_cub3d *main_cub, int inx)
{
	int	j;
	int i;
	char	*tmp;

	j = inx;
	i = 0;
	main_cub->c_map->rows = 0;
	main_cub->c_map->column = 0;
	while (main_cub->map_file[j])
	{
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

void	color_floor(t_map *c_map, int inx, char *tmp)
{
	if (inx == 0)
		c_map->f_color_r = ft_atoi(tmp);
	else if (inx == 1)
		c_map->f_color_g = ft_atoi(tmp);
	else if (inx == 2)
		c_map->f_color_b = ft_atoi(tmp);
}

void	color_ceiling(t_map *c_map, int inx, char *tmp)
{
	if (inx == 0)
		c_map->c_color_r = ft_atoi(tmp);
	else if (inx == 1)
		c_map->c_color_g = ft_atoi(tmp);
	else if (inx == 2)
	{
		printf("%s here\n", tmp);
		c_map->c_color_b = ft_atoi(tmp);
		printf("%d is\n", c_map->c_color_b);
	}
}

void	create_colors(t_map *c_map, char *line, char c)
{
	char 	*tmp;
	int 	inx;
	int 	i;
	int		ti;

	inx = 0;
	ti = 0;
	while (inx < 3)
	{
		while (line[ti] != ',')
			ti++;
		tmp = ft_calloc(ti, sizeof(int));
		i = 0;
		while (i < ti)
		{
			tmp[i] = *line;
			i++;
			line++;
		}
		if (c == 'F')
			color_floor(c_map, inx, tmp);
		else if (c == 'C')
			color_ceiling(c_map, inx, tmp);
		line++;
		inx++;
	}
}

void	parse_file(t_cub3d *main_cub)
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
		if (main_cub->map_file[i][j] == '\n')
			i++;
		else if (main_cub->map_file[i][j] == 'F')
		{
			main_cub->map_file[i] += 2;
			while (main_cub->map_file[i][j] == ' ' || main_cub->map_file[i][j] == '\t')
				main_cub->map_file[i]++;
			create_colors(main_cub->c_map, main_cub->map_file[i], 'F');
			i++;
			found++;
		}
		else if (main_cub->map_file[i][j] == 'C')
		{
			main_cub->map_file[i] += 2;
			while (main_cub->map_file[i][j] == ' ' || main_cub->map_file[i][j] == '\t')
				main_cub->map_file[i]++;
			create_colors(main_cub->c_map, main_cub->map_file[i], 'C');
			i++;
			found++;
		}
		else if (!ft_strncmp(main_cub->map_file[i], "NO ", 3)
			|| !ft_strncmp(main_cub->map_file[i], "SO ", 3)
			|| !ft_strncmp(main_cub->map_file[i], "WE ", 3)
			|| !ft_strncmp(main_cub->map_file[i], "EA ", 3))
		{
			while (main_cub->map_file[i][j] == ' ' || main_cub->map_file[i][j] == '\t')
				main_cub->map_file[i]++;
			create_images(main_cub->c_map, main_cub->map_file[i]);
			i++;
			found++;
		}
		else if (found == 6)
		{
			create_map(main_cub, i);
			break ;
		}
		else
		{
			printf("wrong\n");
			return ;
		}
	}
}

int	read_file(t_cub3d *main_cub, char **argv)
{
	int fd;	
	
	main_cub->c_map = ft_calloc(1, sizeof(t_map));
	fd = open(argv[1], O_RDONLY);
	file_lines(fd, main_cub);
	close(fd);
	fd = open(argv[1], O_RDONLY);
	create_file_arr(fd, main_cub);
	parse_file(main_cub);
	find_player(main_cub);
	rect_map(main_cub->c_map);
	// print_arg(main_cub->c_map->ar_map);
	// printf("\n");
	printf("%d %d %d f\n", main_cub->c_map->f_color_r, main_cub->c_map->f_color_g, main_cub->c_map->f_color_b);
	printf("%d %d %d c\n", main_cub->c_map->c_color_r, main_cub->c_map->c_color_g, main_cub->c_map->c_color_b);
	// printf("\n");
	close(fd);
	// if (checker_2(main_cub, argv))
	// 	return (0);
	return (1);
}