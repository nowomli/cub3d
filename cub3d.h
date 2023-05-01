/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccompote <ccompote@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 15:54:34 by ccompote          #+#    #+#             */
/*   Updated: 2023/05/01 11:37:22 by ccompote         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 100
# endif
# define WIDTH 512
# define HEIGHT 512
# define STEP 0.09f
# define TURN_ANGLE 0.05f
# define RTSTEP 0.001f
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <math.h>
# include <stdbool.h>
# include "MLX42/include/MLX42/MLX42.h"
# include "libft/libft.h"

typedef enum e_mv_dir{not_set = 0, up, dw, lf, rt, rot_lf, rot_rt}	t_mv_dir;

typedef struct s_player
{
	float	x;
	float	y;
	float	angle;
}	t_player;

typedef struct s_rcast
{
	float	x1;
	float	y1;
	float	ang;
	float	dist;
	size_t	cl_h;
	int		i;
}	t_raycst;

typedef struct s_norm
{
	int		txt_x;
	int		txt_y1;
	int		txt_x1;
	int32_t	y;
	int		h;
	int		n;
	int32_t	cmh;
}	t_norm;

typedef struct s_point
{
	int	x;
	int	y;
}	t_point;

typedef struct s_map
{
	int				rows;
	int				column;
	char			**ar_map;
	int				f_color_r;
	int				f_color_g;
	int				f_color_b;
	int				c_color_r;
	int				c_color_g;
	int				c_color_b;
	int				f_color;
	int				c_color;
	char			*north_path;
	char			*south_path;
	char			*west_path;
	char			*east_path;
	mlx_texture_t	*no;
	mlx_texture_t	*so;
	mlx_texture_t	*we;
	mlx_texture_t	*ea;
	char			**temp_map;
}	t_map;

typedef struct s_cub3D
{
	mlx_t			*mlx;
	t_map			*c_map;
	t_player		*pl_pos;
	mlx_image_t		*cur_img;
	mlx_image_t		*image;
	char			**map_file;
	int				file_rows;
	float			view_angle;
	int				fd;
	mlx_texture_t	*minone;
	mlx_texture_t	*mintwo;
	mlx_texture_t	*minthree;
	int				map_found;
	int				found_items;
	int				i_file;
}	t_cub3d;

int		read_file(t_cub3d *zop, char **argv);
char	*gn_strchr(char *s, int c);
char	*gn_strjoin(char *s1, char *s2);
char	*get_next_line(int fd);
int		ft_strlen_no_nl(char *s);
int		check_arg(int argc, char **argv);
int		checker_2(t_cub3d *zop, char **argv);
int		map_lines(int fd, t_cub3d *zop);
int		find_player(t_cub3d *main_cub);
void	tdimarr_clear(char	**arrclear);
void	print_arg(char **args);
int		file_lines(int fd, t_cub3d *main_cub);
int		create_file_arr(int fd, t_cub3d *main_cub);
void	rect_map(t_map *c_map);
int		parse_file(t_cub3d *main_cub);
int		create_colors(t_map *c_map, char *line, char c);
int		check_is_map(t_cub3d *main_cub, int i, int y);
int		map_holes(t_map *map);
int		find_pl(t_map *map, int *x, int *y);
void	free_arr(char **arr);
void	free_map(t_cub3d *m_cub);
int		create_images(t_map *c_map, char *line);
int		check_png(char *path);

#endif