/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inovomli <inovomli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 13:45:04 by inovomli          #+#    #+#             */
/*   Updated: 2023/05/01 12:11:49 by inovomli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//	gcc main.c MLX42/build/libmlx42.a -Iinclude -ldl -lglfw -L 
// "$(brew --prefix glfw)/lib/" -pthread -lm

// gcc main.c MLX42/build/libmlx42.a -Iinclude -ldl -lglfw -L
// "$(brew --prefix glfw)/lib/" -pthread -lm -L../LeakSanitizer -llsan -lc++  
// -Wno-gnu-include-next -I ../LeakSanitizer/include

#include "cub3d.h"

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
