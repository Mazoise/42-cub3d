/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 14:49:07 by mchardin          #+#    #+#             */
/*   Updated: 2021/09/14 20:00:41 by mchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		dir_vect(t_pos *dir, t_pos *hit, double compas)
{
	correct_compas(&compas);
	dir->y += 0.1 * sin(compas);
	dir->x += 0.1 * cos(compas);
	hit->y += 0.2 * sin(compas);
	hit->x += 0.2 * cos(compas);
}

void		key_events(t_params *params)
{
	t_pos		dir;
	t_pos		hit;

	dir.x = params->player.pos.x;
	dir.y = params->player.pos.y;
	hit.x = params->player.pos.x;
	hit.y = params->player.pos.y;
	if (params->event[CAM_L] == 1)
		params->player.compas += 0.06;
	if (params->event[CAM_R] == 1)
		params->player.compas -= 0.06;
	correct_compas(&params->player.compas);
	if (params->event[FORW] == 1)
		dir_vect(&dir, &hit, params->player.compas);
	if (params->event[BCKW] == 1)
		dir_vect(&dir, &hit, params->player.compas + M_PI);
	if (params->event[LEFT] == 1)
		dir_vect(&dir, &hit, params->player.compas + M_PI_2);
	if (params->event[RGHT] == 1)
		dir_vect(&dir, &hit, params->player.compas + M_PI + M_PI_2);
	walk_here(dir, hit, &params->player.pos, params);
}

int			press_key(int keycode, t_params *params)
{
	if (keycode == LEFT_KEY || keycode == Q_KEY)
		params->event[CAM_L] = 1;
	else if (keycode == RIGHT_KEY || keycode == E_KEY)
		params->event[CAM_R] = 1;
	else if (keycode == TAB_KEY)
		params->event[MAP] = 1;
	else if (keycode == W_KEY)
		params->event[FORW] = 1;
	else if (keycode == S_KEY)
		params->event[BCKW] = 1;
	else if (keycode == A_KEY)
		params->event[LEFT] = 1;
	else if (keycode == D_KEY)
		params->event[RGHT] = 1;
	else if (keycode == UP_KEY)
		params->event[UP] = 1;
	else if (keycode == DOWN_KEY)
		params->event[DWN] = 1;
	else if (keycode == F_KEY && params->event[OBJ] == 1)
		params->event[OBJ] = 0;
	else if (keycode == F_KEY && params->event[OBJ] == 0)
		params->event[OBJ] = 1;
	return (1);
}

int			release_key(int keycode, t_params *params)
{
	if (keycode == ESC_KEY)
		exit_wdw(params);
	if (keycode == LEFT_KEY || keycode == Q_KEY)
		params->event[CAM_L] = 0;
	else if (keycode == RIGHT_KEY || keycode == E_KEY)
		params->event[CAM_R] = 0;
	else if (keycode == TAB_KEY)
		params->event[MAP] = 0;
	else if (keycode == W_KEY)
		params->event[FORW] = 0;
	else if (keycode == S_KEY)
		params->event[BCKW] = 0;
	else if (keycode == A_KEY)
		params->event[LEFT] = 0;
	else if (keycode == D_KEY)
		params->event[RGHT] = 0;
	else if (keycode == UP_KEY)
		params->event[UP] = 0;
	else if (keycode == DOWN_KEY)
		params->event[DWN] = 0;
	return (1);
}
