/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quarter_scan.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 17:57:21 by mchardin          #+#    #+#             */
/*   Updated: 2019/12/02 11:59:53 by mchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>

// static void		next_scan(t_pos *dir, t_pos add, char **grid)
// {
// 	while (is_grid_pos(dir->x, dir->y, grid, '0')
// 		|| is_grid_pos(dir->x, dir->y, grid, '2'))
// 	{
// 		dir->y += add.y;
// 		dir->x += add.x;
// 	}
// }

void			scan_ne(t_params *params, double angle, t_pos *wall)
{
	t_pos	player;

	player = params->player.pos;
	which_add(&params->scan.add_horz, angle, 1);
	which_start(&params->scan.hrz, params->player.pos, angle, 1);
	which_add(&params->scan.add_vert, angle, 3);
	which_start(&params->scan.vrt, params->player.pos, angle, 3);
	  close_cam(&params->scan, params->player.pos, &params->scan.nb, params->grid);
	while ((close_cam(&params->scan, params->player.pos, &params->scan.nb, params->grid)))
		;
	if (wall->x == params->scan.hrz.x)
		params->scan.face = &params->graph.NO;
	else
		params->scan.face = &params->graph.EA;
	ft_printf("%d\n", params->scan.nb);
}

void			scan_sw(t_params *params, double angle, t_pos *wall)
{
	t_pos	player;

	player = params->player.pos;
	which_add(&params->scan.add_horz, angle, 2);
	which_start(&params->scan.hrz, params->player.pos, angle, 2);
	which_add(&params->scan.add_vert, angle, 4);
	which_start(&params->scan.vrt, params->player.pos, angle, 4);
	close_cam(&params->scan, params->player.pos, &params->scan.nb, params->grid);
	while ((close_cam(&params->scan, params->player.pos, &params->scan.nb, params->grid)))
		;
	if (wall->y == params->scan.vrt.y)
		params->scan.face = &params->graph.WE;
	else
		params->scan.face = &params->graph.SO;
}

void			scan_se(t_params *params, double angle, t_pos *wall)
{
	t_pos	player;

	player = params->player.pos;
	which_add(&params->scan.add_horz, angle, 2);
	which_start(&params->scan.hrz, params->player.pos, angle, 2);
	which_add(&params->scan.add_vert, angle, 3);
	which_start(&params->scan.vrt, params->player.pos, angle, 3);
	close_cam(&params->scan, params->player.pos, &params->scan.nb, params->grid);
	while ((close_cam(&params->scan, params->player.pos, &params->scan.nb, params->grid)))
		;
	if (wall->y == params->scan.vrt.y)
		params->scan.face = &params->graph.EA;
	else
		params->scan.face = &params->graph.SO;
}

void			scan_nw(t_params *params, double angle, t_pos *wall)
{
	t_pos	player;

	player = params->player.pos;
	which_add(&params->scan.add_horz, angle, 1);
	which_start(&params->scan.hrz, params->player.pos, angle, 1);
	which_add(&params->scan.add_vert, angle, 4);
	which_start(&params->scan.vrt, params->player.pos, angle, 4);
	close_cam(&params->scan, params->player.pos, &params->scan.nb, params->grid);
	while ((close_cam(&params->scan, params->player.pos, &params->scan.nb, params->grid)))
		;
	if (wall->y == params->scan.vrt.y)
		params->scan.face = &params->graph.WE;
	else
		params->scan.face = &params->graph.NO;
}
