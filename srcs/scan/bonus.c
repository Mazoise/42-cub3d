/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 11:44:35 by mchardin          #+#    #+#             */
/*   Updated: 2019/12/04 13:27:53 by mchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
		#include <stdio.h>

// void	cf_put(t_params *params, double height, t_texture txtr, t_idx *idx, double angle, double dist)
// {
// 	int			end;
// 	double		tmp;
// 	double		tmp2;
// 	double		y;
// 	double		x;

// 	// (void)angle;
// 	// (void)dist;
// 	if (idx->j == -1 && idx->j++)
// 		end = (params->max.j - height) / 2;
// 	else
// 		end = params->max.j;
// 	// y = dist / abs(idx->j - end);
// 	(void)dist;
// 	// double projangle = asin(sqrt(pow(height, 2) + pow(dist * params->max.j, 2)));
// 	// dist = end - idx->j;
// 	x = 0;
// 	while (idx->j < end)
// 	{
// 		y = (params->max.i / height) / params->calc.proj;
// 		tmp = params->scan.wall.x + x * cos(M_PI - angle);
// 		// tmp = height;
// 		double tmpy = params->scan.wall.y + x * sin(M_PI - angle);
// 		// tmp = tmp * dist * cos(angle) + params->player.pos.x;
// 		// printf("%f\n", tmp);
// 		tmp = (floor((tmp - floor(tmp)) * txtr.h) + (tmpy - floor(tmpy))) * txtr.w;

void	cf_put(t_params *params, t_idx *idx, double dist)
{
	double		tmp;
	double		tmp2;
	double		tmp3;
	double		distplayer;
	double		x;

	distplayer = 0.0;
	x = 0;
	while (idx->j < params->max.j)
	{
		tmp = params->max.j / (2.0 * idx->j - params->max.j);
		tmp = (tmp - distplayer) / (dist - distplayer);
		double tmpy = tmp * params->scan.wall.y + (1 - tmp) * params->player.pos.y;
		tmp = tmp * params->scan.wall.x + (1 - tmp) * params->player.pos.x;
		tmp3 = (floor((tmp - floor(tmp)) * params->bonus.C.h) + (tmpy - floor(tmpy))) * params->bonus.C.w;
		tmp = (floor((tmp - floor(tmp)) * params->bonus.F.h) + (tmpy - floor(tmpy))) * params->bonus.F.w;
		tmp2 = (params->img.len * idx->j + idx->i * (params->img.bpp >> 3));
		put_pix(&params->img, params->bonus.F.txtr, tmp2 , tmp);
		tmp2 = (params->img.len * (params->max.j - idx->j) + idx->i * (params->img.bpp >> 3));
		put_pix(&params->img, params->bonus.C.txtr, tmp2 , tmp3);
		idx->j++;
	}
}
