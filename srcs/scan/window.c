/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 14:27:33 by mchardin          #+#    #+#             */
/*   Updated: 2019/11/27 21:15:09 by mchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int			exit_wdw(t_params *params)
{
	mlx_destroy_window(params->ptr, params->wdw);
	mlx_destroy_image(params->ptr, params->fullscreen);
	ft_free_strs(params->grid);
	exit(0);
	return (0);
}

int			window_mlx(t_params *params, char *name)
{
	t_mlx_img	*img;
	t_pos		max;
	void		*fs;

	img = &params->img;
	max = params->max;
	if (!(params->wdw = mlx_new_window(params->ptr, max.x, max.y, name)))
	{
		ft_printf("Error\nInitialisation of mlx window failed\n");
		return (0);
	}
	if (!(params->fullscreen = mlx_new_image(params->ptr, max.x, max.y)))
	{
		ft_printf("Error\nInitialisation of mlx img failed\n");
		return (0);
	}
	fs = params->fullscreen;
	img->img = mlx_get_data_addr(fs, &img->bpp, &img->len, &img->endian);
	return (1);
}

void		loop_mlx(t_params *params)
{
	mlx_hook(params->wdw, 17, 0, exit_wdw, params);
	mlx_do_key_autorepeatoff(params->ptr);
	mlx_loop_hook(params->ptr, draw_three_d, params);
	mlx_hook(params->wdw, 2, 1L << 0, press_key, params);
	mlx_hook(params->wdw, 3, 1L << 1, release_key, params);
	mlx_loop(params->ptr);
}
