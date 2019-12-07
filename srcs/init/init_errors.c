/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_errors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/07 19:12:35 by mchardin          #+#    #+#             */
/*   Updated: 2019/12/07 19:55:12 by mchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		txtr_error(char c)
{
	if (c == 'N')
		ft_dprintf(2, "(north texture)\n");
	else if (c == 'S')
		ft_dprintf(2, "(south texture)\n");
	else if (c == 'E')
		ft_dprintf(2, "(east texture)\n");
	else if (c == 'W')
		ft_dprintf(2, "(west texture)\n");
	else if (c == 'F')
		ft_dprintf(2, "(floor texture)\n");
	else if (c == 'C')
		ft_dprintf(2, "(ceiling texture)\n");
	else
		ft_dprintf(2, "(sprite texture)\n");
}

void		player_error(int pos)
{
	if (pos > 1)
		ft_dprintf(2, "Error\nNo multi player mode available on this game\n");
	else if (pos < 1)
		ft_dprintf(2, "Error\nMissing starting point in map\n");
}

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
