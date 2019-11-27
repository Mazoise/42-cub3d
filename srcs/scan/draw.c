/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dir_scan.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 18:21:54 by mchardin          #+#    #+#             */
/*   Updated: 2019/11/27 20:40:14 by mchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>

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
	int		tmp;

	k = 0;
	tmp = ((img->len * j) + i * (img->bpp >> 3));
	while (k < img->bpp >> 3)
	{
		img->img[tmp + k] = color / pow(256, k);
		k++;
	}
}

void	img_to_intsw(t_mlx_img tmp, t_texture *txtr)
{
	int				i;
	int				j;
	unsigned char	argb;

	tmp.bpp >>= 3;
	i = 0;
	while (i < txtr->h * txtr->w)
	{
		j = 0;
		while (j < tmp.bpp)
		{
			argb = (unsigned char)tmp.img[i * tmp.bpp + j];
			txtr->txtr[i] += pow(256, j) * argb;
			j++;
		}
		i++;
	}
}

void	img_to_intne(t_mlx_img tmp, t_texture *txtr)
{
	int		i;
	int		j;
	int		k;
	int		idx1;
	int		idx2;

	tmp.bpp /= 8;
	i = 0;
	k = 0;
	while (1)
	{
		j = -1;
		idx1 = txtr->w * k + txtr->w - (++i);
		while (++j < tmp.bpp)
		{
			idx2 = (txtr->w * k + i - 1) * tmp.bpp + j;
			txtr->txtr[idx1] += pow(256, j) * (unsigned char)tmp.img[idx2];
		}
		if (i == txtr->w)
		{
			if (k++ == txtr->h)
				break ;
			i = 0;
		}
	}
}

void	texture_put(t_params *params, double height, double pct, t_idx idx)
{
	int			k;
	int			j;
	int			end;
	double		tmp;
	double		tmp2;

	j = idx.j;
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
		tmp = k / height * params->scan.face->h;
		tmp2 = floor(tmp) * params->scan.face->w + pct * params->scan.face->w;
		int_to_img(&params->img, params->scan.face->txtr[(int)tmp2], idx.i, j);
		j++;
		k++;
	}
}

void	line_put(t_params *params, double inc, int i)
{
	double	dist;
	int		height;
	t_pos	power;
	t_idx	idx;
	double	pct;

	idx.i = i;
	idx.j = -1;
	power.x = pow(params->scan.wall.x - params->player.pos.x, 2);
	power.y = pow(params->scan.wall.y - params->player.pos.y, 2);
	dist = cos(inc) * params->max.y * sqrt(power.x + power.y);
	height = params->max.x / dist * params->calc.proj;
	while (++idx.j < (params->max.y - height) / 2)
		int_to_img(&params->img, params->graph.C, idx.i, idx.j);
	if (params->scan.face == &params->graph.SO
		|| params->scan.face == &params->graph.NO)
		pct = params->scan.wall.y - floor(params->scan.wall.y);
	else
		pct = params->scan.wall.x - floor(params->scan.wall.x);
	texture_put(params, height, pct, idx);
	idx.j = (params->max.y - (params->max.y - height) / 2) - 1;
	while (++idx.j < params->max.y)
		int_to_img(&params->img, params->graph.F, idx.i, idx.j);
}
