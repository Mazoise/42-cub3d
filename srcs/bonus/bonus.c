/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 11:44:35 by mchardin          #+#    #+#             */
/*   Updated: 2019/12/11 16:09:37 by mchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		loop_mlx(t_params *params)
{
	mlx_hook(params->wdw, 17, 0, exit_wdw, params);
	mlx_do_key_autorepeatoff(params->ptr);
	mlx_loop_hook(params->ptr, draw_in_wdw, params);
	mlx_hook(params->wdw, 2, 1L << 0, press_key, params);
	mlx_hook(params->wdw, 3, 1L << 1, release_key, params);
	mlx_loop(params->ptr);
}

int				draw_in_wdw(t_params *params)
{
	full_scan(params);
	params->bonus.anim += 0.25;
	if (params->bonus.anim == 9)
		params->bonus.anim = 0;
	mlx_put_image_to_window(params->ptr, params->wdw, params->fullscreen, 0, 0);
	key_events(params);
	if (params->event[MAP] == 1)
		draw_mini_map(params);
	if (params->event[UP] == 1)
		params->bonus.camh -= 5;
	if (params->event[DWN] == 1)
		params->bonus.camh += 5;
	return (1);
}

int		init_minimap(t_params *params)
{
	t_mlx_img	*mm;

	mm = &params->mini_m;
	pre_color(&params->bonus.colors);
	if (!(params->minimap = mlx_new_image(params->ptr, params->max.i, params->max.j)))
	{
		ft_dprintf(2, "Error\nMlx error : %s (minimap)\n", strerror(errno));
		return (0);
	}
	mm->img = mlx_get_data_addr(params->minimap, &mm->bpp, &mm->len, &mm->endian);
	return (1);
}

int		main(int argc, char **argv)
{
	t_params	params;

	check_args(argc, argv, &params);
	if (!(params.ptr = mlx_init()))
	{
		ft_dprintf(2, "Error\nMlx error : %s (init.)\n", strerror(errno));
		return (0);
	}
	if (!(initialisation(argv[1], &params)))
		return (0);
	if (params.screenshot == 1)
		screenshot_bmp(&params);
	if (!(window_mlx(&params, "--- CUB 3D ---")) || !(init_minimap(&params)))
		return (0);
	loop_mlx(&params);
}
