/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dir_scan.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 18:21:54 by mchardin          #+#    #+#             */
/*   Updated: 2019/11/23 22:00:11 by mchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>

void	img_to_int(t_mlx_img tmp, t_texture *txtr)
{
	int		i;
	int		j;

	tmp.bpp /= 8;
	i = 0;
//	ft_printf("BPP :%d\n", tmp.bpp);
	while (i < txtr->h * txtr->w)
	{
		j = 0;
		while (j < tmp.bpp)
		{
			txtr->txtr[i] += pow(256, j) * tmp.img[i * tmp.bpp + j];
			j++;
		}
		// ft_printf("%X,", txtr->txtr[i]);
		i++;
	}
}

void	texture_put(t_params *params, int height, double pct, int i, int j)
{
	int		k;
	double tmp;
	k = 0;
	while (k < height)
	{
		tmp = floor((double)k * (double)params->scan.face->h / * (double)params->scan.face->w / (double)height) + floor(pct * (double)params->scan.face->w);
		mlx_pixel_put(params->ptr, params->wdw, i, j, params->scan.face->txtr[(int)floor(tmp)]);
		// ft_printf("tmp : %d", (int)tmp);
		j++;
		k++;
	}
}

void	line_put(t_params *params, double inc, int i)
{
	double	dist;
	double	proj;
	int		height;
	int	j;

	dist = cos(inc) * params->max.y * sqrt((params->scan.wall.x - params->player.pos.x) * (params->scan.wall.x - params->player.pos.x) + (params->scan.wall.y - params->player.pos.y) * (params->scan.wall.y - params->player.pos.y));
	//dist = dist * dist_front;
	j = -1;
//	dist = (fabs(params->scan.wall.x - params->player.pos.x) / cos(M_PI / 2 - angle) * cos(angle));
	proj = (params->max.y / 2) / tan(M_PI / 6); //constant -> ajouter a la struct
	height = params->max.x / dist * proj;
	while (++j < (params->max.y - height) / 2)
		mlx_pixel_put(params->ptr, params->wdw, i, j, params->graph.C);
	if (params->scan.face == &params->graph.SO || params->scan.face == &params->graph.NO)
		texture_put(params, height, params->scan.wall.x - floor(params->scan.wall.x), i, j - 1);
	else
		texture_put(params, height, params->scan.wall.y - floor(params->scan.wall.y), i, j - 1);
	j = (params->max.y - (params->max.y - height) / 2) - 1;
	while (++j < params->max.y)
		mlx_pixel_put(params->ptr, params->wdw, i, j, params->graph.F);
}
