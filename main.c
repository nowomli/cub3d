/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inovomli <inovomli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 13:45:04 by inovomli          #+#    #+#             */
/*   Updated: 2023/04/14 17:30:49 by inovomli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//	gcc main.c MLX42/build/libmlx42.a -Iinclude -ldl -lglfw -L 
// "$(brew --prefix glfw)/lib/" -pthread -lm

// gcc main.c MLX42/build/libmlx42.a -Iinclude -ldl -lglfw -L
// "$(brew --prefix glfw)/lib/" -pthread -lm -L../LeakSanitizer -llsan -lc++  
// -Wno-gnu-include-next -I ../LeakSanitizer/include

#include <unistd.h>
#include <stdio.h>

#include <fcntl.h>
#include <math.h>
#include <string.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "MLX42/include/MLX42/MLX42.h"

#define WIDTH 512
#define HEIGHT 512
#define STEP 0.09f
#define TURN_ANGLE 0.05f
#define RTSTEP 0.001f

typedef enum e_mv_dir{not_set = 0, up, dw, lf, rt, rot_lf, rot_rt}	t_mv_dir;

typedef struct s_player
{
	float	x;
	float	y;
	float	angle;

}	t_player;

typedef struct s_map
{
	int				rows;
	int				column;
	uint32_t		f_color;
	uint32_t		c_color;
	mlx_texture_t	*no;
	mlx_texture_t	*so;
	mlx_texture_t	*we;
	mlx_texture_t	*ea;
	char			**ar_map;
}	t_map;

typedef struct s_cub3D
{
	mlx_texture_t	*minone;
	mlx_texture_t	*mintwo;
	mlx_texture_t	*minthree;
	float			view_angle;
	mlx_t			*mlx;
	t_map			*c_map;
	t_player		*pl_pos;
	mlx_image_t		*cur_img;
	mlx_image_t		*image;
	bool			resize;
}	t_cub3d;

// -----------------------------------------------------------------------------

int32_t	ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

int	get_color(mlx_texture_t *texture, int x_coord, int y_coord)
{
	int			byte;
	uint32_t	color;

	byte = (y_coord * texture->width * 4) + (x_coord * 4);
	color = ft_pixel(texture->pixels[byte], texture->pixels[byte + 1],
			texture->pixels[byte + 2], texture->pixels[byte + 3]);
	return (color);
}

int	min(int a, int b)
{
	if (a <= b)
		return (a);
	return (b);
}

int	max(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}

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

void	draw_txtr_line(mlx_texture_t *txtr, t_cub3d *s_cub, t_raycst *rt, int i)
{
	t_norm	t;

	t.cmh = s_cub->mlx->height;
	t.y = 0;
	while (t.y < rt->cl_h && t.y < t.cmh)
	{
		t.txt_x = txtr->width * ((float)rt->x1 - (int)rt->x1);
		if (rt->cl_h > t.cmh)
			t.txt_y1 = ((rt->cl_h - t.cmh) / 2 + t.y)
				* txtr->height / (rt->cl_h + 0.00001f);
		else
			t.txt_y1 = t.y * txtr->height / (rt->cl_h + 0.00001f);
		t.txt_x1 = txtr->width * ((float)rt->y1 - (int)rt->y1);
		t.h = min(rt->cl_h, t.cmh);
		t.n = min(max((int)((t.cmh - t.h) / 2 + t.y), 0), t.cmh);
		if ((txtr == s_cub->c_map->no) || (txtr == s_cub->c_map->so))
			mlx_put_pixel(s_cub->image, i, t.n,
				get_color(txtr, t.txt_x, t.txt_y1));
		if ((txtr == s_cub->c_map->we) || (txtr == s_cub->c_map->ea))
			mlx_put_pixel(s_cub->image, i, t.n,
				get_color(txtr, t.txt_x1, t.txt_y1));
		++t.y;
	}
}

void	draw_flcl(t_cub3d *s_cub)
{
	int	i;
	int	y;

	i = 0;
	mlx_delete_image(s_cub->mlx, s_cub->image);
	s_cub->image = mlx_new_image(s_cub->mlx,
			s_cub->mlx->width, s_cub->mlx->height);
	while (i < s_cub->mlx->width)
	{
		y = 0;
		while (y < s_cub->mlx->height)
		{
			if (y < s_cub->mlx->height / 2)
				mlx_put_pixel(s_cub->image, i, y, s_cub->c_map->f_color);
			else
				mlx_put_pixel(s_cub->image, i, y, s_cub->c_map->c_color);
			++y;
		}
		++i;
	}
}

mlx_texture_t	*determ_txt(t_cub3d *s_cub, t_raycst *raycst)
{
	mlx_texture_t	*wrk_txt;
	float			x1;
	float			y1;

	raycst->dist -= RTSTEP;
	x1 = s_cub->pl_pos->x + raycst->dist * cosf(raycst->ang);
	y1 = s_cub->pl_pos->y + raycst->dist * sinf(raycst->ang);
	if (fabs(x1 -(int)x1) < fabs(1 - x1 + (int)x1) && fabs(x1 -(int)x1)
		< fabs(1 - y1 + (int)y1) && fabs(x1 -(int)x1) < fabs(y1 - (int)y1))
		wrk_txt = s_cub->c_map->we;
	else if (fabs(1 - x1 + (int)x1) < fabs(x1 -(int)x1)
		&& fabs(1 - x1 + (int)x1)
		< fabs(1 - y1 + (int)y1) && fabs(1 - x1 + (int)x1) < fabs(y1 - (int)y1))
		wrk_txt = s_cub->c_map->ea;
	else if (fabs(y1 - (int)y1) < fabs(1 - x1 + (int)x1) && fabs(y1 - (int)y1)
		< fabs(x1 - (int)x1) && fabs(y1 - (int)y1) < fabs(1 - y1 + (int)y1))
		wrk_txt = s_cub->c_map->no;
	else if (fabs(1 - y1 + (int)y1) < fabs(1 - x1 + (int)x1)
		&& fabs(1 - y1 + (int)y1) < fabs(y1 - (int)y1)
		&& fabs(1 - y1 + (int)y1) < fabs(x1 -(int)x1))
		wrk_txt = s_cub->c_map->so;
	return (wrk_txt);
}

void	fix_artifact(t_cub3d *s_cub, mlx_texture_t *wrk_txt, t_raycst *rt)
{
	if (s_cub->minthree == NULL)
		s_cub->minthree = wrk_txt;
	else if (s_cub->mintwo == NULL)
		s_cub->mintwo = wrk_txt;
	else if (s_cub->minone == NULL)
		s_cub->minone = wrk_txt;
	if (s_cub->mintwo && s_cub->minthree && s_cub->minone)
	{
		if ((s_cub->minthree != s_cub->minone)
			&& (s_cub->minthree == wrk_txt) && (rt->i > 2))
		{
			draw_txtr_line(wrk_txt, s_cub, rt, rt->i - 1);
			draw_txtr_line(wrk_txt, s_cub, rt, rt->i - 2);
			s_cub->minone = wrk_txt;
			s_cub->mintwo = wrk_txt;
		}
		s_cub->minthree = s_cub->mintwo;
		s_cub->mintwo = s_cub->minone;
		s_cub->minone = wrk_txt;
	}
}

void	small_preset(t_raycst *rt, t_cub3d *s_cub)
{
	rt->ang = s_cub->pl_pos->angle - s_cub->view_angle / 2
		+ (s_cub->view_angle * rt->i) / s_cub->mlx->width;
	rt->dist = 0;
}

void	draw_line(t_raycst *rt, t_cub3d *s_cub)
{
	mlx_texture_t	*wrk_txt;

	rt->cl_h = s_cub->mlx->height
		/ (rt->dist * cosf(rt->ang - s_cub->pl_pos->angle));
	wrk_txt = determ_txt(s_cub, rt);
	fix_artifact(s_cub, wrk_txt, rt);
	draw_txtr_line(wrk_txt, s_cub, rt, rt->i);
}

void	redraw_all(t_cub3d *s_cub)
{
	t_raycst	rt;

	draw_flcl(s_cub);
	rt.i = 0;
	while (rt.i < s_cub->mlx->width)
	{
		small_preset(&rt, s_cub);
		while (rt.dist < 20)
		{
			rt.x1 = s_cub->pl_pos->x + rt.dist * cosf(rt.ang);
			rt.y1 = s_cub->pl_pos->y + rt.dist * sinf(rt.ang);
			if ((rt.y1 >= 0) && (rt.y1 < s_cub->c_map->rows) && (rt.x1 >= 0)
				&& ((int)rt.x1 < s_cub->c_map->column)
				&& (s_cub->c_map->ar_map[(int)rt.y1][(int)rt.x1] != '0'))
			{
				draw_line(&rt, s_cub);
				break ;
			}
			rt.dist += RTSTEP;
		}
		++rt.i;
	}
	mlx_image_to_window(s_cub->mlx, s_cub->image, 0, 0);
}

int	check_wall(t_cub3d *s_cub, float dispX, float dispY)
{
	int	new_x;
	int	new_y;

	new_x = (int)(s_cub->pl_pos->x + dispX * 5);
	new_y = (int)(s_cub->pl_pos->y + dispY * 5);
	if (s_cub->c_map->ar_map[new_y][new_x] == '0')
		return (1);
	else
		return (0);
}

void	mv_pl_rt(t_cub3d *s_cub, float dx, float dy)
{
	if (check_wall(s_cub, -dy, 0))
		s_cub->pl_pos->x -= dy;
	if (check_wall(s_cub, 0, +dx))
		s_cub->pl_pos->y += dx;
}

void	mv_pl_lf(t_cub3d *s_cub, float dx, float dy)
{
	if (check_wall(s_cub, +dy, 0))
		s_cub->pl_pos->x += dy;
	if (check_wall(s_cub, 0, -dx))
		s_cub->pl_pos->y -= dx;
}

void	mv_pl_up(t_cub3d *s_cub, float dx, float dy)
{
	if (check_wall(s_cub, dx, 0))
		s_cub->pl_pos->x += dx;
	if (check_wall(s_cub, 0, dy))
		s_cub->pl_pos->y += dy;
}

void	move_pl(t_cub3d *s_cub, t_mv_dir dir)
{
	float	dx;
	float	dy;

	dx = STEP * cosf(s_cub->pl_pos->angle);
	dy = STEP * sinf(s_cub->pl_pos->angle);
	if (dir == rt)
		mv_pl_rt(s_cub, dx, dy);
	else if (dir == lf)
		mv_pl_lf(s_cub, dx, dy);
	else if (dir == up)
		mv_pl_up(s_cub, dx, dy);
	else if (dir == dw)
	{
		if (check_wall(s_cub, -dx, 0))
			s_cub->pl_pos->x -= dx;
		if (check_wall(s_cub, 0, -dy))
			s_cub->pl_pos->y -= dy;
	}
	else if (dir == rot_lf)
		s_cub->pl_pos->angle -= TURN_ANGLE;
	else if (dir == rot_rt)
		s_cub->pl_pos->angle += TURN_ANGLE;
	redraw_all(s_cub);
}

// void move_pl(t_cub3d *s_cub, t_mv_dir dir)
// {
// 	float dx = STEP * cosf(s_cub->pl_pos->angle);
// 	float dy = STEP * sinf(s_cub->pl_pos->angle);
// 	if (dir == rt) 
// 	{
// 		if (check_wall(s_cub, -dy, 0) && check_wall(s_cub, 0, +dx))
// 		{
// 			s_cub->pl_pos->x -= dy;
// 			s_cub->pl_pos->y += dx;	
// 		}	
// 	}
// 	else if (dir == lf)	
// 	{
// 		if (check_wall(s_cub, +dy, 0) && check_wall(s_cub, 0, -dx)) 
// 		{
// 			s_cub->pl_pos->x += dy;
// 			s_cub->pl_pos->y -= dx;		
// 		}
// 	}
// 	else if (dir == up)
// 	{
// 		if (check_wall(s_cub, dx, 0) && check_wall(s_cub, 0, dy*3))	
// 		{	
// 			s_cub->pl_pos->x += dx;
// 			s_cub->pl_pos->y += dy;			
// 		}
// 	}
// 	else if (dir == dw)
// 	{
// 		if (check_wall(s_cub, -dx, 0) && check_wall(s_cub, 0, -dy))	
// 		{
// 			s_cub->pl_pos->x -= dx;		
// 			s_cub->pl_pos->y -= dy;		
// 		}
// 	}
// 	else if (dir == rot_lf)
// 		s_cub->pl_pos->angle -= TURN_ANGLE;
// 	else if (dir == rot_rt)
// 		s_cub->pl_pos->angle += TURN_ANGLE;
// 	redraw_all(s_cub);
// }

	// mlx_key_hook(m_cub.mlx, ft_key_hook, &m_cub);
void	ft_key_hook(mlx_key_data_t keydata, void *param)
{
	t_cub3d	*s_cub;

	s_cub = (t_cub3d *)param;
	if (keydata.key == MLX_KEY_ESCAPE)
		mlx_close_window(s_cub->mlx);
	if (keydata.key == MLX_KEY_W && (keydata.action == MLX_PRESS
			|| keydata.action == MLX_REPEAT))
		move_pl(s_cub, up);
	else if (keydata.key == MLX_KEY_S && (keydata.action == MLX_PRESS
			|| keydata.action == MLX_REPEAT))
		move_pl(s_cub, dw);
	else if (keydata.key == MLX_KEY_A && (keydata.action == MLX_PRESS
			|| keydata.action == MLX_REPEAT))
		move_pl(s_cub, lf);
	else if (keydata.key == MLX_KEY_D && (keydata.action == MLX_PRESS
			|| keydata.action == MLX_REPEAT))
		move_pl(s_cub, rt);
	else if (keydata.key == MLX_KEY_LEFT && (keydata.action == MLX_PRESS
			|| keydata.action == MLX_REPEAT))
		move_pl(s_cub, rot_lf);
	else if (keydata.key == MLX_KEY_RIGHT && (keydata.action == MLX_PRESS
			|| keydata.action == MLX_REPEAT))
		move_pl(s_cub, rot_rt);
}

void	ft_hook(void *param)
{
	t_cub3d	*s_cub;

	s_cub = (t_cub3d *)param;
	if (mlx_is_key_down(s_cub->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(s_cub->mlx);
	else if (mlx_is_key_down(s_cub->mlx, MLX_KEY_D))
		move_pl(s_cub, rt);
	else if (mlx_is_key_down(s_cub->mlx, MLX_KEY_A))
		move_pl(s_cub, lf);
	else if (mlx_is_key_down(s_cub->mlx, MLX_KEY_W))
		move_pl(s_cub, up);
	else if (mlx_is_key_down(s_cub->mlx, MLX_KEY_S))
		move_pl(s_cub, dw);
	else if (mlx_is_key_down(s_cub->mlx, MLX_KEY_RIGHT))
		move_pl(s_cub, rot_rt);
	else if (mlx_is_key_down(s_cub->mlx, MLX_KEY_LEFT))
		move_pl(s_cub, rot_lf);
}

// -----------------------------------------------------------------------------

// char	**feed_map(char *path)
// {
// 	char	**hope;
// 	int		rowsize = 13;
// 	int i = 0;

// 	char *filename = path;
// 	FILE *fp = fopen(filename, "r");

// 	hope = malloc(sizeof(char *) * (rowsize + 1));
// 	if (fp == NULL)
// 	{
// 		printf("Error: could not open file %s", filename);
// 		return 0;
// 	}
// 	const unsigned MAX_LENGTH = 256;
// 	char buffer[MAX_LENGTH];
// 	while (fgets(buffer, MAX_LENGTH, fp))
// 	{
// 		hope[i] = malloc(sizeof(char) * 9);
// 		strcpy(hope[i++],buffer);
// 		// printf("%s", buffer);
// 	}
// 	hope[i] = 0;
// 	fclose(fp);
// 	return (hope);
// }

// void	checkleaks(void)
// {
// 	system("leaks a.out");
// }
	// atexit(checkleaks);

void	tdimarr_clear(char	**arrclear)
{
	int	i;

	i = 0;
	while (arrclear[i])
	{
		free(arrclear[i]);
		i++;
	}
	free(arrclear);
}

int32_t	main(int32_t argc, char *argv[])
{
	t_cub3d		m_cub;
	t_map		loaded_map_st;
	t_player	player;
	char		**map;

	if (argc == 2)
		map = feed_map(argv[1]);
	else
		return (1);
	m_cub.mlx = mlx_init(WIDTH, HEIGHT, "MLX42", false);

	loaded_map_st.ar_map = map;
	loaded_map_st.ea = mlx_load_png("imgs/cls.png");
	loaded_map_st.no = mlx_load_png("imgs/bls.png");
	loaded_map_st.so = mlx_load_png("imgs/grs.png");
	loaded_map_st.we = mlx_load_png("imgs/mss.png");
	loaded_map_st.f_color = ft_pixel(255, 0, 0, 255);
	loaded_map_st.c_color = ft_pixel(116, 96, 31, 255);
	loaded_map_st.column = 7;
	loaded_map_st.rows = 13;

	player.x = 2.5f;
	player.y = 5.4f;
	player.angle = 1.5 * M_PI;

	m_cub.pl_pos = &player;
	m_cub.view_angle = M_PI / 3;
	m_cub.c_map = &loaded_map_st;
	m_cub.minone = NULL;
	m_cub.mintwo = NULL;
	m_cub.minthree = NULL;
	m_cub.image = mlx_new_image(m_cub.mlx, m_cub.mlx->width, m_cub.mlx->height);

	redraw_all(&m_cub);
	mlx_loop_hook(m_cub.mlx, ft_hook, &m_cub);
	mlx_loop(m_cub.mlx);
	mlx_terminate(m_cub.mlx);

	mlx_delete_texture(loaded_map_st.ea);
	mlx_delete_texture(loaded_map_st.no);
	mlx_delete_texture(loaded_map_st.so);
	mlx_delete_texture(loaded_map_st.we);
	tdimarr_clear(loaded_map_st.ar_map);
	return (0);
}
