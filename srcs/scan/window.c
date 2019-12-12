/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 14:27:33 by mchardin          #+#    #+#             */
/*   Updated: 2019/12/12 10:41:23 by mchardin         ###   ########.fr       */
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
	t_mlx_img	*img;

	img = &params->img;
	if (!(params->wdw =
		mlx_new_window(params->ptr, params->max.i, params->max.j, name)))
	{
		ft_dprintf(2, "Error\nMlx error : %s (window)\n", strerror(errno));
		return (0);
	}
	if (!(params->fullscreen =
		mlx_new_image(params->ptr, params->max.i, params->max.j)))
	{
		ft_dprintf(2, "Error\nMlx error : %s (image)\n", strerror(errno));
		return (0);
	}
	img->img = mlx_get_data_addr(params->fullscreen,
		&img->bpp, &img->len, &img->endian);
	return (1);
}
