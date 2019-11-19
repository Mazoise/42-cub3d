/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readgrid.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 16:20:44 by mchardin          #+#    #+#             */
/*   Updated: 2019/11/19 16:52:16 by mchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <limits.h>
#include <fcntl.h>

int			fill_grid(char *str, t_params *params)
{
	char		*add;

	if (!(add = ft_strdup_no_sp(str)))
	{
		ft_printf("Error\nAllocation fail\n");
		return (0);
	}
	if (!(params->grid = ft_strs_plus_one(params->grid, add)))
	{
		ft_printf("Error\nAllocation fail\n");
		return (0);
	}
	return (1);
}

int			first_fill_grid(char *str, t_params *params)
{
	if (!(params->grid[0] = ft_strdup_no_sp(str)))
	{
		ft_printf("Error\nAllocation fail\n");
		free(params->grid);
		return (0);
	}
	return (1);
}
