/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 12:04:39 by mchardin          #+#    #+#             */
/*   Updated: 2019/12/01 13:54:55 by mchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

	if (is_grid_pos(vert.x, vert.y, params->grid, '2')
		|| is_grid_pos(horz.x, horz.y, params->grid, '2')

static int		stop_scan(t_pos	scan, t_pos pos, double angle)
{
	if (angle >= M_PI_2 && angle <= M_PI && (scan.x > pos.x || scan.y < pos.y))
		return (0);
	else if (angle >= M_PI + M_PI_2 && (scan.x < pos.x || scan.y > pos.y))
		return (0);
	else if (angle <= M_PI_2 && (scan.x < pos.x || scan.y < pos.y))
		return (0);
	else if (angle >= M_PI && angle <= M_PI + M_PI_2 && (scan.x > pos.x || scan.y > pos.y))
		return (0);
	else
		return (1);
}

static void		scan_sprite(t_params *params, double angle)
{
	t_pos	vert;
	t_pos	horz;
	
	vert = params->scan.wall;
	horz = params->scan.wall;
	while (stop_scan(params->scan.wall, params->player.pos, angle))
	{
		while(stop_scan(horz, params->player.pos, angle)
			&& !is_grid_pos(horz.x, horz.y, params->grid, '2'))
		{
			horz.y += params->scan.add_horz.y;
			horz.x += params->scan.add_horz.x;
		}
		while(stop_scan(vert, params->player.pos, angle)
			&& !is_grid_pos(vert.x, vert.y, params->grid, '2'))
		{
			vert.y += params->scan.add_vert.y;
			vert.x += params->scan.add_vert.x;
		}
		)
	}
}

void			sprite_put(t_params *params, double angle, int i)
{
	scan_sprite(params, angle);
	// dist.y = params->max.j * fabs(params->scan.wall.y - params->player.pos.y);
	// dist.x = params->max.j * fabs(params->scan.wall.x - params->player.pos.x);

}
