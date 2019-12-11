/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_draw.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 10:26:38 by mchardin          #+#    #+#             */
/*   Updated: 2019/12/11 16:59:36 by mchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		shadow_pix(t_mlx_img *img, int dst, int dark)
{
	int		i;
	int		opp_img;

	i = 0;
	opp_img = img->bpp >> 3;
	while (i < opp_img + 1)
	{
		if (img->img[dst + i] > dark)
			img->img[dst + i] -= dark;
		else
			img->img[dst + i] = 0;
		i++;
	}
}

void		shadow_put(t_params *params, double height, t_idx *idx)
{
	int			k;
	int			end;
	double		tmp;
	double		tmp2;

	if (height < params->max.j)
	{
		k = (params->max.j - height) / 2;
		end = params->max.j - (params->max.j - height) / 2;
	}
	else
	{
		k = 0;
		end = params->max.j;
	}
	while (k < end)
	{
		tmp = 9 * params->max.j / height;
		tmp2 = (params->img.len * k + idx->i * (params->img.bpp >> 3));
		if (k >= 0 && k < params->max.j)
			shadow_pix(&params->img, tmp2, tmp);
		k++;
	}
}

void	put_sky(t_params *params, t_idx *idx, double height, double angle)
{
	int			end;
	int			i;
	double		tmp;
	double		tmp2;

	end = (params->max.j - height) / 2;
	i = 0;
	while (i < end)
	{
		tmp = 2 * M_PI - angle / (2 * M_PI);
		tmp = ((2 * i * params->bonus.C.h) / params->max.j
			+ tmp) * params->bonus.C.w;
		tmp2 = params->img.len * i + idx->i * (params->img.bpp >> 3);
		put_pix(&params->img, params->bonus.C.txtr, tmp2, tmp);
		i++;
	}
}

void	cf_put(t_params *params, t_idx *idx, double height, double angle)
{
	double		tmp;
	double		tmp2;
	double		tmp3;

	put_sky(params, idx, height, angle);
	while (idx->j < params->max.j)
	{
		tmp = height / (2.0 * idx->j - params->max.j);
		tmp3 = tmp * params->scan.wall.y + (1 - tmp) * params->player.pos.y;
		tmp = tmp * params->scan.wall.x + (1 - tmp) * params->player.pos.x;
		tmp = (floor((tmp3 - floor(tmp3)) * params->bonus.F.h)
			+ (tmp - floor(tmp))) * params->bonus.F.w;
		tmp2 = (params->img.len * idx->j + idx->i * (params->img.bpp >> 3));
		put_pix(&params->img, params->bonus.F.txtr, tmp2, tmp);
		shadow_pix(&params->img, tmp2, 80 * (params->max.j / idx->j) * (params->max.j - idx->j) / (params->max.j));
		idx->j++;
	}
}

void		sprite_put(t_params *params, double height, double pct, t_idx *idx)
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
		tmp = floor(k * params->scan.face->h / height) * params->scan.face->w + floor(params->bonus.anim) * floor(params->scan.face->w / 9.0) + pct * floor(params->scan.face->w / 9.0);
		tmp2 = (params->img.len * idx->j + idx->i * (params->img.bpp >> 3));
		add_pix(&params->img, params->scan.face->txtr, tmp2, tmp);
		idx->j++;
		k++;
	}
}

void		line_put(t_params *params, double inc, int i, double angle)
{
	double	dist;
	double	height;
	t_pos	power;
	t_idx	idx;
	double	pct;

	idx.i = i;
	power.x = pow(params->scan.wall.x - params->player.pos.x, 2);
	power.y = pow(params->scan.wall.y - params->player.pos.y, 2);
	dist = cos(inc) * rsqrt(power.x + power.y);
	height = params->max.i / (dist * params->max.j) * params->calc.proj;
	idx.j = params->max.j > height ? (params->max.j - height) / 2 : 0;
	pct = pct_calc(params);
	texture_put(params, height, pct, &idx);
	shadow_put(params, height, &idx);
	cf_put(params, &idx, height, angle);
}
