/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/16 14:45:55 by mchardin          #+#    #+#             */
/*   Updated: 2019/12/10 10:18:29 by mchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>

void		loop_mlx(t_params *params)
{
	mlx_hook(params->wdw, 17, 0, exit_wdw, params);
	mlx_do_key_autorepeatoff(params->ptr);
	mlx_loop_hook(params->ptr, draw_in_wdw, params);
	mlx_hook(params->wdw, 2, 1L << 0, press_key, params);
	mlx_hook(params->wdw, 3, 1L << 1, release_key, params);
	mlx_loop(params->ptr);
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
	if (!(window_mlx(&params, "--- CUB 3D ---")))
		return (0);
	loop_mlx(&params);
}
