/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialisation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 15:41:19 by mchardin          #+#    #+#             */
/*   Updated: 2019/11/19 18:27:18 by mchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int			initialisation(char *mapcub, t_params *params)
{
	init_struct(params);
	if (!(read_map(mapcub, params)))
	{
		ft_printf("READMAP ERROR\n");
		return (0);
	}
	if(!(init_player(params)))
	{
		ft_printf("INITPLAYER ERROR\n");
		return (0);
	}	
	return (1);
}
