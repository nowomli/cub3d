/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm_main3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inovomli <inovomli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 12:06:19 by inovomli          #+#    #+#             */
/*   Updated: 2023/05/01 12:08:58 by inovomli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
	draw_txtr_lin(wrk_txt, s_cub, rt, rt->i);
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

void	checkleaks(void)
{
	system("leaks cub3d");
}
