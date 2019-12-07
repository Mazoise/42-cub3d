/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 16:37:14 by mchardin          #+#    #+#             */
/*   Updated: 2019/12/07 16:52:58 by mchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int			check_all_params(t_params *params)
{
	int ret;
	
	ret = 0;
	if ((params->max.i < 0 || params->max.j < 0))
		ret = ft_dprintf(2, "Error\nMissing resolution format\n");
	if (!params->graph.NO.img)
		ret = ft_dprintf(2, "Error\nMissing north texture path\n");
	if (!params->graph.SO.img)
		ret = ft_dprintf(2, "Error\nMissing south texture path\n");
	if (!params->graph.WE.img)
		ret = ft_dprintf(2, "Error\nMissing west texture path\n");
	if (!params->graph.EA.img)
		ret = ft_dprintf(2, "Error\nMissing east texture path\n");
	if (!params->graph.S.img)
		ret = ft_dprintf(2, "Error\nMissing sprite texture path\n");
	if (((BONUS == 0 && !params->graph.F.true)
		|| (BONUS == 1 && !params->bonus.F.img)))
		ret = ft_dprintf(2, "Error\nMissing floor color format\n");
	if (((BONUS == 0 && !params->graph.C.true)
		|| (BONUS == 1 && !params->bonus.C.img)))
		ret = ft_dprintf(2, "Error\nMissing ceiling color format\n");
	return (ret);
}

void		check_format(char *str)
{
	int	i;

	i = ft_strlen(str);
	if (!ft_strncmp(str, "-save", 6))
	{
		ft_dprintf(2, "Error\nMissing map reference before save request\n");
		exit (0);
	}
	else if (i < 5 || ft_strncmp(&str[i - 4], ".cub", 5))
	{
		ft_dprintf(2, "Error\nMap file should end in \".cub\"\n");
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
	if (params->max.i > FULLSCREEN_W)
		params->max.i = FULLSCREEN_W;
	if (params->max.j > FULLSCREEN_H)
		params->max.j = FULLSCREEN_H;
	params->calc.proj = (params->max.j / 2) / tan(M_PI / 6);
	params->calc.step = 0.1;
	params->calc.turn = 0.05;
}
