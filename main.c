/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inovomli <inovomli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 13:45:04 by inovomli          #+#    #+#             */
/*   Updated: 2023/04/28 18:01:41 by inovomli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//	gcc main.c MLX42/build/libmlx42.a -Iinclude -ldl -lglfw -L 
// "$(brew --prefix glfw)/lib/" -pthread -lm

// gcc main.c MLX42/build/libmlx42.a -Iinclude -ldl -lglfw -L
// "$(brew --prefix glfw)/lib/" -pthread -lm -L../LeakSanitizer -llsan -lc++  
// -Wno-gnu-include-next -I ../LeakSanitizer/include

#include "cub3d.h"

void	print_arg(char **args)
{
	int	i;

	i = 0;
	if (args)
	{
		while (args[i])
		{
			printf("%s", args[i]);
			printf("\n");
			i++;
		}
	}
	else
		printf("args: (null)\n");
}

int32_t	ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

int	gtcl(mlx_texture_t *texture, int x_coord, int y_coord)
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

void	add_norm(mlx_texture_t *txtr, t_norm *t, t_cub3d *s_cub, t_raycst *rt)
{
	if (txtr == s_cub->c_map->so)
		t->txt_x = txtr->width - t->txt_x;
	if (txtr == s_cub->c_map->we)
		t->txt_x1 = txtr->width - t->txt_x1;
	t->h = min(rt->cl_h, t->cmh);
	t->n = min(max((int)((t->cmh - t->h) / 2 + t->y), 0), t->cmh);
}

void	draw_txtr_line(mlx_texture_t *txtr, t_cub3d *s_cub, t_raycst *rt, int i)
{
	t_norm	t;

	t.cmh = s_cub->mlx->height;
	t.y = 0;
	if (txtr == NULL)
		return ;
	while (t.y < (int)rt->cl_h && t.y < t.cmh)
	{
		t.txt_x = txtr->width * ((float)rt->x1 - (int)rt->x1);
		if ((int)rt->cl_h > t.cmh)
			t.txt_y1 = ((rt->cl_h - t.cmh) / 2 + t.y)
				* txtr->height / (rt->cl_h + 0.00001f);
		else
			t.txt_y1 = t.y * txtr->height / (rt->cl_h + 0.00001f);
		t.txt_x1 = txtr->width * ((float)rt->y1 - (int)rt->y1);
		add_norm(txtr, &t, s_cub, rt);
		if ((txtr == s_cub->c_map->no) || (txtr == s_cub->c_map->so))
			mlx_put_pixel(s_cub->image, i, t.n, gtcl(txtr, t.txt_x, t.txt_y1));
		if ((txtr == s_cub->c_map->we) || (txtr == s_cub->c_map->ea))
			mlx_put_pixel(s_cub->image, i, t.n, gtcl(txtr, t.txt_x1, t.txt_y1));
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

	wrk_txt = NULL;
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
		while (rt.dist < 30)
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

void	checkleaks(void)
{
	system("leaks cub3d");
}

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

int	check_ext(char *path)
{
	int	i;

	i = 0;
	if (!path)
		return (0);
	while (path[i])
		i++;
	if (i < 5 || ft_strncmp(&path[i - 4], ".cub", 4) != 0)
		return (0);
	else
		return (1);
}

void	free_everything(t_cub3d *m_cub)
{
	mlx_delete_texture(m_cub->c_map->ea);
	mlx_delete_texture(m_cub->c_map->no);
	mlx_delete_texture(m_cub->c_map->so);
	mlx_delete_texture(m_cub->c_map->we);
	free_map(m_cub);
	free(m_cub->pl_pos);
}

void	init_cub(t_cub3d *cub)
{
	cub->c_map->ea = mlx_load_png(cub->c_map->east_path);
	cub->c_map->no = mlx_load_png(cub->c_map->north_path);
	cub->c_map->so = mlx_load_png(cub->c_map->south_path);
	cub->c_map->we = mlx_load_png(cub->c_map->west_path);
	cub->c_map->f_color = ft_pixel(cub->c_map->f_color_r,
			cub->c_map->f_color_g, cub->c_map->f_color_b, 255);
	cub->c_map->c_color = ft_pixel(cub->c_map->c_color_r,
			cub->c_map->c_color_g, cub->c_map->c_color_b, 255);
	cub->view_angle = M_PI / 3;
	cub->minone = NULL;
	cub->mintwo = NULL;
	cub->minthree = NULL;
	cub->image = mlx_new_image(cub->mlx, cub->mlx->width, cub->mlx->height);
}

int32_t	main(int32_t argc, char *argv[])
{
	t_cub3d		m_cub;

	atexit(checkleaks);
	m_cub.mlx = mlx_init(WIDTH, HEIGHT, "MLX42", false);
	if ((argc == 2) && check_ext(argv[1]))
	{
		if (!read_file(&m_cub, argv))
			return (1);
	}
	else
	{
		printf("Error\n");
		return (1);
	}
	init_cub(&m_cub);
	redraw_all(&m_cub);
	mlx_loop_hook(m_cub.mlx, ft_hook, &m_cub);
	mlx_loop(m_cub.mlx);
	mlx_terminate(m_cub.mlx);
	free_everything(&m_cub);
	return (0);
}
