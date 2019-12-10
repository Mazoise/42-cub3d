/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 08:59:32 by mchardin          #+#    #+#             */
/*   Updated: 2019/12/10 12:02:19 by mchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int			conv_params(char *str, t_params *params)
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
	else if (str[i] == 'F' || str[i] == 'C')
		ret = conv_texture(&str[i + 1], params, str[i]);
	else if (str[i])
	{
		ft_dprintf(2, "Error\nWrong information syntax\n");
		return (0);
	}
	if (ret == -1 && ret++)
		ft_dprintf(2, "Error\nWrong color syntax (R,G,B)");
	return (ret);
}

void		clear_void(t_mlx_img *map, t_idx max)
{
	int		i;
	int		opp;

	i = 0;
	opp = map->bpp / 8;
	while(i < max.i * max.j)
	{
		if (map->img[i * opp + 1] == 0
			&& map->img[i * opp + 2] == 0
			&& map->img[i * opp + 0] == 0)
			map->img[i * opp + 3] = (unsigned char)255;
		i++;
	}
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
	if (!params->bonus.F.img)
		ret = ft_dprintf(2, "Error\nMissing floor texture path\n");
	if (!params->bonus.C.img)
		ret = ft_dprintf(2, "Error\nMissing ceiling texture path\n");
	return (ret);
}

void		pre_color(t_colors *colors)
{
	colors->one.blue = 255;
	colors->one.red = 255;
	colors->one.green = 255;
	colors->two.blue = 150;
	colors->two.red = 54;
	colors->two.green = 54;
	colors->zero.blue = 54;
	colors->zero.red = 54;
	colors->zero.green = 54;
	colors->out.blue = 0;
	colors->out.red = 0;
	colors->out.green = 0;
	colors->player.blue = 130;
	colors->player.red = 150;
	colors->player.green = 54;
}

void		walk_here(t_pos dir, t_pos hit, t_pos *pos, t_params *params)
{
	if (params->event[OBJ] == 1)
	{
		if (is_grid_pos(hit.x, pos->y, params->grid, '0')
			|| is_grid_pos(hit.x, pos->y, params->grid, '2'))
			pos->x = dir.x;
		if (is_grid_pos(pos->x, hit.y, params->grid, '0')
			|| is_grid_pos(pos->x, hit.y, params->grid, '2'))
			pos->y = dir.y;
	}
	else
	{
		if (is_grid_pos(hit.x, pos->y, params->grid, '0'))
			pos->x = dir.x;
		if (is_grid_pos(pos->x, hit.y, params->grid, '0'))
			pos->y = dir.y;
	}
}
