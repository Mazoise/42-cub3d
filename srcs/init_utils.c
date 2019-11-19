/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 16:37:14 by mchardin          #+#    #+#             */
/*   Updated: 2019/11/19 17:09:15 by mchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		init_struct(t_params *params)
{
	params->grid = 0;
	params->max.x = -1;
	params->max.y = -1;
	params->graph.NO.img = 0;
	params->graph.SO.img = 0;
	params->graph.WE.img = 0;
	params->graph.EA.img = 0;
	params->graph.S.img = 0;
	params->graph.F = -1;
	params->graph.C = -1;
}

int			check_all_params(t_params *params)
{
	if (params->max.x < 0 || params->max.y < 0 || !params->graph.NO.img
		|| !params->graph.SO.img || !params->graph.WE.img || params->graph.C < 0
		|| !params->graph.S.img || params->graph.F < 0 || !params->graph.EA.img)
	{
		if (params->max.x < 0 || params->max.y < 0)
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

int			check_format(char *str)
{
	int	i;

	i = ft_len_c(str, 0);
	if (is_save_request(str))
	{
		ft_printf("Error\nMissing file format\n");
		return (0);
	}
	else if (i < 5 || str[i - 1] != 'b' || str[i - 2] != 'u'
		|| str[i - 3] != 'c' || str[i - 4] != '.')
	{
		ft_printf("Error\nInvalid file format\n");
		return (0);
	}
	return (1);
}

int			is_valid_grid_element(char c)
{
	if (c == '0' || c == '1' || c == '2' || c == 'N'
		|| c == 'S' || c == 'E' || c == 'W')
		return (1);
	return (0);
}

int			is_save_request(char *str)
{
	int	i;

	i = ft_len_c(str, 0);
	if (i == 6 && str[0] == '-' && str[1] == '-' && str[2] == 's'
		&& str[3] == 'a' && str[4] == 'v' && str[5] == 'e')
		return (1);
	return (0);
}
