/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 15:59:17 by mchardin          #+#    #+#             */
/*   Updated: 2019/11/28 20:31:30 by mchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	correct_compas(double *compas)
{
	if (*compas > 2 * M_PI)
		*compas = *compas - 2 * M_PI;
	else if (*compas < 0)
		*compas = *compas + 2 * M_PI;
}

int		is_grid_pos(double x, double y, char **grid, char c)
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
