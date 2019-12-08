/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 11:44:35 by mchardin          #+#    #+#             */
/*   Updated: 2019/12/08 13:29:13 by mchardin         ###   ########.fr       */
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
		put_pix(&params->img, params->bonus.C.txtr, tmp2 , tmp);
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
		put_pix(&params->img, params->bonus.F.txtr, tmp2 , tmp);
		idx->j++;
	}
}
