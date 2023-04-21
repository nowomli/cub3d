/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccompote <ccompote@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 16:00:08 by ccompote          #+#    #+#             */
/*   Updated: 2023/04/21 16:17:55 by ccompote         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// int	map_lines(int fd, t_cub3d *main_cub)
// {
// 	int		i;
// 	char	*str;

// 	i = 0;
// 	str = get_next_line(main_cub->fd);
// 	if (str == NULL)
// 		return (0);
// 	main_cub->c_map->columns = ft_strlen_no_nl(str);
// 	i++;
// 	while (str)
// 	{
// 		free(str);
// 		str = get_next_line(main_cub->fd);
// 		if (!str)
// 			break ;
// 		i++;
// 		if (ft_strlen_no_nl(str) != main_cub->c_map->columns)
// 		{
// 			free(str);
// 			return (0);
// 		}	
// 	}
// 	main_cub->c_map->rows = i;
// 	return (1);
// }

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

int	create_images(t_cub3d *main_cub)
{
	char	*tmp;
	int		i;
	int 	j;

	j = 0;
	while (j < 4)
	{
		i = 0;
		if (!ft_strncmp(main_cub->map_file[j], "NO", 2))
		{
			tmp = ft_calloc((ft_strlen(main_cub->map_file[j]) - 1 - 3), sizeof(char));
			main_cub->map_file[j] += 3;
			while (i < (ft_strlen(main_cub->map_file[j]) - 1))
			{
				tmp[i] = main_cub->map_file[j][i];
				i++;
			}
			tmp[i] = '\0';
			main_cub->c_map->north_path = ft_strdup(tmp);
			free(tmp);
		}
		else if (!ft_strncmp(main_cub->map_file[j], "SO", 2))
		{
			tmp = ft_calloc((ft_strlen(main_cub->map_file[j]) - 1 - 3), sizeof(char));
			main_cub->map_file[j] += 3;
			while (i < (ft_strlen(main_cub->map_file[j]) - 1))
			{
				tmp[i] = main_cub->map_file[j][i];
				i++;
			}
			tmp[i] = '\0';
			main_cub->c_map->south_path = ft_strdup(tmp);
			free(tmp);
		}
		else if (!ft_strncmp(main_cub->map_file[j], "WE", 2))
		{
			tmp = ft_calloc((ft_strlen(main_cub->map_file[j]) - 1 - 3), sizeof(char));
			main_cub->map_file[j] += 3;
			while (i < (ft_strlen(main_cub->map_file[j]) - 1))
			{
				tmp[i] = main_cub->map_file[j][i];
				i++;
			}
			tmp[i] = '\0';
			main_cub->c_map->west_path = ft_strdup(tmp);
			free(tmp);
		}
		else if (!ft_strncmp(main_cub->map_file[j], "EA", 2))
		{
			tmp = ft_calloc((ft_strlen(main_cub->map_file[j]) - 1 - 3), sizeof(char));
			main_cub->map_file[j] += 3;
			while (i < (ft_strlen(main_cub->map_file[j]) - 1))
			{
				tmp[i] = main_cub->map_file[j][i];
				i++;
			}
			tmp[i] = '\0';
			main_cub->c_map->east_path = ft_strdup(tmp);
			free(tmp);
		}
		j++;
	}
	return (0);
}

void	create_colors(t_cub3d *main_cub)
{
	int		j;
	char 	*tmp;
	int 	i;
	int 	k;
	int 	ti;
	int		inx;

	j = 5;
	while (j < 7)
	{
		if (*main_cub->map_file[j] == 'F')
		{
			
			i = 0;
			main_cub->map_file[j] += 2;
			ti = 0;
			inx = 0;
			while (inx < 3)
			{
				while (main_cub->map_file[j][ti] != ',')
				{
					i++;
					ti++;
				}
				tmp = ft_calloc(i, sizeof(int));
				k = 0;
				while (k < i)
				{
					tmp[k] = *main_cub->map_file[j];
					k++;
					main_cub->map_file[j]++;
				}
				if (inx == 0)
					main_cub->c_map->f_color_r = ft_atoi(tmp);
				else if (inx == 1)
					main_cub->c_map->f_color_g = ft_atoi(tmp);
				else if (inx == 2)
					main_cub->c_map->f_color_b = ft_atoi(tmp);
				main_cub->map_file[j]++;
				inx++;
			}
		}
		else if (*main_cub->map_file[j] == 'C')
		{
			i = 0;
			main_cub->map_file[j] += 2;
			ti = 0;
			inx = 0;
			while (inx < 3)
			{
				while (main_cub->map_file[j][ti] != ',' && main_cub->map_file[j][ti] != '\0')
				{
					i++;
					ti++;
				}
				tmp = ft_calloc(i, sizeof(int));
				k = 0;
				while (k < i)
				{
					tmp[k] = *main_cub->map_file[j];
					k++;
					main_cub->map_file[j]++;
				}
				if (inx == 0)
					main_cub->c_map->c_color_r = ft_atoi(tmp);
				else if (inx == 1)
					main_cub->c_map->c_color_g = ft_atoi(tmp);
				else if (inx == 2)
					main_cub->c_map->c_color_b = ft_atoi(tmp);
				main_cub->map_file[j]++;
				inx++;
			}
		}
		j++;
	}
}

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

void	create_map(t_cub3d *main_cub)
{
	int	j;
	int i;
	char	*tmp;

	j = 8;
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
	j = 8;
	while (i < main_cub->c_map->rows)
	{
		main_cub->c_map->ar_map[i] = ft_strdup(main_cub->map_file[j]);
		// printf("%s", main_cub->c_map->ar_map[i]);
		i++;
		j++;
	}
	main_cub->c_map->ar_map[i] = NULL;
}

// void	create_map(t_cub3d *main_cub)
// {
// 	int	j;
// 	int i;
// 	char	*tmp;
// 	int 	k;

// 	j = 8;
// 	i = 0;
// 	main_cub->c_map->rows = 0;
// 	main_cub->c_map->column = 0;
// 	while (main_cub->map_file[j])
// 	{
// 		if (ft_strlen_no_nl(main_cub->map_file[j]) > main_cub->c_map->column)
// 			main_cub->c_map->column = ft_strlen_no_nl(main_cub->map_file[j]);
// 		j++;
// 		main_cub->c_map->rows++;
// 	}
// 	main_cub->c_map->ar_map = ft_calloc(main_cub->c_map->rows + 1, sizeof(char *));
// 	j = 8;
// 	while (i < main_cub->c_map->rows)
// 	{ 
// 		k = 0;
// 		// main_cub->c_map->ar_map[i] = ft_strdup(main_cub->map_file[j]);
// 		tmp = ft_calloc((ft_strlen(main_cub->map_file[j]) - 1), sizeof(char));
// 		while (k < (ft_strlen(main_cub->map_file[j]) - 1))
// 		{
// 			tmp[k] = main_cub->map_file[j][k];
// 			k++;
// 		}
// 		tmp[k] = '\0';
// 		main_cub->c_map->ar_map[i] = ft_strdup(tmp);
// 		free(tmp);
// 		i++;
// 		j++;
// 	}
// 	main_cub->c_map->ar_map[i] = NULL;
// }

void	rect_map(t_cub3d *main_cub)
{
	char	**new_map;
	int		i;
	int		j;
	int		k;
	

	i = 0;
	new_map = ft_calloc(main_cub->c_map->rows + 1, sizeof(char *));

	// while (main_cub->c_map->ar_map[i])
	// {
	// 	if (ft_strlen_no_nl(main_cub->c_map->ar_map[i]) != main_cub->c_map->column)
	// 	{
	// 		j = 0;
	// 		k = 0;
	// 		// printf("%d column\n", main_cub->c_map->column);
	// 		new_map[i] = ft_calloc((main_cub->c_map->column + 1), sizeof(char));
	// 		while (j <= main_cub->c_map->column)
	// 		{
	// 			if (main_cub->c_map->ar_map[i][k] == '\n' && new_map[i])
	// 			{
	// 				new_map[i][j] = '1';
	// 			}
	// 			else if (main_cub->c_map->ar_map[i][k] == ' ')
	// 			{
	// 				new_map[i][j] = '1';
	// 				k++;
	// 			}
	// 			else
	// 			{
	// 				new_map[i][j] = main_cub->c_map->ar_map[i][k];
	// 				k++;
	// 			}
	// 			j++;
	// 		}
	// 		// printf("%d j\n", j);
	// 		new_map[i][j] = '\0';
	// 	}
	// 	else
	// 		new_map[i] = ft_strdup(main_cub->c_map->ar_map[i]);
	// 	// printf("%d\n", ft_strlen(new_map[i]));
	// 	printf("%s\n", new_map[i]);
	// 	i++;
	// }
	// new_map[i] = NULL;
	// print_arg(new_map);
	while (i < main_cub->c_map->rows)
	{
		j = 0;
		k = 0;
		// printf("i%i\n", i);
		new_map[i] = ft_calloc((main_cub->c_map->column + 1), sizeof(char));
		while (j < main_cub->c_map->column)
		{
			// printf("j%i\n", j);
			if (main_cub->c_map->ar_map[i][j]
				&& (ft_isdigit(main_cub->c_map->ar_map[i][j])
				|| ft_strchr("NSEW", main_cub->c_map->ar_map[i][j]))
				&& (j <= ft_strlen(main_cub->c_map->ar_map[i])))
				new_map[i][j] = main_cub->c_map->ar_map[i][j];
			else
			{
				new_map[i][j] = '1';
			}
			j++;
		}
			new_map[i][main_cub->c_map->column] = '\0';
		printf("%s\n", new_map[i]);
		i++;
	}
	main_cub->c_map->ar_map = new_map;
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
	create_images(main_cub);
	create_colors(main_cub);
	create_map(main_cub);
	rect_map(main_cub);
	find_player(main_cub);
	close(fd);
	// if (checker_2(main_cub, argv))
	// 	return (0);
	return (1);
}