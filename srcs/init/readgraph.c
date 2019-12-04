/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readgraph.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 12:11:22 by mchardin          #+#    #+#             */
/*   Updated: 2019/12/03 12:02:14 by mchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int			get_texture(char *path, t_texture *txtr, void *ptr)
{
	t_mlx_img	*tmp;

	tmp = &txtr->txtr;
	if (!(txtr->img = mlx_xpm_file_to_image(ptr, path, &txtr->w, &txtr->h)))
	{
		ft_printf("Error\nWrong texture path\n");
		return (0);
	}
	tmp->img = mlx_get_data_addr(txtr->img, &tmp->bpp, &tmp->len, &tmp->endian);
	return (1);
}

int					conv_texture(char *str, t_params *params, char c)
{
	char	*path;
	int		ret;

	path = ft_strdup_no_sp(str);
	if (c == 'N')
		ret = get_texture(path, &params->graph.NO, params->ptr);
	else if (c == 'S')
		ret = get_texture(path, &params->graph.SO, params->ptr);
	else if (c == 'E')
		ret = get_texture(path, &params->graph.EA, params->ptr);
	else if (c == 'W')
		ret = get_texture(path, &params->graph.WE, params->ptr);
	else if (c == 'F')
		ret = get_texture(path, &params->bonus.F, params->ptr);
	else if (c == 'C')
		ret = get_texture(path, &params->bonus.C, params->ptr);
	else
		ret = get_texture(path, &params->graph.S, params->ptr);
	free(path);
	return (ret);
}

// static void			ft_rgb_to_int(t_params *params, t_RGB color, char c)
// {
// 	int		nb;

// 	nb = (int)color.Blue + 256 * (int)color.Green + 65536 * (int)color.Red;
// 	if (c == 'F')
// 		params->graph.F = mlx_get_color_value(params->ptr, nb);
// 	else
// 		params->graph.C = mlx_get_color_value(params->ptr, nb);
// }

static t_rgb		*floor_ceil(t_params *params, char c)
{
	if (c == 'F')
	{
		params->graph.F.true = 1;
		return (&params->graph.F);
	}
	else
	{
		params->graph.C.true = 1;
		return (&params->graph.C);
	}
}

int					conv_color(char *str, t_params *params, char c)
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

int					conv_resolution(char *str, t_params *params)
{
	int		i;

	i = 0;
	params->max.i = ft_atoi(&str[i]);
	while (str[i] == ' ')
		i++;
	while (ft_isdigit(str[i]))
		i++;
	params->max.j = ft_atoi(&str[i]);
	while (str[i] == ' ')
		i++;
	while (ft_isdigit(str[i]))
		i++;
	while (str[i] == ' ')
		i++;
	if (str[i])
	{
		ft_printf("Error\nWrong Resolution format\n");
		return (0);
	}
	return (1);
}
