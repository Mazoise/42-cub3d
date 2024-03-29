/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 12:04:39 by mchardin          #+#    #+#             */
/*   Updated: 2019/12/12 11:09:18 by mchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		add_pix(t_mlx_img *img, t_mlx_img txtr, int dst, int src)
{
	int		i;
	int		opp_img;
	int		opp_txtr;
	double	transp;

	i = 0;
	opp_txtr = txtr.bpp >> 3;
	opp_img = img->bpp >> 3;
	transp = (unsigned char)txtr.img[src * opp_txtr + 3] / (double)255;
	while (i < opp_txtr - 1 && i < opp_img - 1)
	{
		img->img[dst + i] = (unsigned char)img->img[dst + i] * transp
			+ (unsigned char)txtr.img[src * opp_txtr + i] * (1 - transp);
		i++;
	}
}

void		close_sprite(t_scan *scan, int *nb)
{
	if (rsqrt(pow(scan->wall.x - scan->vrt.x, 2)
		+ pow(scan->wall.y - scan->vrt.y, 2))
		>= rsqrt(pow(scan->wall.x - scan->hrz.x, 2)
		+ pow(scan->wall.y - scan->hrz.y, 2)))
	{
		scan->wall.x = scan->hrz.x;
		scan->wall.y = scan->hrz.y;
		scan->hrz.x -= scan->add_horz.x;
		scan->hrz.y -= scan->add_horz.y;
	}
	else
	{
		scan->wall.x = scan->vrt.x;
		scan->wall.y = scan->vrt.y;
		scan->vrt.x -= scan->add_vert.x;
		scan->vrt.y -= scan->add_vert.y;
	}
	(*nb)--;
}

void		print_sprite(t_params *params, double angle, int i)
{
	t_pos		cam;
	double		dist;
	double		dir;
	int			height;
	t_idx		idx;

	idx.i = i;
	cam.x = floor(params->scan.wall.x) + 0.5;
	cam.y = floor(params->scan.wall.y) + 0.5;
	params->scan.face = &params->graph.s;
	dist = rsqrt(pow(cam.x - params->player.pos.x, 2)
		+ pow(cam.y - params->player.pos.y, 2));
	height = params->max.i / (dist * params->max.j) * params->calc.proj;
	if (params->max.j - height > 0)
		idx.j = (params->max.j - height) / 2;
	else
		idx.j = 0;
	dir = tan(asin((((params->player.pos.x - cam.x) * sin(angle))
		+ (cam.y - params->player.pos.y) * cos(angle)) / dist)) * dist + 0.5;
	if (dir >= 0 && dir <= 1)
		sprite_put(params, height, dir, &idx);
}

void		sprite(t_params *params, double angle, int i)
{
	t_scan		*scan;

	scan = &params->scan;
	scan->vrt.x -= scan->add_vert.x;
	scan->vrt.y -= scan->add_vert.y;
	scan->hrz.x -= scan->add_horz.x;
	scan->hrz.y -= scan->add_horz.y;
	while (scan->nb > 0)
	{
		close_sprite(&params->scan, &scan->nb);
		if (is_grid_pos(scan->wall.x, scan->wall.y, params->grid, '2'))
			print_sprite(params, angle, i);
	}
}
