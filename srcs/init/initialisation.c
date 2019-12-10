/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialisation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 15:41:19 by mchardin          #+#    #+#             */
/*   Updated: 2019/12/10 09:02:11 by mchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int			initialisation(char *mapcub, t_params *params)
{
	init_struct(params);
	if (!(read_map(mapcub, params)))
		return (0);
	if (!(init_player(&params->player, params->grid)))
		return (0);
	pre_calc(params);
	return (1);
}
