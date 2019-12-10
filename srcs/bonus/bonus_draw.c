/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_draw.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 10:26:38 by mchardin          #+#    #+#             */
/*   Updated: 2019/12/10 11:11:35 by mchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
		tmp2 = (params->img.len * i + idx->i * (params->img.bpp >> 3));
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
		idx->j++;
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
	if (idx.j < (params->max.j - height) / 2)
		idx.j = (params->max.j - height) / 2;
	pct = pct_calc(params);
	texture_put(params, height, pct, &idx);
	cf_put(params, &idx, height, angle);
}
