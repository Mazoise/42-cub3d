/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 18:21:54 by mchardin          #+#    #+#             */
/*   Updated: 2019/12/10 10:44:24 by mchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>

void		put_pix(t_mlx_img *img, t_mlx_img txtr, int dst, int src)
{
	int		i;
	int		opp_img;
	int		opp_txtr;

	i = 0;
	opp_txtr = txtr.bpp >> 3;
	opp_img = img->bpp >> 3;
	while (i < opp_txtr && i < opp_img)
	{
		img->img[dst + i] = txtr.img[src * opp_txtr + i];
		i++;
	}
}

void		rgb_to_img(t_mlx_img *img, t_rgb color, int i, int j)
{
	int		tmp;

	tmp = ((img->len * j) + i * (img->bpp >> 3));
	img->img[tmp + 0] = color.blue;
	img->img[tmp + 1] = color.green;
	img->img[tmp + 2] = color.red;
}

void		texture_put(t_params *params, double height, double pct, t_idx *idx)
{
	int			k;
	int			end;
	double		tmp;
	double		tmp2;

	if (height > params->max.j)
	{
		k = (height - params->max.j) / 2;
		end = params->max.j + (height - params->max.j) / 2;
	}
	else
	{
		k = 0;
		end = height;
	}
	while (k < end)
	{
		tmp = floor(k * params->scan.face->h / height) + pct;
		tmp = tmp * params->scan.face->w;
		tmp2 = (params->img.len * idx->j + idx->i * (params->img.bpp >> 3));
		if (idx->j >= 0 && idx->j < params->max.j)
			put_pix(&params->img, params->scan.face->txtr, tmp2, tmp);
		idx->j++;
		k++;
	}
}

double		pct_calc(t_params *params)
{
	double pct;

	if (params->scan.face == &params->graph.SO)
		pct = ceil(params->scan.wall.y) - params->scan.wall.y;
	else if (params->scan.face == &params->graph.NO)
		pct = params->scan.wall.y - floor(params->scan.wall.y);
	else if (params->scan.face == &params->graph.EA)
		pct = params->scan.wall.x - floor(params->scan.wall.x);
	else
		pct = ceil(params->scan.wall.x) - params->scan.wall.x;
	return (pct);
}
