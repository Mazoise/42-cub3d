/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dir_scan.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 18:21:54 by mchardin          #+#    #+#             */
/*   Updated: 2019/11/24 14:34:19 by mchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>
#include <stdio.h> //

void	int_to_img(t_mlx_img *img, unsigned int color, int i, int j)
{
	int		k;

	k = 0;
	char	*cursor = img->img;
	cursor += j * img->len + i * (img->bpp / 8);
	while (k < img->bpp / 8)
	{
		cursor[k] = color / pow(256, k);
		// img->img[((img->len * j) + i * (img->bpp / 8)) + k] = color / pow(256, k);
		k++;
	}
	// ft_printf("%d\n", img->len);
}

void	img_to_int(t_mlx_img tmp, t_texture *txtr)
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

void	texture_put(t_params *params, double height, double pct, int i, int j)
{
	int			k;
	double		tmp;
	double		tmp2;

	k = 0;
	while (k < height)
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
