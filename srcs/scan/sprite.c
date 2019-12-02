/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 12:04:39 by mchardin          #+#    #+#             */
/*   Updated: 2019/12/02 17:58:28 by mchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
// static int		stop_scan(t_pos	scan, t_pos pos, double angle)
// {
// 	if (angle >= M_PI_2 && angle <= M_PI
// 		&& (scan.x >= pos.x || scan.y <= pos.y))
// 		return (0);
// 	else if (angle >= M_PI + M_PI_2
// 		&& (scan.x <= pos.x || scan.y >= pos.y))
// 		return (0);
// 	else if (angle < M_PI_2
// 		&& (scan.x <= pos.x || scan.y <= pos.y))
// 		return (0);
// 	else if (angle > M_PI && angle < M_PI + M_PI_2
// 		&& (scan.x >= pos.x || scan.y >= pos.y))
// 		return (0);
// 	else
// 		return (1);
// }

void		close_sprite(t_scan *scan, int *nb)
{
	if (sqrt(pow(scan->wall.x - scan->vrt.x, 2) + pow(scan->wall.y - scan->vrt.y, 2))
		>= sqrt(pow(scan->wall.x - scan->hrz.x, 2) + pow(scan->wall.y - scan->hrz.y, 2)))
	{
		scan->wall.x = scan->hrz.x;
		scan->wall.y = scan->hrz.y;
		scan->hrz.x -= scan->add_horz.x;
		scan->hrz.y -= scan->add_horz.y;
	}
	else
	{
		scan->wall.x = scan->vrt.x;
		scan->wall.y = scan->vrt.y;
		scan->vrt.x -= scan->add_vert.x;
		scan->vrt.y -= scan->add_vert.y;
	}
	(*nb)--;
}
#include <stdio.h>
static void		print_sprite(t_params *params, double angle, int i, double inc)
{
	t_pos 	cam;
	double	dist;
	int		height;
	t_idx	idx;
	(void)inc;
	idx.i = i;
	cam.x = floor(params->scan.wall.x) + 0.5;
	cam.y = floor(params->scan.wall.y) + 0.5;
	params->scan.face = &params->graph.S;
	dist  = sqrt(pow(cam.x - params->player.pos.x, 2) + pow(cam.y - params->player.pos.y, 2));
	// ft_printf("SPRITE ! %d, %d\n", (int)cam.x, (int)cam.y); //
	height = params->max.i / (dist * params->max.j) * params->calc.proj;
	idx.j = (params->max.j - height) / 2;
	// double plane_x = cos(angle) * cos(inc) - sin(angle) * sin(inc);
	// double plane_y = sin(angle) * cos(inc) + cos(angle) * sin(inc);
	double ang = asin(((
		(params->player.pos.x - cam.x) * sin(angle))
		+ (cam.y - params->player.pos.y) * cos(angle)) / dist);
	printf("ret %.6f\n", .5 + dist * tan(ang));
	double dir = .5 + dist * tan(ang);
	if (dir >= 0 && dir <= 1)
		texture_put(params, height, dir, &idx);
	(void)angle; // 
}

void		sprite_put(t_params *params, double angle, int i, double inc)
{
	params->scan.vrt.x -= params->scan.add_vert.x;
	params->scan.vrt.y -= params->scan.add_vert.y;
	params->scan.hrz.x -= params->scan.add_horz.x;
	params->scan.hrz.y -= params->scan.add_horz.y;
	while (params->scan.nb > 0)
	{
		close_sprite(&params->scan, &params->scan.nb);
		if (is_grid_pos(params->scan.wall.x, params->scan.wall.y, params->grid, '2'))
			print_sprite(params, angle, i, inc);
	}
}
 