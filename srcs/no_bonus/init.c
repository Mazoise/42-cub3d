/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 10:41:00 by mchardin          #+#    #+#             */
/*   Updated: 2019/12/12 14:54:15 by mchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int				error_conv(char c)
{
	if (c == 'F')
	{
		ft_dprintf(2, "Error\nMultiple definition (floor)\n");
		return (0);
	}
	else if (c == 'C')
	{
		ft_dprintf(2, "Error\nMultiple definition (ceiling)\n");
		return (0);
	}
	else if (c)
	{
		ft_dprintf(2, "Error\nWrong information syntax\n");
		return (0);
	}
	return (1);
}

static t_rgb	*floor_ceil(t_params *params, char c)
{
	if (c == 'F')
	{
		params->graph.f.true = 1;
		return (&params->graph.f);
	}
	else
	{
		params->graph.c.true = 1;
		return (&params->graph.c);
	}
}

static int		conv_color(char *str, t_params *params, char c)
{
	t_rgb	*color;
	int		i;

	i = 0;
	color = floor_ceil(params, c);
	while (str[i] == ' ')
		i++;
	color->red = (unsigned char)ft_atoi(&str[i]);
	while (ft_isdigit(str[i]))
		i++;
	if (str[i] == ',')
		i++;
	color->green = (unsigned char)ft_atoi(&str[i]);
	while (ft_isdigit(str[i]))
		i++;
	if (str[i] == ',')
		i++;
	color->blue = (unsigned char)ft_atoi(&str[i]);
	while (ft_isdigit(str[i]))
		i++;
	while (str[i] == ' ')
		i++;
	if (str[i])
		return (-1);
	return (1);
}

int				conv_params(char *str, t_params *params)
{
	int		i;
	int		ret;

	i = 0;
	ret = 1;
	while (str[i] == ' ')
		i++;
	if (str[i] == 'R')
		ret = conv_resolution(&str[i + 1], params);
	else if (str[i] == 'S' && str[i + 1] != 'O')
		ret = conv_texture(&str[i + 1], params, 's');
	else if (is_compas(str[i]))
		ret = conv_texture(&str[i + 2], params, str[i]);
	else if ((str[i] == 'F' && !params->graph.f.true)
		|| (str[i] == 'C' && !params->graph.c.true))
		ret = conv_color(&str[i + 1], params, str[i]);
	else
		ret = error_conv(str[i]);
	if (ret == -1 && ret++)
		ft_dprintf(2, "Error\nWrong color syntax (R,G,B)");
	return (ret);
}
