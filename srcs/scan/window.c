/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 14:27:33 by mchardin          #+#    #+#             */
/*   Updated: 2019/12/07 21:44:58 by mchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int			exit_wdw(t_params *params)
{
	mlx_destroy_window(params->ptr, params->wdw);
	free_all(params);
	exit(0);
	return (0);
}

int			window_mlx(t_params *params, char *name)
{
	if (!(params->wdw = mlx_new_window(params->ptr, params->max.i, params->max.j, name)))
	{
		ft_dprintf(2, "Error\nMlx error : %s (window)\n", strerror(errno));
		return (0);
	}
	if (!(params->fullscreen = mlx_new_image(params->ptr, params->max.i, params->max.j))
		|| !(params->minimap = mlx_new_image(params->ptr, params->max.i, params->max.j)))
	{
		ft_dprintf(2, "Error\nMlx error : %s (image)\n", strerror(errno));
		return (0);
	}
	params->img.img = mlx_get_data_addr(params->fullscreen, &params->img.bpp, &params->img.len, &params->img.endian);
	params->mini_m.img = mlx_get_data_addr(params->minimap, &params->mini_m.bpp, &params->mini_m.len, &params->mini_m.endian);
	return (1);
}

void		loop_mlx(t_params *params)
{
	mlx_hook(params->wdw, 17, 0, exit_wdw, params);
	mlx_do_key_autorepeatoff(params->ptr);
	mlx_loop_hook(params->ptr, draw_in_wdw, params);
	mlx_hook(params->wdw, 2, 1L << 0, press_key, params);
	mlx_hook(params->wdw, 3, 1L << 1, release_key, params);
	mlx_loop(params->ptr);
}
