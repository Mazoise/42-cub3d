// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   sprite.c                                           :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2019/12/01 12:04:39 by mchardin          #+#    #+#             */
// /*   Updated: 2019/12/01 21:05:48 by mchardin         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "cub3d.h"
// // static int		stop_scan(t_pos	scan, t_pos pos, double angle)
// // {
// // 	if (angle >= M_PI_2 && angle <= M_PI
// // 		&& (scan.x >= pos.x || scan.y <= pos.y))
// // 		return (0);
// // 	else if (angle >= M_PI + M_PI_2
// // 		&& (scan.x <= pos.x || scan.y >= pos.y))
// // 		return (0);
// // 	else if (angle < M_PI_2
// // 		&& (scan.x <= pos.x || scan.y <= pos.y))
// // 		return (0);
// // 	else if (angle > M_PI && angle < M_PI + M_PI_2
// // 		&& (scan.x >= pos.x || scan.y >= pos.y))
// // 		return (0);
// // 	else
// // 		return (1);
// // }

// static void		correct_cam(t_pos hrz, t_pos vrt, t_pos *cam, t_idx *nb)
// {
// 	if (sqrt(pow(cam->x - vrt.x, 2) + pow(cam->y - vrt.y, 2))
// 		< sqrt(pow(cam->x - hrz.x, 2) + pow(cam->y - hrz.y, 2)))
// 	{
// 		cam->x = vrt.x;
// 		cam->y = vrt.y;
// 		nb->j -= 1;
// 	}
// 	else
// 	{
// 		cam->x = hrz.x;
// 		cam->y = hrz.y;
// 		nb->i -= 1;
// 	}
// }

// static void		print_sprite(t_params *params, double angle, int i)
// {
// 	t_pos 	cam;
// 	double	dist;
// 	int		height;
// 	t_idx	idx;

// 	idx.i = i;
// 	cam.x = floor(params->scan.wall.x) + 0.5;
// 	cam.y = floor(params->scan.wall.y) + 0.5;
// 	params->scan.face = &params->graph.S;
// 	dist  = params->max.j * sqrt(pow(cam.x - params->player.pos.x, 2) + pow(cam.y - params->player.pos.y, 2));
// 	ft_printf("SPRITE ! %d, %d\n", (int)cam.x, (int)cam.y); //
// 	height = params->max.i / dist * params->calc.proj;
// 	idx.j = (params->max.j - height) / 2;
// 	texture_put(params, height, 0.5, &idx);
// 	(void)angle; //
// }

// static void		scan_sprite(t_params *params, double angle, int i)
// {
// 	if (params->scan.face == &params->graph.EA || params->scan.face == &params->graph.WE)
// 	{
// 		while(params->scan)
// 		params->scan.vrt.x -= params->scan.add_vert.x;
// 		params->scan.vrt.y -= params->scan.add_vert.y;
// 	}
// 	else
// 	{
// 		params->scan.hrz.x -= params->scan.add_horz.x;
// 		params->scan.hrz.y -= params->scan.add_horz.y;
// 	}
// 	while ((int)(params->scan.wall.x) != (int)(params->player.pos.x)
// 		&& (int)(params->scan.wall.y) != (int)(params->player.pos.y))
// 	{
// 		params->scan.vrt.x -= params->scan.add_vert.x;
// 		params->scan.vrt.y -= params->scan.add_vert.y;
// 		params->scan.hrz.x -= params->scan.add_horz.x;
// 		params->scan.hrz.y -= params->scan.add_horz.y;
// 		// while(stop_scan(horz, params->player.pos, angle)
// 		// 	&& !is_grid_pos(horz.x, horz.y, params->grid, '2'))
// 		// {
// 		// 	horz.y -= params->scan.add_horz.y;
// 		// 	horz.x -= params->scan.add_horz.x;
// 		// }
// 		// while(stop_scan(vert, params->player.pos, angle)
// 		// 	&& !is_grid_pos(vert.x, vert.y, params->grid, '2'))
// 		// {
// 		// 	vert.y -= params->scan.add_vert.y;
// 		// 	vert.x -= params->scan.add_vert.x;
// 		// }
// 		correct_cam(params->scan.hrz, params->scan.vrt, &params->scan.wall);
// 		if (is_grid_pos(params->scan.wall.x, params->scan.wall.y, params->grid, '2'))
// 			print_sprite(params, angle, i);
// 	}
// }

// void			sprite_put(t_params *params, double angle, int i)
// {
// 	scan_sprite(params, angle, i);
// 	// dist.y = params->max.j * fabs(params->scan.wall.y - params->player.pos.y);
// 	// dist.x = params->max.j * fabs(params->scan.wall.x - params->player.pos.x);

// }
