/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dir_scan.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 18:21:54 by mchardin          #+#    #+#             */
/*   Updated: 2019/11/23 18:24:25 by mchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>

void	img_to_int(t_mlx_img tmp, t_texture *txtr)
{
	int		i;
	int		j;

	i = 0;
	while (i < txtr->h * txtr->w)
	{
		j = 0;
		while (j < tmp.bpp)
		{
			txtr->txtr[i] += (tmp.bpp - j) * (int)tmp.img[i * j + j];
			j++;
		}
		i++;
	}
}

void	texture_put(t_params *params, int height, double pct, int i)
{
	int			j;

	j = 0;	
	while (j < height)
	{
		mlx_pixel_put(params->ptr, params->wdw, i, height, params->scan.face->txtr[(int)(j / height) * (int)(pct * params->scan.face->w) + (int)(j / height)]);
		j++;
	}
}

void	line_put(t_params *params, int color, double inc, int i)
{
	double	dist;
	double	proj;
	int		height;
	int	j;
	(void)color;
	dist = cos(inc) * params->max.y * sqrt((params->scan.wall.x - params->player.pos.x) * (params->scan.wall.x - params->player.pos.x) + (params->scan.wall.y - params->player.pos.y) * (params->scan.wall.y - params->player.pos.y));
	//dist = dist * dist_front;
	j = -1;
//	dist = (fabs(params->scan.wall.x - params->player.pos.x) / cos(M_PI / 2 - angle) * cos(angle));
	proj = (params->max.y / 2) / tan(M_PI / 6); //constant -> ajouter a la struct
	height = params->max.x / dist * proj;
	while (++j < (params->max.y - height) / 2)
		mlx_pixel_put(params->ptr, params->wdw, i, j, params->graph.C);
	if (params->scan.face == &params->graph.SO || params->scan.face == &params->graph.NO)
		texture_put(params, height, fabs(floor(params->scan.wall.x) - params->scan.wall.x), i);
	else
		texture_put(params, height, fabs(floor(params->scan.wall.y) - params->scan.wall.y), i);
	j = (params->max.y - (params->max.y - height) / 2) - 1;
	while (++j < params->max.y)
		mlx_pixel_put(params->ptr, params->wdw, i, j, params->graph.F);
}
