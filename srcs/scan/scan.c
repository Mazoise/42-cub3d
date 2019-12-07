/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scan.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 21:22:18 by mchardin          #+#    #+#             */
/*   Updated: 2019/12/07 16:03:12 by mchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void		scan_face(t_params *params, double angle, int hrz, int vrt)
{
	which_add(&params->scan.add_horz, angle, hrz);
	which_start(&params->scan.hrz, params->player.pos, angle, hrz);
	which_add(&params->scan.add_vert, angle, vrt);
	which_start(&params->scan.vrt, params->player.pos, angle, vrt);
	close_cam(&params->scan, params->player.pos, &params->scan.nb, params->grid);
	while ((close_cam(&params->scan, params->player.pos, &params->scan.nb, params->grid)))
		;
	if (params->scan.wall.y == params->scan.vrt.y && vrt == 4)
		params->scan.face = &params->graph.WE;
	else if (params->scan.wall.y == params->scan.vrt.y && vrt == 3)
		params->scan.face = &params->graph.EA;
	else if (hrz == 1)
		params->scan.face = &params->graph.NO;
	else
		params->scan.face = &params->graph.SO;
}

static void		dir_scan(t_params *params, double angle)
{
	params->scan.nb = 0;
	if (angle >= M_PI_2 && angle <= M_PI)
		scan_face(params, angle, 1, 3);
	else if (angle >= M_PI + M_PI_2)
		scan_face(params, angle, 2, 4);
	else if (angle <= M_PI_2)
		scan_face(params, angle, 2, 3);
	else
		scan_face(params, angle, 1, 4);
}

void			draw_three_d(t_params *params)
{
	double		angle;
	double		inc;
	// t_pos		dist;
	int			i;

	inc = (M_PI / 3) / params->max.i;
	angle = params->player.compas + M_PI_2 / 3;
	i = 0;
	correct_compas(&angle);
	while (i < params->max.i)
	{
		dir_scan(params, angle);
		line_put(params, fabs(params->player.compas - angle), i);
		sprite(params, angle, i);
		angle -= inc;
		i++;
		correct_compas(&angle);
	}
}

int				draw_in_wdw(t_params *params)
{
	draw_three_d(params);
	mlx_put_image_to_window(params->ptr, params->wdw, params->fullscreen, 0, 0);
	key_events(params);
	return (1);
}
