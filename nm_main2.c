/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm_main2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inovomli <inovomli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 11:51:59 by inovomli          #+#    #+#             */
/*   Updated: 2023/05/01 11:54:24 by inovomli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	add_norm(mlx_texture_t *txtr, t_norm *t, t_cub3d *s_cub, t_raycst *rt)
{
	if (txtr == s_cub->c_map->so)
		t->txt_x = txtr->width - t->txt_x;
	if (txtr == s_cub->c_map->we)
		t->txt_x1 = txtr->width - t->txt_x1;
	t->h = min(rt->cl_h, t->cmh);
	t->n = min(max((int)((t->cmh - t->h) / 2 + t->y), 0), t->cmh);
}

void	draw_txtr_lin(mlx_texture_t *txtr, t_cub3d *s_cub, t_raycst *rt, int i)
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
			draw_txtr_lin(wrk_txt, s_cub, rt, rt->i - 1);
			draw_txtr_lin(wrk_txt, s_cub, rt, rt->i - 2);
			s_cub->minone = wrk_txt;
			s_cub->mintwo = wrk_txt;
		}
		s_cub->minthree = s_cub->mintwo;
		s_cub->mintwo = s_cub->minone;
		s_cub->minone = wrk_txt;
	}
}
