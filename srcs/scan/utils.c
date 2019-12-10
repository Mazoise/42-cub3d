/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 15:59:17 by mchardin          #+#    #+#             */
/*   Updated: 2019/12/10 10:02:55 by mchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		correct_compas(double *compas)
{
	if (*compas > 2 * M_PI)
		*compas = *compas - 2 * M_PI;
	else if (*compas < 0)
		*compas = *compas + 2 * M_PI;
}

int			is_grid_pos(double x, double y, char **grid, char c)
{
	t_pos	max;

	max.y = ft_strlen(grid[0]);
	max.x = ft_strslen(grid);
	if (x > 0.5 && x < max.x - 0.5
		&& y > 0.5 && y < max.y - 0.5
		&& grid[(int)x][(int)y] == c)
		return (1);
	return (0);
}

void		put_cut_nb_fd(int nb, int fd, int len)
{
	int		k;

	k = 0;
	while (k < len)
	{
		ft_putchar_fd(nb / (int)pow(256, k), fd);
		k++;
	}
}

void		free_all(t_params *params)
{
	if (params->graph.EA.img)
		mlx_destroy_image(params->ptr, params->graph.EA.img);
	if (params->graph.SO.img)
		mlx_destroy_image(params->ptr, params->graph.SO.img);
	if (params->graph.NO.img)
		mlx_destroy_image(params->ptr, params->graph.NO.img);
	if (params->graph.WE.img)
		mlx_destroy_image(params->ptr, params->graph.WE.img);
	if (params->graph.S.img)
		mlx_destroy_image(params->ptr, params->graph.S.img);
	if (params->bonus.C.img)
		mlx_destroy_image(params->ptr, params->bonus.C.img);
	if (params->bonus.F.img)
		mlx_destroy_image(params->ptr, params->bonus.F.img);
	if (params->fullscreen)
		mlx_destroy_image(params->ptr, params->fullscreen);
	if (params->minimap)
		mlx_destroy_image(params->ptr, params->minimap);
	ft_free_strs(params->grid);
}
