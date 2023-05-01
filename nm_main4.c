/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm_main4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inovomli <inovomli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 12:09:29 by inovomli          #+#    #+#             */
/*   Updated: 2023/05/01 12:10:14 by inovomli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
