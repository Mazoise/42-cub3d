/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialisation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 15:41:19 by mchardin          #+#    #+#             */
/*   Updated: 2019/11/27 12:30:17 by mchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		pre_calc(t_params *params)
{
	params->calc.proj = (params->max.y / 2) / tan(M_PI / 6);
}

int			initialisation(char *mapcub, t_params *params)
{
	init_struct(params);
	if (!(read_map(mapcub, params)))
	{
		ft_printf("READMAP ERROR\n");
		return (0);
	}
	if (!(init_player(&params->player, params->grid)))
	{
		ft_printf("INITPLAYER ERROR\n");
		return (0);
	}
	return (1);
}
