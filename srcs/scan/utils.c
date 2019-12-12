/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 15:59:17 by mchardin          #+#    #+#             */
/*   Updated: 2019/12/12 11:09:47 by mchardin         ###   ########.fr       */
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
	if (params->graph.ea.img)
		mlx_destroy_image(params->ptr, params->graph.ea.img);
	if (params->graph.so.img)
		mlx_destroy_image(params->ptr, params->graph.so.img);
	if (params->graph.no.img)
		mlx_destroy_image(params->ptr, params->graph.no.img);
	if (params->graph.we.img)
		mlx_destroy_image(params->ptr, params->graph.we.img);
	if (params->graph.s.img)
		mlx_destroy_image(params->ptr, params->graph.s.img);
	if (params->bonus.c.img)
		mlx_destroy_image(params->ptr, params->bonus.c.img);
	if (params->bonus.f.img)
		mlx_destroy_image(params->ptr, params->bonus.f.img);
	if (params->fullscreen)
		mlx_destroy_image(params->ptr, params->fullscreen);
	if (params->minimap)
		mlx_destroy_image(params->ptr, params->minimap);
	ft_free_strs(params->grid);
}
