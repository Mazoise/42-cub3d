/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dir_scan.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 18:21:54 by mchardin          #+#    #+#             */
/*   Updated: 2019/11/25 10:02:38 by mchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>
#include <stdio.h> //

// void	txtr_to_image(t_mlx_img *dst, t_mlx_img src, t_pos dst_pos, t_pos src_pos)
// {
// 	int		i;
// 	int		j;

// 	src.bpp /= 8;
// 	i = 0;
// 	while (i < txtr->h * txtr->w)
// 	{
// 		j = 0;
// 		while (j < tmp.bpp)
// 		{
// 			txtr->txtr[i] += pow(256, j) * (unsigned char)tmp.img[i * tmp.bpp + j];
// 			j++;
// 		}
// 		i++;
// 	}
// }

void	int_to_img(t_mlx_img *img, unsigned int color, int i, int j)
{
	int		k;

	k = 0;
	while (k < img->bpp / 8)
	{
		img->img[((img->len * j) + i * (img->bpp / 8)) + k] = color / pow(256, k);
		k++;
	}
}

void	img_to_intSW(t_mlx_img tmp, t_texture *txtr)
{
	int		i;
	int		j;

	tmp.bpp /= 8;
	i = 0;
	while (i < txtr->h * txtr->w)
	{
		j = 0;
		while (j < tmp.bpp)
		{
			txtr->txtr[i] += pow(256, j) * (unsigned char)tmp.img[i * tmp.bpp + j];
			j++;
		}
		i++;
	}
}

void	img_to_intNE(t_mlx_img tmp, t_texture *txtr)
{
	int		i;
	int		j;
	int		k;

	tmp.bpp /= 8;
	i = 1;
	k = 0;
	while (k <= txtr->h)
	{
		j = 0;
		while (j < tmp.bpp)
		{
			txtr->txtr[txtr->w * k + txtr->w - i] += pow(256, j) * (unsigned char)tmp.img[(txtr->w * k + i - 1) * tmp.bpp + j];
			j++;
		}
		i++;
		if (i == txtr->w + 1)
		{
			if (k == txtr->h)
				break;
			i = 1;
			k++;
		}
	}
}

void	texture_put(t_params *params, double height, double pct, int i, int j)
{
	int			k;
	int			end;
	double		tmp;
	double		tmp2;

	if (height > params->max.y)
	{
		k = (height - params->max.y) / 2;
		end = params->max.y + (height - params->max.y) / 2;
	}
	else
	{
		k = 0;
		end = height;
	}
	while (k < end)
	{
		tmp = k / height;
		tmp2 = floor(tmp * params->scan.face->h) * params->scan.face->w + pct * params->scan.face->w;
		int_to_img(&params->img, params->scan.face->txtr[(int)tmp2], i, j);
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

	dist = cos(inc) * params->max.y * sqrt(pow(params->scan.wall.x - params->player.pos.x, 2) + pow(params->scan.wall.y - params->player.pos.y, 2));
	j = -1;
//	dist = (fabs(params->scan.wall.x - params->player.pos.x) / cos(M_PI / 2 - angle) * cos(angle));
	proj = (params->max.y / 2) / tan(M_PI / 6); //constant -> ajouter a la struct
	height = params->max.x / dist * proj;
	while (++j < (params->max.y - height) / 2)
		int_to_img(&params->img, params->graph.C, i, j);
	if (params->scan.face == &params->graph.SO || params->scan.face == &params->graph.NO)
		texture_put(params, height, params->scan.wall.y - floor(params->scan.wall.y), i, j - 1);
	else
		texture_put(params, height, params->scan.wall.x - floor(params->scan.wall.x), i, j - 1);
	j = (params->max.y - (params->max.y - height) / 2) - 1;
	while (++j < params->max.y)
		int_to_img(&params->img, params->graph.F, i, j);
}
