/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readgraph.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 12:11:22 by mchardin          #+#    #+#             */
/*   Updated: 2019/12/12 11:08:47 by mchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int			get_texture(char *path, t_texture *txtr, void *ptr)
{
	t_mlx_img	*tmp;

	tmp = &txtr->txtr;
	if (!(txtr->img = mlx_xpm_file_to_image(ptr, path, &txtr->w, &txtr->h)))
	{
		ft_dprintf(2, "Error\nMlx error : %s ", strerror(errno));
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
		ret = get_texture(path, &params->graph.no, params->ptr);
	else if (c == 'S')
		ret = get_texture(path, &params->graph.so, params->ptr);
	else if (c == 'E')
		ret = get_texture(path, &params->graph.ea, params->ptr);
	else if (c == 'W')
		ret = get_texture(path, &params->graph.we, params->ptr);
	else if (c == 'F')
		ret = get_texture(path, &params->bonus.f, params->ptr);
	else if (c == 'C')
		ret = get_texture(path, &params->bonus.c, params->ptr);
	else
		ret = get_texture(path, &params->graph.s, params->ptr);
	free(path);
	if (ret == 0)
		txtr_error(c);
	return (ret);
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
		ft_dprintf(2, "Error\nWrong Resolution format\n");
		return (0);
	}
	return (1);
}
