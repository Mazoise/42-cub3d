/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 11:44:35 by mchardin          #+#    #+#             */
/*   Updated: 2019/12/07 12:11:40 by mchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	cf_put(t_params *params, t_idx *idx, double height)
{
	double		tmp;
	double		tmp2;
	double		tmp3;
	double		tmp4;

	while (idx->j < params->max.j)
	{
		tmp = height / (2.0 * idx->j - params->max.j);
		tmp4 = tmp * params->scan.wall.y + (1 - tmp) * params->player.pos.y;
		tmp = tmp * params->scan.wall.x + (1 - tmp) * params->player.pos.x;
		tmp3 = (floor((tmp4 - floor(tmp4)) * params->bonus.C.h) + (tmp - floor(tmp))) * params->bonus.C.w;
		tmp = (floor((tmp4 - floor(tmp4)) * params->bonus.F.h) + (tmp - floor(tmp))) * params->bonus.F.w;
		tmp2 = (params->img.len * idx->j + idx->i * (params->img.bpp >> 3));
		put_pix(&params->img, params->bonus.F.txtr, tmp2 , tmp);
		tmp2 = (params->img.len * (params->max.j - idx->j) + idx->i * (params->img.bpp >> 3));
		put_pix(&params->img, params->bonus.C.txtr, tmp2 , tmp3);
		idx->j++;
	}
}
