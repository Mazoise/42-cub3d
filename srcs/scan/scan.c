/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scan.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 21:22:18 by mchardin          #+#    #+#             */
/*   Updated: 2019/11/28 20:43:02 by mchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void		dir_scan(t_params *params, double angle)
{
	if (angle >= M_PI_2 && angle <= M_PI)
		scan_ne(params, angle, &params->scan.wall);
	else if (angle >= M_PI + M_PI_2)
		scan_sw(params, angle, &params->scan.wall);
	else if (angle <= M_PI_2)
		scan_se(params, angle, &params->scan.wall);
	else
		scan_nw(params, angle, &params->scan.wall);
}

int				draw_three_d(t_params *params)
{
	double		angle;
	double		inc;
	t_pos		dist;
	int			i;
	static int		stat = 0;

	inc = (M_PI / 3) / params->max.i;
	angle = params->player.compas + M_PI_2 / 3;
	dist.y = params->max.j * fabs(params->scan.wall.y - params->player.pos.y);
	dist.x = params->max.j * fabs(params->scan.wall.x - params->player.pos.x);
	i = 0;
	correct_compas(&angle);
	while (i < params->max.i)
	{
		dir_scan(params, angle);
		line_put(params, fabs(params->player.compas - angle), i);
		angle -= inc;
		i++;
		correct_compas(&angle);
	}
	if (stat == 0)
	{
		screenshot_bmp(params);
		stat++;
	}
	mlx_put_image_to_window(params->ptr, params->wdw, params->fullscreen, 0, 0);
	key_events(params);
	return (1);
}
