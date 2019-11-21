/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quarter_scan.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 17:57:21 by mchardin          #+#    #+#             */
/*   Updated: 2019/11/21 20:31:07 by mchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>

void	scan_ne(t_params *params, double angle)
{
	t_pos	horz;
	t_pos	vert;

	horz = floor_scan_horz(&params->player.pos, params->grid, angle);
	vert = ceil_scan_vert(&params->player.pos, params->grid, angle);

	params->scan.wall.y = (horz.y > vert.y || horz.x < vert.x ? vert.y : horz.y);
	params->scan.wall.x = (params->scan.wall.y == vert.y ? vert.x : horz.x);
	if (params->scan.wall.y == vert.y)
		params->scan.face = &params->graph.EA;
	else
		params->scan.face = &params->graph.NO;
}

void	scan_sw(t_params *params, double angle)
{
	t_pos	horz;
	t_pos	vert;

	horz = ceil_scan_horz(&params->player.pos, params->grid, angle);
	vert = floor_scan_vert(&params->player.pos, params->grid, angle);

	params->scan.wall.y = (horz.y < vert.y || horz.x > vert.x ? vert.y : horz.y);
	params->scan.wall.x = (params->scan.wall.y == vert.y ? vert.x : horz.x);
	if (params->scan.wall.y == vert.y)
		params->scan.face = &params->graph.WE;
	else
		params->scan.face = &params->graph.SO;
}

void	scan_se(t_params *params, double angle)
{
	t_pos	horz;
	t_pos	vert;

	horz = ceil_scan_horz(&params->player.pos, params->grid, angle);
	vert = ceil_scan_vert(&params->player.pos, params->grid, angle);

	params->scan.wall.y = (horz.y > vert.y || horz.x > vert.x ? vert.y : horz.y);
	params->scan.wall.x = (params->scan.wall.y == vert.y ? vert.x : horz.x);
	if (params->scan.wall.y == vert.y)
		params->scan.face = &params->graph.EA;
	else
		params->scan.face = &params->graph.SO;
}

void	scan_nw(t_params *params, double angle)
{
	t_pos	horz;
	t_pos	vert;

	horz = floor_scan_horz(&params->player.pos, params->grid, angle);
	vert = floor_scan_vert(&params->player.pos, params->grid, angle);

	params->scan.wall.y = (horz.y < vert.y || horz.x < vert.x ? vert.y : horz.y);
	params->scan.wall.x = (params->scan.wall.y == vert.y ? vert.x : horz.x);
	if (params->scan.wall.y == vert.y)
		params->scan.face = &params->graph.WE;
	else
		params->scan.face = &params->graph.NO;
}
