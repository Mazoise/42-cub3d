/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 16:37:14 by mchardin          #+#    #+#             */
/*   Updated: 2019/11/30 10:23:51 by mchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		init_struct(t_params *params)
{
	params->grid = 0;
	params->max.i = -1;
	params->max.j = -1;
	params->graph.NO.img = 0;
	params->graph.SO.img = 0;
	params->graph.WE.img = 0;
	params->graph.EA.img = 0;
	params->graph.S.img = 0;
	params->graph.F = -1;
	params->graph.C = -1;
	ft_memset(params->event, 0, 7);
}

int			check_all_params(t_params *params)
{
	if (params->max.i < 0 || params->max.j < 0 || !params->graph.NO.img
		|| !params->graph.SO.img || !params->graph.WE.img || params->graph.C < 0
		|| !params->graph.S.img || params->graph.F < 0 || !params->graph.EA.img)
	{
		if (params->max.i < 0 || params->max.j < 0)
			ft_printf("Error\nMissing resolution format\n");
		if (!params->graph.NO.img)
			ft_printf("Error\nMissing north texture path\n");
		if (!params->graph.SO.img)
			ft_printf("Error\nMissing south texture path\n");
		if (!params->graph.WE.img)
			ft_printf("Error\nMissing west texture path\n");
		if (!params->graph.EA.img)
			ft_printf("Error\nMissing east texture path\n");
		if (!params->graph.S.img)
			ft_printf("Error\nMissing sprite texture path\n");
		if (params->graph.F < 0)
			ft_printf("Error\nMissing floor color format\n");
		if (params->graph.C < 0)
			ft_printf("Error\nMissing ceiling color format\n");
		return (0);
	}
	return (1);
}

void		check_format(char *str)
{
	int	i;

	i = ft_strlen(str);
	if (!ft_strncmp(str, "-save", 6))
	{
		ft_printf("Error\nMissing map reference before save request\n");
		exit (0);
	}
	else if (i < 5 || ft_strncmp(&str[i - 4], ".cub", 5))
	{
		ft_printf("Error\nMap file should end in \".cub\"\n");
		exit (0);
	}
}

int			is_grid(char c)
{
	if (c == '0' || c == '1' || c == '2')
		return (1);
	return (0);
}

int			is_compas(char c)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (1);
	return (0);
}

void		pre_calc(t_params *params)
{
	params->calc.proj = (params->max.j / 2) / tan(M_PI / 6);
}
