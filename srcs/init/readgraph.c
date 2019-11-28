/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readgraph.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 12:11:22 by mchardin          #+#    #+#             */
/*   Updated: 2019/11/28 20:29:51 by mchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// 	#include <stdio.h>
// 	#include <sys/types.h>
// 	#include <sys/uio.h>
// 	#include <fcntl.h>
// 	#include <unistd.h>
// 	#include "mlx.h"
// void	changestring(char **str)
// {


// 	int fd;
// 	char str2[4166];
// 	int	end;
// 	int i = 0;
// 	fd = open("brick3.bmp", O_RDONLY);
// 	end = read(fd, str2, 4166);
// 	close(fd);

// 	int j = 70;
// 	while(j < end)
// 	{
// 		str[0][i] = str2[j];
// 		i++;
// 		j++;
// 	}
// }

static int			get_texture(char *path, t_texture *txtr, void *ptr, char c)
{
	t_mlx_img	tmp;

	if (!(txtr->img = mlx_xpm_file_to_image(ptr, path, &txtr->w, &txtr->h)))
	{
		ft_printf("Error\nMLX2 error\n");
		return (0);
	}
	if (!(txtr->txtr = ft_calloc(sizeof(int), txtr->w * txtr->h)))
	{
		ft_printf("Error\nAllocation error\n");
		return (0);
	}
	tmp.img = mlx_get_data_addr(txtr->img, &tmp.bpp, &tmp.len, &tmp.endian);
//
	// changestring(&tmp.img);
//
	if (c == 'N' || c == 'E')
		img_to_intne(tmp, txtr);
	else
		img_to_intsw(tmp, txtr);
	return (1);
}

int					conv_texture(char *str, t_params *params, char c)
{
	char	*path;
	int		ret;

	path = ft_strdup_no_sp(str);
	if (c == 'N')
		ret = get_texture(path, &params->graph.NO, params->ptr, c);
	else if (c == 'S')
		ret = get_texture(path, &params->graph.SO, params->ptr, c);
	else if (c == 'E')
		ret = get_texture(path, &params->graph.EA, params->ptr, c);
	else if (c == 'W')
		ret = get_texture(path, &params->graph.WE, params->ptr, c);
	else
		ret = get_texture(path, &params->graph.S, params->ptr, c);
	free(path);
	if (ret == 0)
		ft_printf("Error ret texture\n");
	return (ret);
}

static void			ft_rgb_to_int(t_params *params, t_RGB color, char c)
{
	int		nb;

	nb = (int)color.Blue + 256 * (int)color.Green + 65536 * (int)color.Red;
	if (c == 'F')
		params->graph.F = mlx_get_color_value(params->ptr, nb);
	else
		params->graph.C = mlx_get_color_value(params->ptr, nb);
}

int					conv_color(char *str, t_params *params, char c)
{
	t_RGB	color;
	int		i;

	i = 0;
	while (str[i] == ' ')
		i++;
	color.Red = (unsigned char)ft_atoi(&str[i]);
	while (ft_isdigit(str[i]))
		i++;
	if (str[i] == ',')
		i++;
	color.Green = (unsigned char)ft_atoi(&str[i]);
	while (ft_isdigit(str[i]))
		i++;
	if (str[i] == ',')
		i++;
	color.Blue = (unsigned char)ft_atoi(&str[i]);
	while (ft_isdigit(str[i]))
		i++;
	while (str[i] == ' ')
		i++;
	if (str[i])
		return (0);
	ft_rgb_to_int(params, color, c);
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
		return (0);
	return (1);
}
